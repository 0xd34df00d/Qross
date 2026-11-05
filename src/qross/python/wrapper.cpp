/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
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
#include <QtCore/QVarLengthArray>
#include "../core/object.h"
#include "../core/wrapperinterface.h"
#include "context.h"
#include "function.h"
#include "object.h"
#include "ref.h"
#include "variant.h"

using namespace Qross;

namespace
{
    struct ObjectWrapper
    {
        PyObject_HEAD
            QPointer<QObject>* object;
    };

    struct MethodWrapper
    {
        PyObject_HEAD PyObject* owner;
        PyObject* name;
    };

    PyTypeObject* objectType = nullptr;
    PyTypeObject* methodType = nullptr;

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

    QObject* objectOf(PyObject* self)
    {
        auto* const wrapper = reinterpret_cast<ObjectWrapper*>(self);
        return wrapper->object ? wrapper->object->data() : nullptr;
    }

    /// \return the wrapped object, raising RuntimeError when it is gone.
    QObject* liveObject(PyObject* self)
    {
        QObject* const object = objectOf(self);
        if (!object)
            PyErr_SetString(PyExc_RuntimeError, "the wrapped QObject has been deleted");
        return object;
    }

    /// Storage for one slot of a metacall.
    struct Argument
    {
        QVariant value;
        bool variant = false;

        void* data() { return variant ? static_cast<void*>(&value) : value.data(); }
    };

    bool numbers(PyObject* sequence, int count, double* out)
    {
        if (!PySequence_Check(sequence) || PyUnicode_Check(sequence) || PySequence_Size(sequence) != count)
            return false;
        for (int i = 0; i < count; ++i)
        {
            const Ref item(PySequence_GetItem(sequence, i));
            const Ref number(item ? PyNumber_Float(item.get()) : nullptr);
            if (!number)
            {
                PyErr_Clear();
                return false;
            }
            out[i] = PyFloat_AsDouble(number.get());
        }
        return true;
    }

    bool convertGeometry(PyObject* object, QMetaType type, Argument& argument)
    {
        double n[4] = {};
        switch (type.id())
        {
        case QMetaType::QSize:
            if (numbers(object, 2, n))
                argument.value = QSize(int(n[0]), int(n[1]));
            break;
        case QMetaType::QSizeF:
            if (numbers(object, 2, n))
                argument.value = QSizeF(n[0], n[1]);
            break;
        case QMetaType::QPoint:
            if (numbers(object, 2, n))
                argument.value = QPoint(int(n[0]), int(n[1]));
            break;
        case QMetaType::QPointF:
            if (numbers(object, 2, n))
                argument.value = QPointF(n[0], n[1]);
            break;
        case QMetaType::QRect:
            if (numbers(object, 4, n))
                argument.value = QRect(int(n[0]), int(n[1]), int(n[2]), int(n[3]));
            break;
        case QMetaType::QRectF:
            if (numbers(object, 4, n))
                argument.value = QRectF(n[0], n[1], n[2], n[3]);
            break;
        default:
            break;
        }
        return argument.value.isValid();
    }

    /// Fills \p argument for a parameter or property of \p type, raising TypeError when \p object does not fit.
    bool convertArgument(PyObject* object, QMetaType type, Argument& argument)
    {
        if (type == QMetaType::fromType<QVariant>())
        {
            argument.value = toVariant(object);
            argument.variant = true;
            return true;
        }
        if (object == Py_None)
        {
            argument.value = QVariant(type);
            if (argument.value.isValid())
                return true;
            PyErr_Format(PyExc_TypeError, "cannot pass None as %s", type.name());
            return false;
        }
        if (type == QMetaType::fromType<Object::Ptr>())
        {
            argument.value = QVariant::fromValue(Object::Ptr(new PythonObject(object)));
            return true;
        }
        if (isWrapper(object))
        {
            QObject* const wrapped = liveObject(object);
            if (!wrapped)
                return false;
            // A WrapperInterface stands in for what it wraps wherever it does not fit itself.
            auto* const interface = dynamic_cast<WrapperInterface*>(wrapped);
            if (type.flags() & QMetaType::PointerToQObject)
            {
                const QMetaObject* const target = type.metaObject();
                QObject* pointer = wrapped;
                if (target && !target->cast(wrapped))
                {
                    if (!interface)
                    {
                        PyErr_Format(PyExc_TypeError, "expected %s, got %s", type.name(), wrapped->metaObject()->className());
                        return false;
                    }
                    pointer = static_cast<QObject*>(interface->wrappedObject());
                }
                argument.value = QVariant(type, &pointer);
                return true;
            }
            if (interface)
            {
                void* const pointer = interface->wrappedObject();
                argument.value = (type.flags() & QMetaType::IsPointer) ? QVariant(type, &pointer) : QVariant(type, pointer);
                return true;
            }
            PyErr_Format(PyExc_TypeError, "cannot pass a %s as %s", wrapped->metaObject()->className(), type.name());
            return false;
        }
        if (convertGeometry(object, type, argument))
            return true;

        QVariant converted = toVariant(object);
        if (converted.metaType() == type || converted.convert(type))
        {
            argument.value = converted;
            return true;
        }

        // Any other sequence fills a container through the metatype's view.
        argument.value = QVariant(type);
        QSequentialIterable sequence;
        if (PySequence_Check(object) && !PyUnicode_Check(object) && argument.value.isValid() && QMetaType::view(type, argument.value.data(), QMetaType::fromType<QSequentialIterable>(), &sequence))
        {
            const Py_ssize_t count = PySequence_Size(object);
            for (Py_ssize_t i = 0; i < count; ++i)
            {
                const Ref item(PySequence_GetItem(object, i));
                Argument element;
                if (!item || !convertArgument(item.get(), sequence.valueMetaType(), element))
                    return false;
                sequence.addValue(element.value, QSequentialIterable::AtEnd);
            }
            return true;
        }

        PyErr_Format(PyExc_TypeError, "cannot convert %s to %s", Py_TYPE(object)->tp_name, type.name());
        return false;
    }

    QMetaMethod findSignal(const QMetaObject* meta, const char* name)
    {
        for (const int index : indexOf(meta).methods.value(name))
            if (meta->method(index).methodType() == QMetaMethod::Signal)
                return meta->method(index);
        return {};
    }

    PyObject* newMethod(PyObject* owner, PyObject* name)
    {
        auto* const method = reinterpret_cast<MethodWrapper*>(methodType->tp_alloc(methodType, 0));
        if (!method)
            return nullptr;
        Py_INCREF(owner);
        method->owner = owner;
        Py_INCREF(name);
        method->name = name;
        return reinterpret_cast<PyObject*>(method);
    }

    void methodDealloc(PyObject* self)
    {
        auto* const method = reinterpret_cast<MethodWrapper*>(self);
        Py_XDECREF(method->owner);
        Py_XDECREF(method->name);
        PyTypeObject* const type = Py_TYPE(self);
        type->tp_free(self);
        Py_DECREF(type);
    }

    PyObject* methodRepr(PyObject* self)
    {
        auto* const method = reinterpret_cast<MethodWrapper*>(self);
        QObject* const object = objectOf(method->owner);
        return PyUnicode_FromFormat("<method %s.%U of %R>", object ? object->metaObject()->className() : "?", method->name, method->owner);
    }

    PyObject* methodCall(PyObject* self, PyObject* args, PyObject* kwargs)
    {
        auto* const method = reinterpret_cast<MethodWrapper*>(self);
        if (kwargs && PyDict_Size(kwargs) > 0)
        {
            PyErr_SetString(PyExc_TypeError, "Qt methods take no keyword arguments");
            return nullptr;
        }
        QObject* const object = liveObject(method->owner);
        if (!object)
            return nullptr;

        const QMetaObject* const meta = object->metaObject();
        const char* const name = PyUnicode_AsUTF8(method->name);
        const Py_ssize_t count = PyTuple_GET_SIZE(args);

        // The first overload whose arguments convert wins.
        QVarLengthArray<Argument, 8> arguments;
        QMetaMethod chosen;
        Ref lastError;
        for (const int index : indexOf(meta).methods.value(name))
        {
            const QMetaMethod candidate = meta->method(index);
            if (candidate.parameterCount() != count)
                continue;
            arguments.clear();
            arguments.resize(count);
            bool converted = true;
            for (Py_ssize_t i = 0; i < count && converted; ++i)
                converted = convertArgument(PyTuple_GET_ITEM(args, i), candidate.parameterMetaType(int(i)), arguments[i]);
            if (converted)
            {
                chosen = candidate;
                break;
            }
            lastError = Ref(PyErr_GetRaisedException());
        }
        if (!chosen.isValid())
        {
            if (lastError)
                PyErr_SetRaisedException(lastError.release());
            else
                PyErr_Format(PyExc_TypeError, "%s.%s() does not take %zd arguments", meta->className(), name, count);
            return nullptr;
        }

        const QMetaType returnType = chosen.returnMetaType();
        if (!returnType.isValid())
        {
            PyErr_Format(PyExc_TypeError, "the return type %s of %s() is unknown to the metatype system", chosen.typeName(), name);
            return nullptr;
        }
        const bool hasResult = returnType.id() != QMetaType::Void;
        Argument result;
        if (hasResult)
        {
            if (returnType == QMetaType::fromType<QVariant>())
                result.variant = true;
            else
                result.value = QVariant(returnType);
            if (!result.variant && !result.value.isValid())
            {
                PyErr_Format(PyExc_TypeError, "cannot hold a return value of type %s", returnType.name());
                return nullptr;
            }
        }

        QVarLengthArray<void*, 9> pointers(count + 1);
        pointers[0] = hasResult ? result.data() : nullptr;
        for (Py_ssize_t i = 0; i < count; ++i)
            pointers[i + 1] = arguments[i].data();

        Py_BEGIN_ALLOW_THREADS
            QMetaObject::metacall(object, QMetaObject::InvokeMetaMethod, chosen.methodIndex(), pointers.data());
        Py_END_ALLOW_THREADS

            if (!hasResult)
                Py_RETURN_NONE;
        return toPython(result.value);
    }

    PyObject* methodConnect(PyObject* self, PyObject* callable)
    {
        auto* const method = reinterpret_cast<MethodWrapper*>(self);
        QObject* const object = liveObject(method->owner);
        if (!object)
            return nullptr;
        if (!PyCallable_Check(callable))
        {
            PyErr_SetString(PyExc_TypeError, "connect() expects a callable");
            return nullptr;
        }
        const char* const name = PyUnicode_AsUTF8(method->name);
        const QMetaMethod signal = findSignal(object->metaObject(), name);
        if (!signal.isValid())
        {
            PyErr_Format(PyExc_TypeError, "%s.%s is not a signal", object->metaObject()->className(), name);
            return nullptr;
        }
        new PythonFunction(object, signal, callable, PythonContext::current());
        Py_RETURN_NONE;
    }

    PyObject* methodDisconnect(PyObject* self, PyObject* callable)
    {
        auto* const method = reinterpret_cast<MethodWrapper*>(self);
        QObject* const object = liveObject(method->owner);
        if (!object)
            return nullptr;
        const char* const name = PyUnicode_AsUTF8(method->name);
        const QList<QObject*> children = object->children();
        for (QObject* const child : children)
        {
            auto* const relay = dynamic_cast<PythonFunction*>(child);
            if (relay && relay->signal().name() == name && relay->matches(callable))
                delete relay;
        }
        Py_RETURN_NONE;
    }

    PyMethodDef methodMethods[] = {
        { "connect", methodConnect, METH_O, "connect(callable) calls back whenever the signal is emitted" },
        { "disconnect", methodDisconnect, METH_O, "disconnect(callable) undoes connect(callable)" },
        { nullptr, nullptr, 0, nullptr },
    };

    PyType_Slot methodSlots[] = {
        { Py_tp_dealloc, reinterpret_cast<void*>(methodDealloc) },
        { Py_tp_call, reinterpret_cast<void*>(methodCall) },
        { Py_tp_repr, reinterpret_cast<void*>(methodRepr) },
        { Py_tp_methods, methodMethods },
        { 0, nullptr },
    };

    PyType_Spec methodSpec = {
        "qross.Method",
        sizeof(MethodWrapper),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_IMMUTABLETYPE | Py_TPFLAGS_DISALLOW_INSTANTIATION,
        methodSlots,
    };

    void objectDealloc(PyObject* self)
    {
        delete reinterpret_cast<ObjectWrapper*>(self)->object;
        PyTypeObject* const type = Py_TYPE(self);
        type->tp_free(self);
        Py_DECREF(type);
    }

    PyObject* objectGetAttr(PyObject* self, PyObject* nameObject)
    {
        const char* const name = PyUnicode_AsUTF8(nameObject);
        if (!name)
            return nullptr;
        if (name[0] == '_' && name[1] == '_')
            return PyObject_GenericGetAttr(self, nameObject);

        QObject* const object = liveObject(self);
        if (!object)
            return nullptr;
        const QMetaObject* const meta = object->metaObject();

        const int propertyIndex = meta->indexOfProperty(name);
        if (propertyIndex >= 0)
        {
            const QMetaProperty property = meta->property(propertyIndex);
            if (!property.isReadable())
            {
                PyErr_Format(PyExc_AttributeError, "property '%s' is not readable", name);
                return nullptr;
            }
            return toPython(property.read(object));
        }

        const Index& index = indexOf(meta);
        if (index.methods.contains(name))
            return newMethod(self, nameObject);
        if (const auto found = index.enums.constFind(name); found != index.enums.cend())
            return PyLong_FromLong(found.value());
        if (object->dynamicPropertyNames().contains(name))
            return toPython(object->property(name));
        return PyObject_GenericGetAttr(self, nameObject);
    }

    int objectSetAttr(PyObject* self, PyObject* nameObject, PyObject* value)
    {
        const char* const name = PyUnicode_AsUTF8(nameObject);
        if (!name)
            return -1;
        QObject* const object = liveObject(self);
        if (!object)
            return -1;
        if (!value)
        {
            PyErr_Format(PyExc_AttributeError, "cannot delete '%s'", name);
            return -1;
        }

        const QMetaObject* const meta = object->metaObject();
        const int propertyIndex = meta->indexOfProperty(name);
        if (propertyIndex < 0 && !object->dynamicPropertyNames().contains(name))
        {
            PyErr_Format(PyExc_AttributeError, "%s has no property '%s'", meta->className(), name);
            return -1;
        }

        Argument argument;
        if (propertyIndex < 0)
        {
            if (!convertArgument(value, QMetaType::fromType<QVariant>(), argument))
                return -1;
            object->setProperty(name, argument.value);
            return 0;
        }

        const QMetaProperty property = meta->property(propertyIndex);
        if (!property.isWritable())
        {
            PyErr_Format(PyExc_AttributeError, "property '%s' is not writable", name);
            return -1;
        }
        if (!convertArgument(value, property.metaType(), argument))
            return -1;
        if (!property.write(object, argument.value))
        {
            PyErr_Format(PyExc_AttributeError, "setting '%s' failed", name);
            return -1;
        }
        return 0;
    }

    PyObject* objectRepr(PyObject* self)
    {
        QObject* const object = objectOf(self);
        if (!object)
            return PyUnicode_FromString("<deleted QObject>");
        const QByteArray name = object->objectName().toUtf8();
        return PyUnicode_FromFormat("<%s \"%s\" at %p>", object->metaObject()->className(), name.constData(), static_cast<void*>(object));
    }

    PyObject* objectCompare(PyObject* self, PyObject* other, int op)
    {
        if ((op != Py_EQ && op != Py_NE) || !isWrapper(other))
            Py_RETURN_NOTIMPLEMENTED;
        const bool equal = objectOf(self) == objectOf(other);
        return PyBool_FromLong(op == Py_EQ ? equal : !equal);
    }

    Py_hash_t objectHash(PyObject* self)
    {
        const auto hash = Py_hash_t(reinterpret_cast<quintptr>(objectOf(self)) >> 4);
        return hash == -1 ? -2 : hash;
    }

    PyObject* objectProperty(PyObject* self, PyObject* nameObject)
    {
        QObject* const object = liveObject(self);
        const char* const name = PyUnicode_AsUTF8(nameObject);
        if (!object || !name)
            return nullptr;
        return toPython(object->property(name));
    }

    PyObject* objectSetProperty(PyObject* self, PyObject* args)
    {
        PyObject* nameObject = nullptr;
        PyObject* value = nullptr;
        if (!PyArg_ParseTuple(args, "UO:setProperty", &nameObject, &value))
            return nullptr;
        QObject* const object = liveObject(self);
        if (!object)
            return nullptr;
        const char* const name = PyUnicode_AsUTF8(nameObject);
        const int propertyIndex = object->metaObject()->indexOfProperty(name);
        Argument argument;
        const QMetaType type = propertyIndex >= 0 ? object->metaObject()->property(propertyIndex).metaType() : QMetaType::fromType<QVariant>();
        if (!convertArgument(value, type, argument))
            return nullptr;
        object->setProperty(name, argument.value);
        Py_RETURN_NONE;
    }

    PyObject* objectClassName(PyObject* self, PyObject*)
    {
        QObject* const object = liveObject(self);
        return object ? PyUnicode_FromString(object->metaObject()->className()) : nullptr;
    }

    PyObject* objectDir(PyObject* self, PyObject*)
    {
        QObject* const object = liveObject(self);
        if (!object)
            return nullptr;
        Ref names(PyList_New(0));
        const auto add = [&names](const QByteArray& name) {
            const Ref item(PyUnicode_FromStringAndSize(name.constData(), name.size()));
            PyList_Append(names.get(), item.get());
        };
        const QMetaObject* const meta = object->metaObject();
        for (int i = 0; i < meta->propertyCount(); ++i)
            add(meta->property(i).name());
        for (const QByteArray& name : object->dynamicPropertyNames())
            add(name);
        const Index& index = indexOf(meta);
        for (auto it = index.methods.cbegin(); it != index.methods.cend(); ++it)
            add(it.key());
        for (auto it = index.enums.cbegin(); it != index.enums.cend(); ++it)
            add(it.key());
        for (const char* name : { "property", "setProperty", "className" })
            add(name);
        return names.release();
    }

    PyMethodDef objectMethods[] = {
        { "property", objectProperty, METH_O, "property(name) -> the value of a static or dynamic property" },
        { "setProperty", objectSetProperty, METH_VARARGS, "setProperty(name, value) sets a static or dynamic property" },
        { "className", objectClassName, METH_NOARGS, "className() -> the C++ class name" },
        { "__dir__", objectDir, METH_NOARGS, nullptr },
        { nullptr, nullptr, 0, nullptr },
    };

    PyType_Slot objectSlots[] = {
        { Py_tp_dealloc, reinterpret_cast<void*>(objectDealloc) },
        { Py_tp_getattro, reinterpret_cast<void*>(objectGetAttr) },
        { Py_tp_setattro, reinterpret_cast<void*>(objectSetAttr) },
        { Py_tp_repr, reinterpret_cast<void*>(objectRepr) },
        { Py_tp_richcompare, reinterpret_cast<void*>(objectCompare) },
        { Py_tp_hash, reinterpret_cast<void*>(objectHash) },
        { Py_tp_methods, objectMethods },
        { 0, nullptr },
    };

    PyType_Spec objectSpec = {
        "qross.QObject",
        sizeof(ObjectWrapper),
        0,
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_IMMUTABLETYPE | Py_TPFLAGS_DISALLOW_INSTANTIATION,
        objectSlots,
    };

    bool ensureTypes()
    {
        if (!objectType)
            objectType = reinterpret_cast<PyTypeObject*>(PyType_FromSpec(&objectSpec));
        if (!methodType)
            methodType = reinterpret_cast<PyTypeObject*>(PyType_FromSpec(&methodSpec));
        return objectType && methodType;
    }
}

PyObject* Qross::wrapObject(QObject* object)
{
    if (!object)
        Py_RETURN_NONE;
    if (!ensureTypes())
        return nullptr;
    auto* const wrapper = reinterpret_cast<ObjectWrapper*>(objectType->tp_alloc(objectType, 0));
    if (!wrapper)
        return nullptr;
    wrapper->object = new QPointer<QObject>(object);
    return reinterpret_cast<PyObject*>(wrapper);
}

bool Qross::isWrapper(PyObject* object)
{
    return objectType && PyObject_TypeCheck(object, objectType);
}

QObject* Qross::unwrapObject(PyObject* object)
{
    return isWrapper(object) ? objectOf(object) : nullptr;
}
