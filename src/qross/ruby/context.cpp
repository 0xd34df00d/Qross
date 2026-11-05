/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2007 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "context.h"
#include <QtCore/QMetaMethod>
#include <QtCore/QSet>
#include "../core/script.h"
#include "call.h"
#include "function.h"
#include "interpreter.h"
#include "variant.h"
#include "wrapper.h"

using namespace Qross;

namespace
{
    /// The hidden instance variable holding the published objects by name.
    ID objectsKey()
    {
        static const ID key = rb_intern("__qross_objects");
        return key;
    }

    /// The method behind every published object: it answers to the name it was published under.
    VALUE publishedObject(VALUE self)
    {
        return rb_hash_lookup2(rb_ivar_get(self, objectsKey()), ID2SYM(rb_frame_this_func()), Qnil);
    }
}

RubyContext::RubyContext(Interpreter* interpreter, Script* script)
    : Context(interpreter, script)
{
    if (rubyRunning())
    {
        rb_gc_register_address(&m_self);
        rb_gc_register_address(&m_binding);
    }
}

RubyContext::~RubyContext()
{
    if (!rubyRunning())
        return;
    resetContext();
    rb_gc_unregister_address(&m_self);
    rb_gc_unregister_address(&m_binding);
}

std::expected<void, Error> RubyContext::prepare()
{
    if (const auto thread = requireRubyThread(); !thread)
        return thread;
    return ensureContext();
}

void RubyContext::resetContext()
{
    for (const QPointer<RubyFunction>& relay : std::as_const(m_connections))
        delete relay.data();
    m_connections.clear();
    m_self = Qnil;
    m_binding = Qnil;
}

std::expected<void, Error> RubyContext::ensureContext()
{
    if (!NIL_P(m_self))
        return {};

    m_self = wrapObject(script());
    rb_ivar_set(m_self, objectsKey(), rb_hash_new());
    // Extended rather than defined on self, so that they are not functions of the script.
    const VALUE accessors = rb_module_new();
    for (const Published& published : script()->publishedObjects())
        publish(accessors, published.name, published.object);
    rb_extend_object(m_self, accessors);

    const VALUE arguments[] = { fromString(QStringLiteral("binding")), fromString(QStringLiteral("<qross>")), INT2FIX(1) };
    const Result binding = callProtected(m_self, rb_intern("instance_eval"), std::size(arguments), arguments);
    if (!binding)
    {
        resetContext();
        return std::unexpected(errorOf(binding.error()));
    }
    m_binding = *binding;
    appendLoadPath();
    return {};
}

void RubyContext::publish(VALUE accessors, const QString& name, QObject* object)
{
    const QByteArray utf8 = name.toUtf8();
    const ID id = rb_intern2(utf8.constData(), utf8.size());
    const VALUE wrapper = wrapObject(object);
    rb_hash_aset(rb_ivar_get(m_self, objectsKey()), ID2SYM(id), wrapper);
    rb_define_method(accessors, utf8.constData(), publishedObject, 0);
    if (rb_is_const_id(id))
        rb_const_set(rb_singleton_class(m_self), id, wrapper);
}

void RubyContext::appendLoadPath()
{
    // Appended rather than put first, so that a script named like an
    // installed library does not shadow it for itself.
    const QString directory = script()->directory();
    if (directory.isEmpty())
        return;
    const VALUE path = rb_gv_get("$LOAD_PATH");
    const VALUE entry = fromString(directory);
    if (RB_TYPE_P(path, T_ARRAY) && !RTEST(rb_ary_includes(path, entry)))
        rb_ary_push(path, entry);
}

std::expected<QVariant, Error> RubyContext::run(const QByteArray& code, const QString& file)
{
    const VALUE arguments[] = { rb_utf8_str_new(code.constData(), code.size()), fromString(file), INT2FIX(1) };
    const Result result = callProtected(m_binding, rb_intern("eval"), std::size(arguments), arguments);
    if (!result)
        return std::unexpected(errorOf(result.error()));
    const auto value = toVariant(*result);
    if (!value)
        return std::unexpected(errorOf(value.error()));
    return *value;
}

std::expected<void, Error> RubyContext::execute()
{
    if (const auto thread = requireRubyThread(); !thread)
        return thread;
    resetContext();
    if (const auto context = ensureContext(); !context)
        return context;
    if (const auto result = run(script()->code(), script()->name()); !result)
        return std::unexpected(result.error());
    connectSignals();
    return {};
}

VALUE RubyContext::functions()
{
    VALUE inherited = Qfalse;
    return rb_obj_singleton_methods(1, &inherited, m_self);
}

void RubyContext::connectSignals()
{
    const VALUE names = functions();
    for (const Published& published : script()->publishedObjects())
    {
        if (!(published.options & AutoConnectSignals))
            continue;
        QObject* const sender = published.object;

        // Overloads share a name, so one connection per name.
        QSet<QByteArray> connected;
        const QMetaObject* const meta = sender->metaObject();
        for (int i = 0; i < meta->methodCount(); ++i)
        {
            const QMetaMethod method = meta->method(i);
            if (method.methodType() != QMetaMethod::Signal || connected.contains(method.name()))
                continue;
            const ID id = rb_intern2(method.name().constData(), method.name().size());
            if (!RTEST(rb_ary_includes(names, ID2SYM(id))))
                continue;
            const Result handler = callProtected(m_self, rb_intern("method"), { ID2SYM(id) });
            if (!handler)
                continue;
            connected.insert(method.name());
            m_connections << new RubyFunction(sender, method, *handler);
        }
    }
}

QStringList RubyContext::functionNames()
{
    if (!prepare())
        return {};
    const VALUE names = functions();
    QStringList result;
    for (long i = 0; i < RARRAY_LEN(names); ++i)
        result << toString(rb_ary_entry(names, i));
    return result;
}

std::expected<QVariant, Error> RubyContext::callFunction(const QString& name, const QVariantList& args)
{
    if (const auto ready = prepare(); !ready)
        return std::unexpected(ready.error());

    const QByteArray utf8 = name.toUtf8();
    const ID id = rb_intern2(utf8.constData(), utf8.size());
    if (!RTEST(rb_ary_includes(functions(), ID2SYM(id))))
        return std::unexpected(Error { QStringLiteral("No such function \"%1\"").arg(name) });

    VALUE arguments = rb_ary_new_capa(args.size());
    for (const QVariant& arg : args)
    {
        const Result value = toRuby(arg);
        if (!value)
            return std::unexpected(errorOf(value.error()));
        rb_ary_push(arguments, *value);
    }
    const Result result = callProtected(m_self, id, RARRAY_LEN(arguments), RARRAY_CONST_PTR(arguments));
    RB_GC_GUARD(arguments);
    if (!result)
        return std::unexpected(errorOf(result.error()));
    const auto value = toVariant(*result);
    if (!value)
        return std::unexpected(errorOf(value.error()));
    return *value;
}

std::expected<QVariant, Error> RubyContext::evaluate(const QByteArray& code)
{
    if (const auto ready = prepare(); !ready)
        return std::unexpected(ready.error());
    return run(code, QStringLiteral("<evaluate>"));
}
