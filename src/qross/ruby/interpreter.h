/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2007 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include "../core/interpreter.h"
#include "rubyapi.h"

namespace Qross
{
    /// \return whether Ruby is up. It stays down once the interpreter is gone.
    bool rubyRunning();

    /// \return whether the current thread is the one that started Ruby, the only one that may run it.
    bool onRubyThread();

    /// \return onRubyThread(), setting the error of \p target when it is false.
    bool requireRubyThread(ErrorInterface& target);

    /**
     * Moves \p exception into \p target: "Class: message" as the message,
     * Ruby's full report as the trace, and the line the report names.
     */
    void storeException(ErrorInterface& target, VALUE exception);

    /**
     * Starts Ruby on first use and shuts it down with the interpreter, which
     * runs the at_exit blocks of the scripts and flushes their output. A host
     * that runs Ruby already is left alone. Ruby cannot start twice in a
     * process, so a second interpreter after the first one is gone reports
     * an error.
     *
     * Ruby runs on one thread only, the one that created the interpreter.
     * Scripts and callbacks on other threads are refused rather than run;
     * signals emitted elsewhere reach their Ruby handlers through the event
     * loop of that thread.
     */
    class RubyInterpreter : public Interpreter
    {
        bool m_owner = false;
    public:
        explicit RubyInterpreter(InterpreterInfo* info);
        ~RubyInterpreter() override;

        Context* createContext(Script* script) override;
    };
}
