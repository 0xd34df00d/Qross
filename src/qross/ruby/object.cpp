/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2005 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "object.h"
#include "call.h"
#include "interpreter.h"
#include "variant.h"

using namespace Qross;

RubyObject::RubyObject(VALUE value)
    : m_value(value)
{
    rb_gc_register_address(&m_value);
}

RubyObject::~RubyObject()
{
    // Once Ruby is gone, so is its list of addresses.
    if (rubyRunning())
        rb_gc_unregister_address(&m_value);
}

QVariant RubyObject::callMethod(const QString& name, const QVariantList& args)
{
    clearError();
    if (!requireRubyThread(*this))
        return {};

    const QByteArray utf8 = name.toUtf8();
    const ID method = rb_intern2(utf8.constData(), utf8.size());
    const Result known = callProtected(m_value, rb_intern("respond_to?"), { ID2SYM(method) });
    if (!known)
    {
        storeException(*this, known.error());
        return {};
    }
    if (!RTEST(*known))
    {
        setError(QStringLiteral("No such method \"%1\"").arg(name));
        return {};
    }

    VALUE arguments = rb_ary_new_capa(args.size());
    for (const QVariant& arg : args)
    {
        const Result value = toRuby(arg);
        if (!value)
        {
            storeException(*this, value.error());
            return {};
        }
        rb_ary_push(arguments, *value);
    }
    const Result result = callProtected(m_value, method, RARRAY_LEN(arguments), RARRAY_CONST_PTR(arguments));
    RB_GC_GUARD(arguments);
    if (!result)
    {
        storeException(*this, result.error());
        return {};
    }
    return toVariant(*result);
}

QStringList RubyObject::methodNames()
{
    if (!onRubyThread())
        return {};
    const Result names = callProtected(m_value, rb_intern("public_methods"), { Qfalse });
    QStringList result;
    if (names && RB_TYPE_P(*names, T_ARRAY))
        for (long i = 0; i < RARRAY_LEN(*names); ++i)
            result << toString(rb_ary_entry(*names, i));
    result.sort();
    return result;
}
