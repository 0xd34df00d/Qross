/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2008 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QVariant>
#include "call.h"

namespace Qross
{
    /**
     * \return the Ruby counterpart of \p value, or a TypeError when there
     * is none. Pointers to QObjects become wrappers, after the type handlers
     * of the \a Manager had their say.
     *
     * Strings come back in UTF-8 and byte arrays as binary strings. Sizes,
     * points and rectangles are arrays of numbers, dates are Date objects
     * when the date library is loaded, date-times are Time objects, and
     * times of day are ISO strings, since Ruby has no type for them.
     */
    Result toRuby(const QVariant& value);

    /**
     * \return the C++ counterpart of \p value. Values without one, such as
     * instances of script classes, travel as an \a Object::Ptr and come
     * back unchanged.
     */
    QVariant toVariant(VALUE value);

    /// \return the text of a String or Symbol \p value in UTF-8; anything else gives an empty string.
    QString toString(VALUE value);

    /// \return a UTF-8 String with the text of \p string.
    VALUE fromString(const QString& string);
}
