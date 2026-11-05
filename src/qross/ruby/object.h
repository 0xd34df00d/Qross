/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2005 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QPointer>
#include "../core/object.h"
#include "rubyapi.h"

namespace Qross
{
    class RubyContext;

    /// A Ruby object handed to C++ as an \a Object::Ptr; its methods run with the context that made it current.
    class RubyObject : public Object
    {
        VALUE m_value;
        QPointer<RubyContext> m_context;
    public:
        /// Keeps \p value alive for as long as it lives itself.
        explicit RubyObject(VALUE value);
        ~RubyObject() override;

        VALUE value() const { return m_value; }

        std::expected<QVariant, Error> callMethod(const QString& name, const QVariantList& args = QVariantList()) override;
        QStringList methodNames() override;
    };
}
