/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <optional>
#include <QtCore/QVariant>

namespace Qross
{
    /**
     * \return a new reference to the Python counterpart of \p value, or null
     * with a TypeError raised when there is none. Pointers to QObjects become
     * wrappers, after the type handlers of the \a Manager had their say.
     */
    PyObject* toPython(const QVariant& value);

    /**
     * \return the C++ counterpart of \p object, or nothing with the exception
     * raised when a value on the way has none, such as an integer beyond
     * double or a key whose str() fails. Objects without a counterpart of
     * their own, such as class instances, travel as an \a Object::Ptr and
     * come back unchanged.
     */
    std::optional<QVariant> toVariant(PyObject* object);

    /// \return the text of the str \p object, lone surrogates included.
    QString toString(PyObject* object);
}
