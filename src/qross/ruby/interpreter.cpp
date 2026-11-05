/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2007 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "interpreter.h"
#include <csignal>
#include <iterator>
#include <QtCore/QRegularExpression>
#include <QtCore/QThread>
#include "call.h"
#include "context.h"
#include "function.h"
#include "variant.h"

QROSS_EXPORT_INTERPRETER(Qross::RubyInterpreter)

using namespace Qross;

namespace
{
    enum class State
    {
        Down,
        Up,
        Gone
    };

    State state = State::Down;
    QThread* rubyThread = nullptr;

    /**
     * Ruby takes these over when it starts and turns them into exceptions
     * it raises the next time it runs, which would make SIGTERM and Ctrl-C
     * wait for the next script. They stay with the application.
     */
    constexpr int applicationSignals[] = { SIGINT, SIGHUP, SIGQUIT, SIGTERM, SIGALRM, SIGUSR1, SIGUSR2 };

    class Dispositions
    {
        struct sigaction m_saved[std::size(applicationSignals)] = {};
    public:
        Dispositions()
        {
            for (size_t i = 0; i < std::size(applicationSignals); ++i)
                sigaction(applicationSignals[i], nullptr, &m_saved[i]);
        }

        void restore() const
        {
            for (size_t i = 0; i < std::size(applicationSignals); ++i)
                sigaction(applicationSignals[i], &m_saved[i], nullptr);
        }
    };

    VALUE requireDate(VALUE)
    {
        return rb_require("date");
    }

    VALUE fullMessage(VALUE exception)
    {
        VALUE options = rb_hash_new();
        rb_hash_aset(options, ID2SYM(rb_intern("highlight")), Qfalse);
        rb_hash_aset(options, ID2SYM(rb_intern("order")), ID2SYM(rb_intern("top")));
        return rb_funcallv_kw(exception, rb_intern("full_message"), 1, &options, RB_PASS_KEYWORDS);
    }

    /// \return the line of the first "file:line:" in \p text, or -1.
    long lineOf(const QString& text)
    {
        static const QRegularExpression location(QStringLiteral(":(\\d+):"));
        const QRegularExpressionMatch match = location.match(text);
        return match.hasMatch() ? match.captured(1).toLong() : -1;
    }
}

bool Qross::rubyRunning()
{
    return state == State::Up;
}

bool Qross::onRubyThread()
{
    return state == State::Up && QThread::currentThread() == rubyThread;
}

bool Qross::requireRubyThread(ErrorInterface& target)
{
    if (onRubyThread())
        return true;
    target.setError(rubyRunning() ? QStringLiteral("Ruby runs only on the thread that started it") : QStringLiteral("Ruby is not running"));
    return false;
}

void Qross::storeException(ErrorInterface& target, VALUE exception)
{
    const QString type = toString(rb_class_name(rb_obj_class(exception)));
    const Result message = callProtected(exception, rb_intern("message"), {});
    const QString text = message && RB_TYPE_P(*message, T_STRING) ? toString(*message) : QString();

    long line = -1;
    const Result backtrace = callProtected(exception, rb_intern("backtrace"), {});
    if (backtrace && RB_TYPE_P(*backtrace, T_ARRAY))
        for (long i = 0; i < RARRAY_LEN(*backtrace) && line < 0; ++i)
            line = lineOf(toString(rb_ary_entry(*backtrace, i)));
    // Syntax errors name their line in the message only.
    if (line < 0)
        line = lineOf(text);

    const Result report = runProtected(fullMessage, exception);
    const QString trace = report && RB_TYPE_P(*report, T_STRING) ? toString(*report).trimmed() : QString();

    target.setError(QStringLiteral("%1: %2").arg(type, text), trace, line);
}

RubyInterpreter::RubyInterpreter(InterpreterInfo* info)
    : Interpreter(info)
{
    if (state == State::Up)
        return;
    if (state == State::Gone)
    {
        setError(QStringLiteral("Ruby cannot start again in this process"));
        return;
    }

    rubyThread = QThread::currentThread();
    if (rb_cObject)
    {
        // The host runs Ruby already.
        state = State::Up;
        return;
    }

    const Dispositions dispositions;
    volatile VALUE marker = Qnil;
    ruby_init_stack(&marker);
    if (ruby_setup() != 0)
    {
        state = State::Gone;
        setError(QStringLiteral("Ruby failed to start"));
        return;
    }
    // An empty program: ruby_options sets up the load path, RubyGems and
    // the rest of what the ruby binary does before it runs a script.
    const char* arguments[] = { "qross", "-e", "" };
    void* const program = ruby_options(int(std::size(arguments)), const_cast<char**>(arguments));
    m_owner = true;
    state = State::Up;
    dispositions.restore();

    int status = 0;
    if (!ruby_executable_node(program, &status))
    {
        setError(QStringLiteral("Ruby failed to start, status %1").arg(status));
        return;
    }
    ruby_script("qross");
    // Dates have a Ruby class only with the date library loaded.
    if (!runProtected(requireDate, Qnil))
        qrosswarning(QStringLiteral("Ruby cannot load the date library; dates travel as strings"));
}

RubyInterpreter::~RubyInterpreter()
{
    if (!onRubyThread())
    {
        if (m_owner)
            qrosswarning(QStringLiteral("Ruby is left running: the interpreter is destroyed on another thread"));
        return;
    }
    RubyFunction::deleteAll();
    if (!m_owner)
        return;
    state = State::Gone;
    ruby_cleanup(0);
}

Context* RubyInterpreter::createContext(Action* action)
{
    return new RubyContext(this, action);
}
