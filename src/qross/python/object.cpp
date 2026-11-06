/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "object.h"
#include "context.h"
#include "gil.h"
#include "interpreter.h"
#include "ref.h"
#include "variant.h"

using namespace Qross;

PythonObject::PythonObject(PyObject* object)
    : m_object(object)
    , m_context(PythonContext::current())
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

std::expected<QVariant, Error> PythonObject::callMethod(const QString& name, const QVariantList& args)
{
    const Gil gil;
    const PythonContext::Scope scope(m_context);

    const Ref method(PyObject_GetAttrString(m_object, name.toUtf8().constData()));
    if (!method || !PyCallable_Check(method.get()))
    {
        PyErr_Clear();
        return std::unexpected(Error { QStringLiteral("No such method \"%1\"").arg(name) });
    }

    Ref arguments(PyTuple_New(args.size()));
    for (qsizetype i = 0; i < args.size(); ++i)
    {
        PyObject* const argument = toPython(args[i]);
        if (!argument)
            return std::unexpected(takeException());
        PyTuple_SET_ITEM(arguments.get(), i, argument);
    }

    const Ref result(PyObject_CallObject(method.get(), arguments.get()));
    const auto value = result ? toVariant(result.get()) : std::nullopt;
    if (!value)
        return std::unexpected(takeException());
    return *value;
}

QStringList PythonObject::methodNames()
{
    const Gil gil;
    const PythonContext::Scope scope(m_context);
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
        if (!PyUnicode_Check(name))
            continue;
        const QString text = toString(name);
        if (text.startsWith(QLatin1String("__")))
            continue;
        const Ref attribute(PyObject_GetAttr(m_object, name));
        if (attribute && PyCallable_Check(attribute.get()))
            names << text;
        PyErr_Clear();
    }
    return names;
}
