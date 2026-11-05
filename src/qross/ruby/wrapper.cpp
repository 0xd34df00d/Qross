/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2007 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006-2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "wrapper.h"
#include <QtCore/QHash>
#include <QtCore/QMetaMethod>
#include <QtCore/QMetaProperty>
#include <QtCore/QPointer>
#include <QtCore/QRect>
#include <QtCore/QSequentialIterable>
#include <QtCore/QSet>
#include <QtCore/QVarLengthArray>
#include "../core/object.h"
#include "../core/wrapperinterface.h"
#include "call.h"
#include "context.h"
#include "function.h"
#include "object.h"
#include "variant.h"

using namespace Qross;

namespace
{
    void freeWrapper(void* pointer)
    {
        delete static_cast<QPointer<QObject>*>(pointer);
    }

    size_t wrapperSize(const void*)
    {
        return sizeof(QPointer<QObject>);
    }

    const rb_data_type_t wrapperType = {
        .wrap_struct_name = "Qross::QObject",
        .function = { .dmark = nullptr, .dfree = freeWrapper, .dsize = wrapperSize },
        .flags = RUBY_TYPED_FREE_IMMEDIATELY,
    };

    /// What a metaobject offers under which name, computed once per class.
    struct Index
    {
        QHash<QByteArray, QList<int>> methods;
        QHash<QByteArray, int> enums;
    };

    const Index& indexOf(const QMetaObject* meta)
    {
        static QHash<const QMetaObject*, Index> cache;
        const auto found = cache.constFind(meta);
        if (found != cache.cend())
            return found.value();

        Index index;
        for (int i = 0; i < meta->methodCount(); ++i)
        {
            const QMetaMethod method = meta->method(i);
            if (method.access() == QMetaMethod::Private || method.methodType() == QMetaMethod::Constructor)
                continue;
            // Scripts get the signals of QObject but not deleteLater().
            if (method.enclosingMetaObject() == &QObject::staticMetaObject && method.methodType() != QMetaMethod::Signal)
                continue;
            index.methods[method.name()] << i;
        }
        for (int i = 0; i < meta->enumeratorCount(); ++i)
        {
            const QMetaEnum enumerator = meta->enumerator(i);
            for (int j = 0; j < enumerator.keyCount(); ++j)
                index.enums.insert(enumerator.key(j), enumerator.value(j));
        }
        return *cache.insert(meta, index);
    }

    QObject* objectOf(VALUE self)
    {
        const auto* const pointer = static_cast<const QPointer<QObject>*>(RTYPEDDATA_DATA(self));
        return pointer ? pointer->data() : nullptr;
    }

    /// \return the wrapped object, or RuntimeError when it is gone.
    std::expected<QObject*, VALUE> liveObject(VALUE self)
    {
        if (QObject* const object = objectOf(self))
            return object;
        return fail(rb_eRuntimeError, QStringLiteral("the wrapped QObject has been deleted"));
    }

    /// Storage for one slot of a metacall.
    struct Argument
    {
        QVariant value;
        bool variant = false;

        void* data() { return variant ? static_cast<void*>(&value) : value.data(); }
    };

    bool numbers(VALUE array, long count, double* out)
    {
        if (!RB_TYPE_P(array, T_ARRAY) || RARRAY_LEN(array) != count)
            return false;
        for (long i = 0; i < count; ++i)
        {
            const VALUE item = rb_ary_entry(array, i);
            if (RB_FLOAT_TYPE_P(item))
                out[i] = RFLOAT_VALUE(item);
            else if (FIXNUM_P(item))
                out[i] = double(FIX2LONG(item));
            else if (RB_TYPE_P(item, T_BIGNUM))
                out[i] = rb_big2dbl(item);
            else
                return false;
        }
        return true;
    }

    bool convertGeometry(VALUE value, QMetaType type, Argument& argument)
    {
        double n[4] = {};
        switch (type.id())
        {
        case QMetaType::QSize:
            if (numbers(value, 2, n))
                argument.value = QSize(int(n[0]), int(n[1]));
            break;
        case QMetaType::QSizeF:
            if (numbers(value, 2, n))
                argument.value = QSizeF(n[0], n[1]);
            break;
        case QMetaType::QPoint:
            if (numbers(value, 2, n))
                argument.value = QPoint(int(n[0]), int(n[1]));
            break;
        case QMetaType::QPointF:
            if (numbers(value, 2, n))
                argument.value = QPointF(n[0], n[1]);
            break;
        case QMetaType::QRect:
            if (numbers(value, 4, n))
                argument.value = QRect(int(n[0]), int(n[1]), int(n[2]), int(n[3]));
            break;
        case QMetaType::QRectF:
            if (numbers(value, 4, n))
                argument.value = QRectF(n[0], n[1], n[2], n[3]);
            break;
        default:
            break;
        }
        return argument.value.isValid();
    }

    /// Fills \p argument for a parameter or property of \p type, or explains in a TypeError why \p value does not fit.
    std::expected<void, VALUE> convertArgument(VALUE value, QMetaType type, Argument& argument)
    {
        if (type == QMetaType::fromType<QVariant>())
        {
            auto converted = toVariant(value);
            if (!converted)
                return std::unexpected(converted.error());
            argument.value = std::move(*converted);
            argument.variant = true;
            return {};
        }
        if (NIL_P(value))
        {
            argument.value = QVariant(type);
            if (argument.value.isValid())
                return {};
            return fail(rb_eTypeError, QStringLiteral("cannot pass nil as %1").arg(QString::fromLatin1(type.name())));
        }
        if (type == QMetaType::fromType<Object::Ptr>())
        {
            argument.value = QVariant::fromValue(Object::Ptr(new RubyObject(value)));
            return {};
        }
        if (isWrapper(value))
        {
            const auto wrapped = liveObject(value);
            if (!wrapped)
                return std::unexpected(wrapped.error());
            // A WrapperInterface stands in for what it wraps wherever it does not fit itself.
            auto* const interface = dynamic_cast<WrapperInterface*>(*wrapped);
            if (type.flags() & QMetaType::PointerToQObject)
            {
                const QMetaObject* const target = type.metaObject();
                QObject* pointer = *wrapped;
                if (target && !target->cast(pointer))
                {
                    if (!interface)
                        return fail(rb_eTypeError, QStringLiteral("expected %1, got %2").arg(QString::fromLatin1(type.name()), QString::fromLatin1(pointer->metaObject()->className())));
                    pointer = static_cast<QObject*>(interface->wrappedObject());
                }
                argument.value = QVariant(type, &pointer);
                return {};
            }
            if (interface)
            {
                void* const pointer = interface->wrappedObject();
                argument.value = (type.flags() & QMetaType::IsPointer) ? QVariant(type, &pointer) : QVariant(type, pointer);
                return {};
            }
            return fail(rb_eTypeError, QStringLiteral("cannot pass a %1 as %2").arg(QString::fromLatin1((*wrapped)->metaObject()->className()), QString::fromLatin1(type.name())));
        }
        if (convertGeometry(value, type, argument))
            return {};

        auto converted = toVariant(value);
        if (!converted)
            return std::unexpected(converted.error());
        if (converted->metaType() == type || converted->convert(type))
        {
            argument.value = std::move(*converted);
            return {};
        }

        // Any other array fills a container through the metatype's view.
        argument.value = QVariant(type);
        QSequentialIterable sequence;
        if (RB_TYPE_P(value, T_ARRAY) && argument.value.isValid() && QMetaType::view(type, argument.value.data(), QMetaType::fromType<QSequentialIterable>(), &sequence))
        {
            for (long i = 0; i < RARRAY_LEN(value); ++i)
            {
                Argument element;
                if (const auto ok = convertArgument(rb_ary_entry(value, i), sequence.valueMetaType(), element); !ok)
                    return ok;
                sequence.addValue(element.value, QSequentialIterable::AtEnd);
            }
            return {};
        }

        return fail(rb_eTypeError, QStringLiteral("cannot convert %1 to %2").arg(QString::fromUtf8(rb_obj_classname(value)), QString::fromLatin1(type.name())));
    }

    Result callMetaMethod(QObject* object, const QByteArray& name, int argc, const VALUE* argv)
    {
        const QMetaObject* const meta = object->metaObject();

        // The first overload whose arguments convert wins.
        QVarLengthArray<Argument, 8> arguments;
        QMetaMethod chosen;
        VALUE lastError = Qnil;
        for (const int index : indexOf(meta).methods.value(name))
        {
            const QMetaMethod candidate = meta->method(index);
            if (candidate.parameterCount() != argc)
                continue;
            arguments.clear();
            arguments.resize(argc);
            std::expected<void, VALUE> converted;
            for (int i = 0; i < argc && converted; ++i)
                converted = convertArgument(argv[i], candidate.parameterMetaType(i), arguments[i]);
            if (converted)
            {
                chosen = candidate;
                break;
            }
            lastError = converted.error();
        }
        if (!chosen.isValid())
        {
            if (!NIL_P(lastError))
                return std::unexpected(lastError);
            return fail(rb_eArgError, QStringLiteral("wrong number of arguments for %1.%2 (given %3)").arg(QString::fromLatin1(meta->className()), QString::fromLatin1(name)).arg(argc));
        }

        const QMetaType returnType = chosen.returnMetaType();
        if (!returnType.isValid())
            return fail(rb_eTypeError, QStringLiteral("the return type %1 of %2() is unknown to the metatype system").arg(QString::fromLatin1(chosen.typeName()), QString::fromLatin1(name)));
        const bool hasResult = returnType.id() != QMetaType::Void;
        Argument result;
        if (hasResult)
        {
            if (returnType == QMetaType::fromType<QVariant>())
                result.variant = true;
            else
                result.value = QVariant(returnType);
            if (!result.variant && !result.value.isValid())
                return fail(rb_eTypeError, QStringLiteral("cannot hold a return value of type %1").arg(QString::fromLatin1(returnType.name())));
        }

        QVarLengthArray<void*, 9> pointers(argc + 1);
        pointers[0] = hasResult ? result.data() : nullptr;
        for (int i = 0; i < argc; ++i)
            pointers[i + 1] = arguments[i].data();
        QMetaObject::metacall(object, QMetaObject::InvokeMetaMethod, chosen.methodIndex(), pointers.data());

        if (!hasResult)
            return Qnil;
        return toRuby(result.value);
    }

    Result readProperty(QObject* object, const QMetaProperty& property)
    {
        if (!property.isReadable())
            return fail(rb_eNoMethodError, QStringLiteral("property %1 is not readable").arg(QString::fromLatin1(property.name())));
        return toRuby(property.read(object));
    }

    Result writeProperty(QObject* object, const QMetaProperty& property, VALUE value)
    {
        if (!property.isWritable())
            return fail(rb_eNoMethodError, QStringLiteral("property %1 is not writable").arg(QString::fromLatin1(property.name())));
        Argument argument;
        if (const auto ok = convertArgument(value, property.metaType(), argument); !ok)
            return std::unexpected(ok.error());
        if (!property.write(object, argument.value))
            return fail(rb_eRuntimeError, QStringLiteral("setting %1 failed").arg(QString::fromLatin1(property.name())));
        return value;
    }

    /**
     * The body of every generated method. Property accessors, Qt methods
     * and enum keys are told apart by the name Ruby called.
     */
    Result dispatchImpl(int argc, VALUE* argv, VALUE self)
    {
        const auto object = liveObject(self);
        if (!object)
            return std::unexpected(object.error());
        const QByteArray name = rb_id2name(rb_frame_this_func());
        if (name.isEmpty())
            return fail(rb_eRuntimeError, QStringLiteral("cannot tell which method was called"));
        const QMetaObject* const meta = (*object)->metaObject();

        if (name.endsWith('='))
        {
            const int index = meta->indexOfProperty(name.chopped(1).constData());
            if (index >= 0 && argc == 1)
                return writeProperty(*object, meta->property(index), argv[0]);
        }
        else if (argc == 0)
        {
            const int index = meta->indexOfProperty(name.constData());
            if (index >= 0)
                return readProperty(*object, meta->property(index));
        }

        const Index& index = indexOf(meta);
        if (index.methods.contains(name))
            return callMetaMethod(*object, name, argc, argv);
        if (const auto found = index.enums.constFind(name); found != index.enums.cend() && argc == 0)
            return INT2NUM(found.value());
        return fail(rb_eArgError, QStringLiteral("wrong number of arguments for %1.%2 (given %3)").arg(QString::fromLatin1(meta->className()), QString::fromLatin1(name)).arg(argc));
    }

    Result propertyImpl(VALUE self, VALUE name)
    {
        const auto object = liveObject(self);
        if (!object)
            return std::unexpected(object.error());
        return toRuby((*object)->property(toString(name).toUtf8().constData()));
    }

    Result setPropertyImpl(VALUE self, VALUE name, VALUE value)
    {
        const auto object = liveObject(self);
        if (!object)
            return std::unexpected(object.error());
        const QByteArray utf8 = toString(name).toUtf8();
        const QMetaObject* const meta = (*object)->metaObject();
        const int index = meta->indexOfProperty(utf8.constData());
        Argument argument;
        if (const auto ok = convertArgument(value, index >= 0 ? meta->property(index).metaType() : QMetaType::fromType<QVariant>(), argument); !ok)
            return std::unexpected(ok.error());
        (*object)->setProperty(utf8.constData(), argument.value);
        return Qnil;
    }

    Result classNameImpl(VALUE self)
    {
        const auto object = liveObject(self);
        if (!object)
            return std::unexpected(object.error());
        return fromString(QString::fromLatin1((*object)->metaObject()->className()));
    }

    /// \return the signal \p spec names: a signature picks one overload, a bare name takes the first.
    QMetaMethod findSignal(const QMetaObject* meta, const QByteArray& spec)
    {
        if (spec.contains('('))
        {
            const int index = meta->indexOfSignal(QMetaObject::normalizedSignature(spec.constData()));
            return index >= 0 ? meta->method(index) : QMetaMethod();
        }
        for (const int index : indexOf(meta).methods.value(spec))
            if (meta->method(index).methodType() == QMetaMethod::Signal)
                return meta->method(index);
        return {};
    }

    Result connectImpl(int argc, VALUE* argv, VALUE self)
    {
        if (argc < 1 || argc > 2)
            return fail(rb_eArgError, QStringLiteral("wrong number of arguments (given %1, expected 1..2)").arg(argc));
        const auto object = liveObject(self);
        if (!object)
            return std::unexpected(object.error());

        const VALUE callable = argc == 2 ? argv[1] : rb_block_given_p() ? rb_block_proc() :
                                                                          Qnil;
        if (NIL_P(callable) || !rb_respond_to(callable, rb_intern("call")))
            return fail(rb_eArgError, QStringLiteral("connect() expects a block or something that responds to call"));
        const QByteArray spec = toString(argv[0]).toUtf8();
        const QMetaMethod signal = findSignal((*object)->metaObject(), spec);
        if (!signal.isValid())
            return fail(rb_eArgError, QStringLiteral("%1 has no signal %2").arg(QString::fromLatin1((*object)->metaObject()->className()), QString::fromUtf8(spec)));
        new RubyFunction(*object, signal, callable, RubyContext::current());
        return callable;
    }

    Result disconnectImpl(int argc, VALUE* argv, VALUE self)
    {
        if (argc < 1 || argc > 2)
            return fail(rb_eArgError, QStringLiteral("wrong number of arguments (given %1, expected 1..2)").arg(argc));
        const auto object = liveObject(self);
        if (!object)
            return std::unexpected(object.error());

        const QByteArray spec = toString(argv[0]).toUtf8();
        const QMetaMethod signal = findSignal((*object)->metaObject(), spec);
        if (!signal.isValid())
            return fail(rb_eArgError, QStringLiteral("%1 has no signal %2").arg(QString::fromLatin1((*object)->metaObject()->className()), QString::fromUtf8(spec)));
        const VALUE callable = argc == 2 ? argv[1] : Qnil;
        const bool exact = spec.contains('(');
        for (RubyFunction* const relay : RubyFunction::relaysOf(*object))
        {
            const bool sameSignal = exact ? relay->signal() == signal : relay->signal().name() == signal.name();
            if (sameSignal && (NIL_P(callable) || relay->matches(callable)))
                delete relay;
        }
        return Qnil;
    }

    Result equalImpl(VALUE self, VALUE other)
    {
        return isWrapper(other) && objectOf(self) == objectOf(other) ? Qtrue : Qfalse;
    }

    Result hashImpl(VALUE self)
    {
        return LONG2NUM(long(reinterpret_cast<quintptr>(objectOf(self)) >> 4));
    }

    Result inspectImpl(VALUE self)
    {
        QObject* const object = objectOf(self);
        const VALUE klass = rb_obj_class(self);
        QString name = toString(rb_mod_name(klass));
        if (name.isEmpty())
            name = QString::fromLatin1(object ? object->metaObject()->className() : "QObject");
        if (!object)
            return fromString(QStringLiteral("#<%1 (deleted)>").arg(name));
        return fromString(QStringLiteral("#<%1:0x%2 \"%3\">").arg(name, QString::number(reinterpret_cast<quintptr>(object), 16), object->objectName()));
    }

    /// Dynamic properties; anything else is left to Ruby, signalled by Qundef.
    Result methodMissingImpl(int argc, VALUE* argv, VALUE self)
    {
        QObject* const object = argc >= 1 ? objectOf(self) : nullptr;
        if (!object)
            return Qundef;
        const QByteArray name = toString(argv[0]).toUtf8();
        const QList<QByteArray> dynamic = object->dynamicPropertyNames();
        if (argc == 1 && dynamic.contains(name))
            return toRuby(object->property(name.constData()));
        if (argc == 2 && name.endsWith('=') && dynamic.contains(name.chopped(1)))
        {
            Argument argument;
            if (const auto ok = convertArgument(argv[1], QMetaType::fromType<QVariant>(), argument); !ok)
                return std::unexpected(ok.error());
            object->setProperty(name.chopped(1).constData(), argument.value);
            return argv[1];
        }
        return Qundef;
    }

    VALUE methodMissing(int argc, VALUE* argv, VALUE self)
    {
        const Result result = methodMissingImpl(argc, argv, self);
        if (!result)
            rb_exc_raise(result.error());
        if (*result == Qundef)
            return rb_call_super(argc, argv);
        return *result;
    }

    VALUE respondToMissing(VALUE self, VALUE name, VALUE)
    {
        QObject* const object = objectOf(self);
        if (!object)
            return Qfalse;
        const QByteArray utf8 = toString(name).toUtf8();
        const QList<QByteArray> dynamic = object->dynamicPropertyNames();
        return dynamic.contains(utf8) || (utf8.endsWith('=') && dynamic.contains(utf8.chopped(1))) ? Qtrue : Qfalse;
    }

    /// Raises what \p Impl failed with, once nothing of it is left on the stack.
    template<auto Impl>
    struct Method;

    template<typename... Args, Result (*Impl)(Args...)>
    struct Method<Impl>
    {
        static VALUE call(Args... args)
        {
            const Result result = Impl(args...);
            if (!result)
                rb_exc_raise(result.error());
            return *result;
        }
    };

    /// Names \p klass after the C++ class under Qross, where the name allows it and is still free.
    void nameClass(VALUE klass, const char* className)
    {
        QStringList parts = QString::fromLatin1(className).split(QStringLiteral("::"));
        if (parts.size() > 1 && parts.first() == QLatin1String("Qross"))
            parts.removeFirst();
        VALUE outer = rb_define_module("Qross");
        for (qsizetype i = 0; i < parts.size(); ++i)
        {
            const QByteArray part = parts[i].toUtf8();
            const ID id = rb_intern2(part.constData(), part.size());
            if (!rb_is_const_id(id))
                return;
            const bool last = i == parts.size() - 1;
            if (rb_const_defined_at(outer, id))
            {
                if (last)
                    return;
                outer = rb_const_get_at(outer, id);
                if (!RB_TYPE_P(outer, T_MODULE))
                    return;
            }
            else if (last)
                rb_const_set(outer, id, klass);
            else
                outer = rb_define_module_under(outer, part.constData());
        }
    }

    void defineRoot(VALUE klass)
    {
        rb_undef_alloc_func(klass);
        rb_define_method(klass, "property", Method<propertyImpl>::call, 1);
        rb_define_method(klass, "setProperty", Method<setPropertyImpl>::call, 2);
        rb_define_method(klass, "className", Method<classNameImpl>::call, 0);
        rb_define_method(klass, "connect", Method<connectImpl>::call, -1);
        rb_define_method(klass, "disconnect", Method<disconnectImpl>::call, -1);
        rb_define_method(klass, "==", Method<equalImpl>::call, 1);
        rb_define_method(klass, "eql?", Method<equalImpl>::call, 1);
        rb_define_method(klass, "hash", Method<hashImpl>::call, 0);
        rb_define_method(klass, "inspect", Method<inspectImpl>::call, 0);
        rb_define_method(klass, "to_s", Method<inspectImpl>::call, 0);
        rb_define_method(klass, "method_missing", methodMissing, -1);
        rb_define_method(klass, "respond_to_missing?", respondToMissing, 2);
    }

    /// Defines what \p meta adds to its superclass.
    void defineMembers(VALUE klass, const QMetaObject* meta)
    {
        QSet<QByteArray> defined;
        for (int i = meta->methodOffset(); i < meta->methodCount(); ++i)
        {
            const QMetaMethod method = meta->method(i);
            if (method.access() == QMetaMethod::Private || method.methodType() == QMetaMethod::Constructor)
                continue;
            if (meta == &QObject::staticMetaObject && method.methodType() != QMetaMethod::Signal)
                continue;
            if (defined.contains(method.name()))
                continue;
            defined.insert(method.name());
            rb_define_method(klass, method.name().constData(), Method<dispatchImpl>::call, -1);
        }
        for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
        {
            const QMetaProperty property = meta->property(i);
            rb_define_method(klass, property.name(), Method<dispatchImpl>::call, -1);
            if (property.isWritable())
                rb_define_method(klass, (QByteArray(property.name()) + '=').constData(), Method<dispatchImpl>::call, -1);
        }
        for (int i = meta->enumeratorOffset(); i < meta->enumeratorCount(); ++i)
        {
            const QMetaEnum enumerator = meta->enumerator(i);
            for (int j = 0; j < enumerator.keyCount(); ++j)
            {
                const char* const key = enumerator.key(j);
                rb_define_method(klass, key, Method<dispatchImpl>::call, -1);
                const ID id = rb_intern(key);
                if (rb_is_const_id(id) && !rb_const_defined_at(klass, id))
                    rb_const_set(klass, id, INT2NUM(enumerator.value(j)));
            }
        }
    }

    VALUE classFor(const QMetaObject* meta)
    {
        static QHash<const QMetaObject*, VALUE*> classes;
        if (VALUE* const found = classes.value(meta))
            return *found;

        const VALUE super = meta->superClass() ? classFor(meta->superClass()) : rb_cObject;
        const VALUE klass = rb_class_new(super);
        // The collector does not see the hash, so each class gets a registered slot.
        auto* const slot = new VALUE(klass);
        rb_gc_register_address(slot);
        classes.insert(meta, slot);

        nameClass(klass, meta->className());
        if (!meta->superClass())
            defineRoot(klass);
        defineMembers(klass, meta);
        return klass;
    }
}

VALUE Qross::wrapObject(QObject* object)
{
    if (!object)
        return Qnil;
    return rb_data_typed_object_wrap(classFor(object->metaObject()), new QPointer<QObject>(object), &wrapperType);
}

bool Qross::isWrapper(VALUE value)
{
    return RB_TYPE_P(value, T_DATA) && rb_typeddata_is_kind_of(value, &wrapperType);
}

QObject* Qross::unwrapObject(VALUE value)
{
    return isWrapper(value) ? objectOf(value) : nullptr;
}
