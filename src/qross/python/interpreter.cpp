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
        setError(QStringLiteral("Python failed to start: %1").arg(QString::fromUtf8(status.err_msg ? status.err_msg : "no details")));
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

Context* PythonInterpreter::createContext(Script* script)
{
    return new PythonContext(this, script);
}

void Qross::storeException(ErrorInterface& target)
{
    const Ref exception(PyErr_GetRaisedException());
    if (!exception)
    {
        target.setError(QStringLiteral("Python failed without raising an exception"));
        return;
    }

    const Ref typeName(PyObject_GetAttrString(reinterpret_cast<PyObject*>(Py_TYPE(exception.get())), "__name__"));
    const Ref text(PyObject_Str(exception.get()));
    const QString message = QStringLiteral("%1: %2").arg(toVariant(typeName.get()).toString(), toVariant(text.get()).toString());

    QString trace;
    const Ref module(PyImport_ImportModule("traceback"));
    const Ref lines(module ? PyObject_CallMethod(module.get(), "format_exception", "O", exception.get()) : nullptr);
    if (lines)
        trace = toVariant(lines.get()).toStringList().join(QString()).trimmed();

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

    target.setError(message, trace, line);
}
