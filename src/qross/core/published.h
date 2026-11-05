/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QFlags>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QString>
#include "qrossconfig.h"

namespace Qross
{
    enum ObjectOption
    {
        /// After every run, each signal of the object is connected to the script function of the same name.
        AutoConnectSignals = 0x1,
    };
    Q_DECLARE_FLAGS(ObjectOptions, ObjectOption)
    Q_DECLARE_OPERATORS_FOR_FLAGS(ObjectOptions)

    /// A QObject scripts see under \c name, which defaults to the object name.
    struct Published
    {
        QObject* object = nullptr;
        QString name = {};
        ObjectOptions options = {};
    };

    /**
     * The objects a \a Manager or a \a Script publishes, held weakly: an
     * object the host deletes drops out of the list.
     */
    class QROSSCORE_EXPORT PublishedObjects
    {
        struct Entry
        {
            QPointer<QObject> object;
            QString name;
            ObjectOptions options;
        };

        QList<Entry> m_entries;
    public:
        /// Adds \p object as \p name, or as its object name, replacing an earlier entry of that name.
        void add(QObject* object, const QString& name = {}, ObjectOptions options = {});
        void remove(const QString& name);
        /// The entries whose objects are alive, in insertion order.
        QList<Published> live() const;
    };
}
