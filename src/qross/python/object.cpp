/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "object.h"
#include "gil.h"
#include "interpreter.h"
#include "ref.h"
#include "variant.h"

using namespace Qross;

PythonObject::PythonObject(PyObject* object)
    : m_object(object)
{
    Py_INCREF(m_object);
}

PythonObject::~PythonObject()
{
    // After finalization there is nothing left to release the reference to.
    if (!Py_IsInitialized())
        return;
    const Gil gil;
    Py_DECREF(m_object);
}

PyObject* PythonObject::object() const
{
    Py_INCREF(m_object);
    return m_object;
}

QVariant PythonObject::callMethod(const QString& name, const QVariantList& args)
{
    clearError();
    const Gil gil;

    const Ref method(PyObject_GetAttrString(m_object, name.toUtf8().constData()));
    if (!method || !PyCallable_Check(method.get()))
    {
        PyErr_Clear();
        setError(QStringLiteral("No such method \"%1\"").arg(name));
        return {};
    }

    Ref arguments(PyTuple_New(args.size()));
    for (qsizetype i = 0; i < args.size(); ++i)
    {
        PyObject* const argument = toPython(args[i]);
        if (!argument)
        {
            storeException(*this);
            return {};
        }
        PyTuple_SET_ITEM(arguments.get(), i, argument);
    }

    const Ref result(PyObject_CallObject(method.get(), arguments.get()));
    if (!result)
    {
        storeException(*this);
        return {};
    }
    return toVariant(result.get());
}

QStringList PythonObject::methodNames()
{
    const Gil gil;
    QStringList names;
    const Ref directory(PyObject_Dir(m_object));
    if (!directory)
    {
        PyErr_Clear();
        return names;
    }
    const Py_ssize_t count = PyList_GET_SIZE(directory.get());
    for (Py_ssize_t i = 0; i < count; ++i)
    {
        PyObject* const name = PyList_GET_ITEM(directory.get(), i);
        const QString text = toVariant(name).toString();
        if (text.startsWith(QLatin1String("__")))
            continue;
        const Ref attribute(PyObject_GetAttr(m_object, name));
        if (attribute && PyCallable_Check(attribute.get()))
            names << text;
        PyErr_Clear();
    }
    return names;
}
