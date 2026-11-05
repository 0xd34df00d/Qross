/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <QtCore/QPointer>
#include "../core/object.h"

namespace Qross
{
    class PythonContext;

    /// A Python object handed to C++ as an \a Object::Ptr; its methods run with the context that made it current.
    class PythonObject : public Object
    {
        PyObject* m_object;
        QPointer<PythonContext> m_context;
    public:
        /// Keeps its own reference to \p object.
        explicit PythonObject(PyObject* object);
        ~PythonObject() override;

        /// \return a new reference.
        PyObject* object() const;

        std::expected<QVariant, Error> callMethod(const QString& name, const QVariantList& args = QVariantList()) override;
        QStringList methodNames() override;
    };
}
