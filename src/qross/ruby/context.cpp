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
#include "../core/action.h"
#include "../core/manager.h"
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

RubyContext::RubyContext(Interpreter* interpreter, Action* action)
    : Context(interpreter, action)
{
    if (interpreter->hadError())
        setError(interpreter);
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

bool RubyContext::prepare()
{
    return requireRubyThread(*this) && ensureContext();
}

void RubyContext::resetContext()
{
    for (const QPointer<RubyFunction>& relay : std::as_const(m_connections))
        delete relay.data();
    m_connections.clear();
    m_self = Qnil;
    m_binding = Qnil;
}

bool RubyContext::ensureContext()
{
    if (!NIL_P(m_self))
        return true;

    m_self = wrapObject(action());
    rb_ivar_set(m_self, objectsKey(), rb_hash_new());
    // Extended rather than defined on self, so that they are not functions of the script.
    const VALUE accessors = rb_module_new();
    for (const auto& [name, object] : Manager::self().objects().asKeyValueRange())
        publish(accessors, name, object);
    for (const auto& [name, object] : action()->objects().asKeyValueRange())
        publish(accessors, name, object);
    rb_extend_object(m_self, accessors);

    const VALUE arguments[] = { fromString(QStringLiteral("binding")), fromString(QStringLiteral("<qross>")), INT2FIX(1) };
    const Result binding = callProtected(m_self, rb_intern("instance_eval"), std::size(arguments), arguments);
    if (!binding)
    {
        storeException(*this, binding.error());
        resetContext();
        return false;
    }
    m_binding = *binding;
    appendLoadPath();
    return true;
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
    const QString directory = action()->currentPath();
    if (directory.isEmpty())
        return;
    const VALUE path = rb_gv_get("$LOAD_PATH");
    const VALUE entry = fromString(directory);
    if (RB_TYPE_P(path, T_ARRAY) && !RTEST(rb_ary_includes(path, entry)))
        rb_ary_push(path, entry);
}

QVariant RubyContext::run(const QByteArray& code, const QString& file)
{
    const VALUE arguments[] = { rb_utf8_str_new(code.constData(), code.size()), fromString(file), INT2FIX(1) };
    const Result result = callProtected(m_binding, rb_intern("eval"), std::size(arguments), arguments);
    if (!result)
    {
        storeException(*this, result.error());
        return {};
    }
    return toVariant(*result);
}

void RubyContext::execute()
{
    clearError();
    if (!requireRubyThread(*this))
        return;
    resetContext();
    if (!ensureContext())
        return;
    run(action()->code(), action()->file().isEmpty() ? action()->name() : action()->file());
    if (!hadError())
        connectSignals();
}

VALUE RubyContext::functions()
{
    VALUE inherited = Qfalse;
    return rb_obj_singleton_methods(1, &inherited, m_self);
}

void RubyContext::connectSignals()
{
    const VALUE names = functions();
    const QHash<QString, ChildrenInterface::Options> options = action()->objectOptions();
    for (auto it = options.cbegin(); it != options.cend(); ++it)
    {
        if (!(it.value() & ChildrenInterface::AutoConnectSignals))
            continue;
        QObject* const sender = action()->object(it.key());
        if (!sender)
            continue;

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

QVariant RubyContext::callFunction(const QString& name, const QVariantList& args)
{
    clearError();
    if (!prepare())
        return {};

    const QByteArray utf8 = name.toUtf8();
    const ID id = rb_intern2(utf8.constData(), utf8.size());
    if (!RTEST(rb_ary_includes(functions(), ID2SYM(id))))
    {
        setError(QStringLiteral("No such function \"%1\"").arg(name));
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
    const Result result = callProtected(m_self, id, RARRAY_LEN(arguments), RARRAY_CONST_PTR(arguments));
    RB_GC_GUARD(arguments);
    if (!result)
    {
        storeException(*this, result.error());
        return {};
    }
    return toVariant(*result);
}

QVariant RubyContext::evaluate(const QByteArray& code)
{
    clearError();
    if (!prepare())
        return {};
    return run(code, QStringLiteral("<evaluate>"));
}
