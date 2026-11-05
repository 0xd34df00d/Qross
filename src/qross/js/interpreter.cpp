/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007-2008 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "interpreter.h"
#include "context.h"
#include "object.h"

QROSS_EXPORT_INTERPRETER(Qross::JsInterpreter)

using namespace Qross;

JsInterpreter::JsInterpreter(InterpreterInfo* info)
    : Interpreter(info)
{
    JsObject::registerConverters();
}

Context* JsInterpreter::createContext(Script* script)
{
    return new JsContext(this, script);
}
