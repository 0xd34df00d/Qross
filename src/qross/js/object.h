/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QPointer>
#include <QtQml/QJSValue>
#include "../core/object.h"

class QJSEngine;

namespace Qross
{
    /// The error \p thrown stands for, which may be any JavaScript value; \p trace is used when it has no stack.
    Error errorOf(const QJSValue& thrown, const QStringList& trace = {});

    /**
     * A JavaScript object handed to C++ as an \a Object::Ptr.
     *
     * The engine converts slot arguments of types it does not know through
     * QMetaType, so a converter registered once per process turns a QJSValue
     * into an \a Object::Ptr. A QJSValue does not know its engine, which the
     * converter needs; prepareEngine() therefore gives every object of an
     * engine a hidden way back to it.
     *
     * Once the engine is gone, calls fail with an error instead of crashing.
     */
    class JsObject : public Object
    {
        QPointer<QJSEngine> m_engine;
        QJSValue m_value;
    public:
        JsObject(QJSEngine* engine, const QJSValue& value);

        static void registerConverters();
        static void prepareEngine(QJSEngine& engine);

        std::expected<QVariant, Error> callMethod(const QString& name, const QVariantList& args = QVariantList()) override;
        QStringList methodNames() override;
    private:
        static Object::Ptr fromValue(const QJSValue& value);
    };
}
