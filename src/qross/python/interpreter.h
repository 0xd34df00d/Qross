/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <optional>
#include "../core/interpreter.h"

namespace Qross
{
    /// Takes the raised Python exception as an error, with the traceback as the trace.
    Error takeException();

    /**
     * Starts Python on first use and shuts it down with the interpreter,
     * which also flushes the output of the scripts. A host that runs Python
     * already is left alone. Scripts of one process share the interpreter
     * and its modules, which keeps them light and gives them a common
     * \c sys.path.
     */
    class PythonInterpreter : public Interpreter
    {
        PyThreadState* m_mainThread = nullptr;
        std::optional<Error> m_failure;
    public:
        explicit PythonInterpreter(InterpreterInfo* info);
        ~PythonInterpreter() override;

        std::expected<std::unique_ptr<Context>, Error> createContext(Script* script) override;
    };
}
