/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2007 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QList>
#include <QtCore/QPointer>
#include "../core/context.h"
#include "rubyapi.h"

namespace Qross
{
    class RubyFunction;

    /**
     * Runs the code of a \a Script with the script as \c self.
     *
     * Every execute() starts afresh: the code runs in a binding of its own
     * where \c self is a wrapper of the script, so methods defined at the
     * top level are the functions of the script and classes defined there
     * belong to it alone. The objects of the \a Manager (\c Qross among
     * them) and of the script are its constants where their names allow
     * it, and methods of \c self in any case. The binding
     * keeps local variables across evaluate() calls. The directory of the
     * script file is appended to the load path, so that scripts can
     * require their neighbours.
     *
     * Objects stay owned by C++; a wrapper of a deleted object raises
     * RuntimeError.
     */
    class RubyContext : public Context
    {
        VALUE m_self = Qnil;
        VALUE m_binding = Qnil;
        QList<QPointer<RubyFunction>> m_connections;
    public:
        RubyContext(Interpreter* interpreter, Script* script);
        ~RubyContext() override;

        std::expected<void, Error> execute() override;
        QStringList functionNames() override;
        std::expected<QVariant, Error> callFunction(const QString& name, const QVariantList& args = QVariantList()) override;
        std::expected<QVariant, Error> evaluate(const QByteArray& code) override;
    private:
        std::expected<void, Error> prepare();
        std::expected<void, Error> ensureContext();
        void resetContext();
        void publish(VALUE accessors, const QString& name, QObject* object);
        void appendLoadPath();
        std::expected<QVariant, Error> run(const QByteArray& code, const QString& file);
        VALUE functions();
        void connectSignals();
    };
}
