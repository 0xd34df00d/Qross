/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <expected>
#include <initializer_list>
#include <QtCore/QString>
#include "rubyapi.h"

namespace Qross
{
    /**
     * A Ruby value, or the exception that stands in for it.
     *
     * Ruby reports errors by unwinding the stack past C++ destructors, so
     * nothing in this backend raises while it holds C++ objects. Functions
     * return a Result instead, and the few entry points Ruby calls raise
     * what they got back once their locals are gone.
     */
    using Result = std::expected<VALUE, VALUE>;

    /// \return a failure carrying a new exception of \p type.
    inline std::unexpected<VALUE> fail(VALUE type, const QString& message)
    {
        const QByteArray utf8 = message.toUtf8();
        return std::unexpected(rb_exc_new_str(type, rb_utf8_str_new(utf8.constData(), utf8.size())));
    }

    /// Runs \p function under rb_protect, turning whatever it raises into the error.
    Result runProtected(VALUE (*function)(VALUE), VALUE argument);

    /// Calls \p method on \p receiver, turning whatever it raises into the error.
    Result callProtected(VALUE receiver, ID method, long argc, const VALUE* argv);

    inline Result callProtected(VALUE receiver, ID method, std::initializer_list<VALUE> args)
    {
        return callProtected(receiver, method, long(args.size()), args.begin());
    }
}
