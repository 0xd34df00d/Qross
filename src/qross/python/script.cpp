/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "script.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QSet>
#include "../core/action.h"
#include "../core/manager.h"
#include "function.h"
#include "gil.h"
#include "interpreter.h"
#include "ref.h"
#include "variant.h"
#include "wrapper.h"

using namespace Qross;

PythonScript::PythonScript(Interpreter* interpreter, Action* action)
    : Script(interpreter, action)
{
    if (interpreter->hadError())
        setError(interpreter);
}

PythonScript::~PythonScript()
{
    if (!Py_IsInitialized())
        return;
    const Gil gil;
    resetModule();
}

void PythonScript::resetModule()
{
    for (const QPointer<PythonFunction>& relay : std::as_const(m_connections))
        delete relay.data();
    m_connections.clear();
    Py_CLEAR(m_module);
}

PyObject* PythonScript::ensureModule()
{
    if (m_module)
        return m_module;

    Ref module(PyModule_New("__main__"));
    PyObject* const dict = PyModule_GetDict(module.get());
    PyDict_SetItemString(dict, "__builtins__", PyEval_GetBuiltins());
    if (!action()->file().isEmpty())
    {
        const Ref file(toPython(action()->file()));
        PyDict_SetItemString(dict, "__file__", file.get());
    }

    publish(dict, QStringLiteral("self"), action());
    for (const auto& [name, object] : Manager::self().objects().asKeyValueRange())
        publish(dict, name, object);
    for (const auto& [name, object] : action()->objects().asKeyValueRange())
        publish(dict, name, object);

    // Appended rather than put first, so that a script named like an
    // installed module does not shadow it for itself.
    const QString directory = action()->currentPath();
    if (!directory.isEmpty())
    {
        const Ref sys(PyImport_ImportModule("sys"));
        const Ref path(sys ? PyObject_GetAttrString(sys.get(), "path") : nullptr);
        const Ref entry(toPython(directory));
        if (path && PyList_Check(path.get()) && PySequence_Contains(path.get(), entry.get()) == 0)
            PyList_Append(path.get(), entry.get());
    }
    PyErr_Clear();

    m_module = module.release();
    return m_module;
}

void PythonScript::publish(PyObject* dict, const QString& name, QObject* object)
{
    const Ref wrapper(wrapObject(object));
    PyDict_SetItemString(dict, name.toUtf8().constData(), wrapper.get());
}

void PythonScript::execute()
{
    clearError();
    const Gil gil;
    resetModule();
    PyObject* const dict = PyModule_GetDict(ensureModule());

    const QByteArray file = (action()->file().isEmpty() ? action()->name() : action()->file()).toUtf8();
    const Ref code(Py_CompileString(action()->code().constData(), file.constData(), Py_file_input));
    const Ref result(code ? PyEval_EvalCode(code.get(), dict, dict) : nullptr);
    if (!result)
    {
        storeException(*this);
        return;
    }
    connectSignals();
}

void PythonScript::connectSignals()
{
    PyObject* const dict = PyModule_GetDict(m_module);
    const QHash<QString, ChildrenInterface::Options> options = action()->objectOptions();
    for (auto it = options.cbegin(); it != options.cend(); ++it)
    {
        if (!(it.value() & ChildrenInterface::AutoConnectSignals))
            continue;
        QObject* const sender = action()->object(it.key());
        if (!sender)
            continue;

        // Overloads share a name, so one connection per name.
        QSet<QByteArray> connected;
        const QMetaObject* const meta = sender->metaObject();
        for (int i = 0; i < meta->methodCount(); ++i)
        {
            const QMetaMethod method = meta->method(i);
            if (method.methodType() != QMetaMethod::Signal || connected.contains(method.name()))
                continue;
            PyObject* const handler = PyDict_GetItemString(dict, method.name().constData());
            if (!handler || !PyCallable_Check(handler))
                continue;
            connected.insert(method.name());
            m_connections << new PythonFunction(sender, method, handler);
        }
    }
}

QStringList PythonScript::functionNames()
{
    const Gil gil;
    PyObject* const dict = PyModule_GetDict(ensureModule());
    QStringList names;
    PyObject* key = nullptr;
    PyObject* value = nullptr;
    Py_ssize_t position = 0;
    while (PyDict_Next(dict, &position, &key, &value))
    {
        const QString name = toVariant(key).toString();
        if (name.startsWith(QLatin1String("__")) || !PyCallable_Check(value) || PyModule_Check(value))
            continue;
        names << name;
    }
    return names;
}

QVariant PythonScript::callFunction(const QString& name, const QVariantList& args)
{
    clearError();
    const Gil gil;
    PyObject* const dict = PyModule_GetDict(ensureModule());

    PyObject* const function = PyDict_GetItemString(dict, name.toUtf8().constData());
    if (!function || !PyCallable_Check(function))
    {
        setError(QStringLiteral("No such function \"%1\"").arg(name));
        return {};
    }

    Ref arguments(PyTuple_New(args.size()));
    for (qsizetype i = 0; i < args.size(); ++i)
    {
        PyObject* const argument = toPython(args[i]);
        if (!argument)
        {
            storeException(*this);
            return {};
        }
        PyTuple_SET_ITEM(arguments.get(), i, argument);
    }

    const Ref result(PyObject_CallObject(function, arguments.get()));
    if (!result)
    {
        storeException(*this);
        return {};
    }
    return toVariant(result.get());
}

QVariant PythonScript::evaluate(const QByteArray& code)
{
    clearError();
    const Gil gil;
    PyObject* const dict = PyModule_GetDict(ensureModule());

    // An expression has a value; anything else runs as statements.
    Ref compiled(Py_CompileString(code.constData(), "<evaluate>", Py_eval_input));
    if (!compiled && PyErr_ExceptionMatches(PyExc_SyntaxError))
    {
        PyErr_Clear();
        compiled = Ref(Py_CompileString(code.constData(), "<evaluate>", Py_file_input));
    }
    const Ref result(compiled ? PyEval_EvalCode(compiled.get(), dict, dict) : nullptr);
    if (!result)
    {
        storeException(*this);
        return {};
    }
    return toVariant(result.get());
}
