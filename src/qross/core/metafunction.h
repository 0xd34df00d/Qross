/***************************************************************************
 * metafunction.h
 * This file is part of the KDE project
 * copyright (C)2005-2006 Ian Reinhart Geiser <geiseri@kde.org>
 * copyright (C)2005-2006 Matt Broadstone     <mbroadst@gmail.com>
 * copyright (C)2005-2006 Richard J. Moore    <rich@kde.org>
 * copyright (C)2005-2006 Erik L. Bunce       <kde@bunce.us>
 * copyright (C)2005-2007 by Sebastian Sauer  <mail@dipe.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 ***************************************************************************/

#pragma once

#include "qross_export.h"

#include <QtCore/QMetaMethod>
#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QVariant>

namespace Qross
{
    /**
     * Receives a Qt signal whose signature is only known at runtime and
     * forwards its arguments to callback().
     *
     * Backends subclass this to connect signals of published QObjects to
     * script functions. The connection goes through QMetaObject::connect to
     * a slot index no metaobject contains, and the invocation arrives in
     * qt_metacall(), the way QSignalSpy works, so nothing has to be built
     * with QMetaObjectBuilder.
     */
    class QROSSCORE_EXPORT MetaFunction : public QObject
    {
        QPointer<QObject> m_sender;
        QMetaMethod m_signal;
        QMetaObject::Connection m_connection;
    public:
        /**
         * Connects to \p signal of \p sender right away. isConnected() tells
         * whether that worked: a null sender, a method that is not a signal
         * or a signal of another class are refused.
         */
        MetaFunction(QObject* sender, const QMetaMethod& signal, Qt::ConnectionType type = Qt::AutoConnection);

        /**
         * Looks the signal up by its \p signature, normalizing it first.
         */
        MetaFunction(QObject* sender, const QByteArray& signature, Qt::ConnectionType type = Qt::AutoConnection);

        ~MetaFunction() override;

        /// \return true while the connection to the signal is alive.
        bool isConnected() const;

        /// Disconnects from the signal; callback() is not called any more.
        void disconnectSignal();

        /// \return the object whose signal is relayed, or null once it is gone.
        QObject* signalSender() const;

        /// \return the relayed signal.
        QMetaMethod signal() const;

        /// \internal receives the invocation of the virtual slot.
        int qt_metacall(QMetaObject::Call call, int id, void** args) override;
    protected:
        /**
         * Called each time the signal is emitted, with its arguments as
         * QVariants in declaration order. An argument of a type unknown to
         * QMetaType arrives as an invalid QVariant.
         */
        virtual void callback(const QVariantList& args) = 0;
    private:
        void dispatch(void** args);
    };
}
