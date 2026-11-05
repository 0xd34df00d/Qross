/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "context.h"

using namespace Qross;

Context::Context(Interpreter* interpreter, Action* action)
    : m_interpreter(interpreter)
    , m_action(action)
{
}

Interpreter* Context::interpreter() const
{
    return m_interpreter;
}

Action* Context::action() const
{
    return m_action;
}
