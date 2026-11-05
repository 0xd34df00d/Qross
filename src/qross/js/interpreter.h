/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007-2008 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include "../core/interpreter.h"

namespace Qross
{
    /// Creates a \a JsContext for every \a Script that runs JavaScript.
    class JsInterpreter : public Interpreter
    {
    public:
        explicit JsInterpreter(InterpreterInfo* info);

        Context* createContext(Script* script) override;
    };
}
