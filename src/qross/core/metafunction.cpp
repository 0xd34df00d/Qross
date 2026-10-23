/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2006 Ian Reinhart Geiser <geiseri@kde.org>
 * Copyright (C) 2005-2006 Matt Broadstone <mbroadst@gmail.com>
 * Copyright (C) 2005-2006 Richard J. Moore <rich@kde.org>
 * Copyright (C) 2005-2006 Erik L. Bunce <kde@bunce.us>
 * Copyright (C) 2005-2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "metafunction.h"
#include <utility>
#include "qrossconfig.h"

namespace Qross
{
    namespace
    {
        // Qt hands this index back to qt_metacall() unchanged and stores it in
        // sixteen bits. No metaobject has that many methods, so it cannot
        // collide with a real one, moc-generated or not.
        constexpr int VirtualSlotIndex = 0xffff;

        QMetaMethod findSignal(QObject* sender, const QByteArray& signature)
        {
            if (!sender)
                return {};

            const auto* meta = sender->metaObject();
            return meta->method(meta->indexOfSignal(QMetaObject::normalizedSignature(signature.constData())));
        }
    }

    MetaFunction::MetaFunction(QObject* sender, const QMetaMethod& signal, Qt::ConnectionType type)
        : m_sender(sender)
        , m_signal(signal)
    {
        if (!sender)
        {
            qrosswarning(QStringLiteral("MetaFunction: no sender to connect to"));
            return;
        }

        if (!signal.isValid() || signal.methodType() != QMetaMethod::Signal)
        {
            qrosswarning(QString("MetaFunction: \"%1\" is not a signal")
                    .arg(QString::fromLatin1(signal.methodSignature())));
            return;
        }

        if (!sender->metaObject()->inherits(signal.enclosingMetaObject()))
        {
            qrosswarning(QString("MetaFunction: signal \"%1\" does not belong to the class of %2")
                    .arg(QString::fromLatin1(signal.methodSignature()), QString::fromLatin1(sender->metaObject()->className())));
            return;
        }

        m_connection = QMetaObject::connect(sender, signal.methodIndex(), this, VirtualSlotIndex, static_cast<int>(type), nullptr);
    }

    MetaFunction::MetaFunction(QObject* sender, const QByteArray& signature, Qt::ConnectionType type)
        : MetaFunction(sender, findSignal(sender, signature), type)
    {
    }

    MetaFunction::~MetaFunction()
    {
        disconnectSignal();
    }

    bool MetaFunction::isConnected() const
    {
        return m_sender && static_cast<bool>(m_connection);
    }

    void MetaFunction::disconnectSignal()
    {
        if (const auto connection = std::exchange(m_connection, {}))
            QObject::disconnect(connection);
    }

    QObject* MetaFunction::signalSender() const
    {
        return m_sender;
    }

    QMetaMethod MetaFunction::signal() const
    {
        return m_signal;
    }

    int MetaFunction::qt_metacall(QMetaObject::Call call, int id, void** args)
    {
        if (call == QMetaObject::InvokeMetaMethod && id == VirtualSlotIndex)
        {
            dispatch(args);
            return -1;
        }
        return QObject::qt_metacall(call, id, args);
    }

    void MetaFunction::dispatch(void** args)
    {
        const int count = m_signal.parameterCount();
        QVariantList arguments;
        arguments.reserve(count);
        for (int i = 0; i < count; ++i)
        {
            // args[0] is the return value slot; the arguments start at 1.
            const QMetaType type = m_signal.parameterMetaType(i);
            if (!type.isValid())
            {
                qrosswarning(QString("MetaFunction: argument %1 of \"%2\" has a type unknown to QMetaType")
                        .arg(i)
                        .arg(QString::fromLatin1(m_signal.methodSignature())));
                arguments.append(QVariant());
                continue;
            }
            arguments.append(QVariant(type, args[i + 1]));
        }
        callback(arguments);
    }
}
