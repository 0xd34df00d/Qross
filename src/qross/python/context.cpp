/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "context.h"
#include <utility>
#include <QtCore/QFileInfo>
#include <QtCore/QMetaMethod>
#include <QtCore/QRegularExpression>
#include <QtCore/QSet>
#include "../core/script.h"
#include "function.h"
#include "gil.h"
#include "interpreter.h"
#include "ref.h"
#include "variant.h"
#include "wrapper.h"

using namespace Qross;

namespace
{
    thread_local PythonContext* currentContext = nullptr;

    /// \return qross_ and the name of \p script as an identifier, numbered while sys.modules has it.
    QByteArray moduleName(const QString& script)
    {
        QString stem = QFileInfo(script).completeBaseName();
        stem.replace(QRegularExpression(QStringLiteral("\\W")), QStringLiteral("_"));
        stem.remove(QRegularExpression(QStringLiteral("^_+|_+$")));
        if (stem.isEmpty())
            stem = QStringLiteral("script");

        const QByteArray base = "qross_" + stem.toUtf8();
        PyObject* const modules = PyImport_GetModuleDict();
        QByteArray name = base;
        for (int n = 2; PyDict_GetItemString(modules, name.constData()); ++n)
            name = base + '_' + QByteArray::number(n);
        return name;
    }
}

PythonContext::PythonContext(Interpreter* interpreter, Script* script)
    : Context(interpreter, script)
{
}

PythonContext::~PythonContext()
{
    if (!Py_IsInitialized())
        return;
    const Gil gil;
    resetModule();
}

PythonContext* PythonContext::current()
{
    return currentContext;
}

PythonContext::Scope::Scope(PythonContext* context)
    : m_previous(std::exchange(currentContext, context))
{
}

PythonContext::Scope::~Scope()
{
    currentContext = m_previous;
}

void PythonContext::adopt(PythonFunction* relay)
{
    m_connections << relay;
}

void PythonContext::resetModule()
{
    for (const QPointer<PythonFunction>& relay : std::as_const(m_connections))
        delete relay.data();
    m_connections.clear();
    if (m_module)
    {
        PyObject* const modules = PyImport_GetModuleDict();
        if (PyDict_GetItemString(modules, m_name.constData()) == m_module)
            PyDict_DelItemString(modules, m_name.constData());
    }
    Py_CLEAR(m_module);
}

PyObject* PythonContext::ensureModule()
{
    if (m_module)
        return m_module;

    m_name = moduleName(script()->name());
    Ref module(PyModule_New(m_name.constData()));
    PyObject* const dict = PyModule_GetDict(module.get());
    PyDict_SetItemString(dict, "__builtins__", PyEval_GetBuiltins());
    if (!script()->file().isEmpty())
    {
        const Ref file(toPython(script()->file()));
        PyDict_SetItemString(dict, "__file__", file.get());
    }

    publish(dict, QStringLiteral("self"), script());
    for (const Published& published : script()->publishedObjects())
        publish(dict, published.name, published.object);

    // Appended rather than put first, so that a script named like an
    // installed module does not shadow it for itself.
    const QString directory = script()->directory();
    if (!directory.isEmpty())
    {
        const Ref sys(PyImport_ImportModule("sys"));
        const Ref path(sys ? PyObject_GetAttrString(sys.get(), "path") : nullptr);
        const Ref entry(toPython(directory));
        if (path && PyList_Check(path.get()) && PySequence_Contains(path.get(), entry.get()) == 0)
            PyList_Append(path.get(), entry.get());
    }
    PyErr_Clear();

    PyDict_SetItemString(PyImport_GetModuleDict(), m_name.constData(), module.get());
    m_module = module.release();
    return m_module;
}

void PythonContext::publish(PyObject* dict, const QString& name, QObject* object)
{
    const Ref wrapper(wrapObject(object));
    PyDict_SetItemString(dict, name.toUtf8().constData(), wrapper.get());
}

std::expected<void, Error> PythonContext::execute()
{
    const Gil gil;
    const Scope scope(this);
    resetModule();
    PyObject* const dict = PyModule_GetDict(ensureModule());

    const QByteArray file = script()->name().toUtf8();
    const Ref code(Py_CompileString(script()->code().constData(), file.constData(), Py_file_input));
    const Ref result(code ? PyEval_EvalCode(code.get(), dict, dict) : nullptr);
    if (!result)
        return std::unexpected(takeException());
    connectSignals();
    return {};
}

void PythonContext::connectSignals()
{
    PyObject* const dict = PyModule_GetDict(m_module);
    for (const Published& published : script()->publishedObjects())
    {
        if (!(published.options & AutoConnectSignals))
            continue;
        QObject* const sender = published.object;

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
            new PythonFunction(sender, method, handler, this);
        }
    }
}

std::expected<QStringList, Error> PythonContext::functionNames()
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

std::expected<QVariant, Error> PythonContext::callFunction(const QString& name, const QVariantList& args)
{
    const Gil gil;
    const Scope scope(this);
    PyObject* const dict = PyModule_GetDict(ensureModule());

    PyObject* const function = PyDict_GetItemString(dict, name.toUtf8().constData());
    if (!function || !PyCallable_Check(function))
        return std::unexpected(Error { QStringLiteral("No such function \"%1\"").arg(name) });

    Ref arguments(PyTuple_New(args.size()));
    for (qsizetype i = 0; i < args.size(); ++i)
    {
        PyObject* const argument = toPython(args[i]);
        if (!argument)
            return std::unexpected(takeException());
        PyTuple_SET_ITEM(arguments.get(), i, argument);
    }

    const Ref result(PyObject_CallObject(function, arguments.get()));
    if (!result)
        return std::unexpected(takeException());
    return toVariant(result.get());
}

std::expected<QVariant, Error> PythonContext::evaluate(const QByteArray& code)
{
    const Gil gil;
    const Scope scope(this);
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
        return std::unexpected(takeException());
    return toVariant(result.get());
}
