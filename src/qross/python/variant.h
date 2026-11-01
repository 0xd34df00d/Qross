/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
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
     * \return the C++ counterpart of \p object. Objects without one, such as
     * class instances, travel as an \a Object::Ptr and come back unchanged.
     */
    QVariant toVariant(PyObject* object);
}
