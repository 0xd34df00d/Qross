/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2007 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006-2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QObject>
#include "rubyapi.h"

namespace Qross
{
    /**
     * \return a wrapper for \p object, or nil for null.
     *
     * Wrappers are instances of one Ruby class per QMetaObject, named
     * after the C++ class under \c Qross where the name allows it and
     * inheriting the way the C++ classes do, down to \c Qross::QObject.
     * Slots, invokables and signals are methods, and calling a signal
     * emits it. Properties come with \c name and \c name= accessors,
     * dynamic properties answer through method_missing, and enum keys are
     * methods as well as constants of the class. \c Qross::QObject adds
     * property(), setProperty(), className(), connect() and disconnect(),
     * compares and hashes by the wrapped object, and raises RuntimeError
     * once that object is gone.
     */
    VALUE wrapObject(QObject* object);

    /// \return whether \p value is a wrapper, alive or not.
    bool isWrapper(VALUE value);

    /// \return the wrapped object, or null if \p value is no wrapper or its object is gone.
    QObject* unwrapObject(VALUE value);
}
