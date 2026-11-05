/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "function.h"
#include <QtCore/QSet>
#include "call.h"
#include "context.h"
#include "interpreter.h"
#include "variant.h"

using namespace Qross;

namespace
{
    QSet<RubyFunction*> relays;
}

RubyFunction::RubyFunction(QObject* sender, const QMetaMethod& signal, VALUE callable, RubyContext* owner)
    : MetaFunction(sender, signal)
    , m_callable(callable)
    , m_owner(owner)
{
    rb_gc_register_address(&m_callable);
    relays.insert(this);
    if (owner)
        owner->adopt(this);
    connect(sender, &QObject::destroyed, this, &QObject::deleteLater);
}

RubyFunction::~RubyFunction()
{
    relays.remove(this);
    if (rubyRunning())
        rb_gc_unregister_address(&m_callable);
}

bool RubyFunction::matches(VALUE callable) const
{
    const Result equal = callProtected(m_callable, rb_intern("=="), { callable });
    return equal && RTEST(*equal);
}

QList<RubyFunction*> RubyFunction::relaysOf(const QObject* sender)
{
    QList<RubyFunction*> result;
    for (RubyFunction* const relay : std::as_const(relays))
        if (relay->signalSender() == sender)
            result << relay;
    return result;
}

void RubyFunction::deleteAll()
{
    const QList<RubyFunction*> remaining(relays.cbegin(), relays.cend());
    qDeleteAll(remaining);
}

void RubyFunction::callback(const QVariantList& args)
{
    if (!onRubyThread())
    {
        qrosswarning(QStringLiteral("Signal %1 dropped: its Ruby handler cannot run on this thread").arg(QString::fromLatin1(signal().name())));
        return;
    }

    // Nothing awaits the result, so errors can only be logged.
    const RubyContext::Scope scope(m_owner);
    VALUE arguments = rb_ary_new_capa(args.size());
    for (const QVariant& arg : args)
    {
        const Result value = toRuby(arg);
        if (!value)
        {
            qrosswarning(errorOf(value.error()).toString());
            return;
        }
        rb_ary_push(arguments, *value);
    }
    const Result result = callProtected(m_callable, rb_intern("call"), RARRAY_LEN(arguments), RARRAY_CONST_PTR(arguments));
    RB_GC_GUARD(arguments);
    if (!result)
        qrosswarning(errorOf(result.error()).toString());
}
