/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QString>

namespace Qross
{
    /// What a script raised, or why it could not run at all.
    struct Error
    {
        QString message;
        QString trace = {};
        int line = -1;

        /// The message, with the trace on the following lines when there is one.
        QString toString() const
        {
            return trace.isEmpty() ? message : message + QLatin1Char('\n') + trace;
        }
    };
}
