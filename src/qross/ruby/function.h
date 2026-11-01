/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QList>
#include "../core/metafunction.h"
#include "rubyapi.h"

namespace Qross
{
    /**
     * Relays a signal to anything Ruby can call.
     *
     * A relay lives on the Ruby thread, so a signal emitted elsewhere
     * arrives through the event loop of that thread, and it goes away with
     * its sender.
     */
    class RubyFunction : public MetaFunction
    {
        VALUE m_callable;
    public:
        RubyFunction(QObject* sender, const QMetaMethod& signal, VALUE callable);
        ~RubyFunction() override;

        /// \return whether \p callable is the one this relay calls, by Ruby's ==.
        bool matches(VALUE callable) const;

        /// \return the relays of the signals of \p sender.
        static QList<RubyFunction*> relaysOf(const QObject* sender);

        /// Deletes every relay, for use before Ruby shuts down.
        static void deleteAll();
    protected:
        void callback(const QVariantList& args) override;
    };
}
