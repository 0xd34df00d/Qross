/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <QtCore/QObject>

namespace Qross
{
    /**
     * \return a new reference to a wrapper of \p object, or None for null.
     *
     * The wrapper exposes properties as attributes, slots, invokables and
     * signals as callables with \c connect() and \c disconnect(), enum keys
     * as attributes, and has \c property(), \c setProperty() and
     * \c className(). Wrappers compare equal when they wrap the same object,
     * and raise RuntimeError once that object is gone.
     */
    PyObject* wrapObject(QObject* object);

    /// \return whether \p object is a wrapper, alive or not.
    bool isWrapper(PyObject* object);

    /// \return the wrapped object, or null if \p object is no wrapper or its object is gone.
    QObject* unwrapObject(PyObject* object);
}
