/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "interpreter.h"
#include "context.h"
#include "function.h"
#include "ref.h"
#include "variant.h"

QROSS_EXPORT_INTERPRETER(Qross::PythonInterpreter)

using namespace Qross;

namespace
{
    QString textOf(PyObject* object)
    {
        return object && PyUnicode_Check(object) ? toString(object) : QString();
    }
}

PythonInterpreter::PythonInterpreter(InterpreterInfo* info)
    : Interpreter(info)
{
    if (Py_IsInitialized())
        return;

    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    // Signals stay with the application.
    config.install_signal_handlers = 0;
    config.parse_argv = 0;
    const PyStatus status = Py_InitializeFromConfig(&config);
    PyConfig_Clear(&config);
    if (PyStatus_Exception(status))
    {
        m_failure = Error { QStringLiteral("Python failed to start: %1").arg(QString::fromUtf8(status.err_msg ? status.err_msg : "no details")) };
        return;
    }
    // Released here and taken per call, so that callbacks work from any thread.
    m_mainThread = PyEval_SaveThread();
}

PythonInterpreter::~PythonInterpreter()
{
    PythonFunction::deleteAll();
    if (!m_mainThread)
        return;
    PyEval_RestoreThread(m_mainThread);
    Py_FinalizeEx();
}

std::expected<std::unique_ptr<Context>, Error> PythonInterpreter::createContext(Script* script)
{
    if (m_failure)
        return std::unexpected(*m_failure);
    return std::make_unique<PythonContext>(this, script);
}

Error Qross::takeException()
{
    const Ref exception(PyErr_GetRaisedException());
    if (!exception)
        return Error { QStringLiteral("Python failed without raising an exception") };

    const Ref typeName(PyObject_GetAttrString(reinterpret_cast<PyObject*>(Py_TYPE(exception.get())), "__name__"));
    const Ref text(PyObject_Str(exception.get()));
    const QString message = QStringLiteral("%1: %2").arg(textOf(typeName.get()), textOf(text.get()));

    QString trace;
    const Ref module(PyImport_ImportModule("traceback"));
    const Ref lines(module ? PyObject_CallMethod(module.get(), "format_exception", "O", exception.get()) : nullptr);
    if (const auto list = lines ? toVariant(lines.get()) : std::nullopt)
        trace = list->toStringList().join(QString()).trimmed();

    long line = -1;
    for (Ref frame(PyException_GetTraceback(exception.get())); frame && frame.get() != Py_None; frame = Ref(PyObject_GetAttrString(frame.get(), "tb_next")))
    {
        const Ref number(PyObject_GetAttrString(frame.get(), "tb_lineno"));
        if (number)
            line = PyLong_AsLong(number.get());
    }
    if (line < 0)
    {
        const Ref number(PyObject_GetAttrString(exception.get(), "lineno"));
        if (number && number.get() != Py_None)
            line = PyLong_AsLong(number.get());
    }
    PyErr_Clear();

    return Error { message, trace, int(line) };
}
