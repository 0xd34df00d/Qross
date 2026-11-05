/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "context.h"

using namespace Qross;

Context::Context(Interpreter* interpreter, Script* script)
    : m_interpreter(interpreter)
    , m_script(script)
{
}

Interpreter* Context::interpreter() const
{
    return m_interpreter;
}

Script* Context::script() const
{
    return m_script;
}
