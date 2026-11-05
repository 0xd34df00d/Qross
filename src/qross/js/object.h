/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QPointer>
#include <QtQml/QJSValue>
#include <QtQml/qqmlregistration.h>
#include "../core/object.h"

class QJSEngine;

namespace Qross
{
    /// The error \p thrown stands for, which may be any JavaScript value; \p trace is used when it has no stack.
    Error errorOf(const QJSValue& thrown, const QStringList& trace = {});

    /// \return the failure of the call that just ended in \p engine, which threw or was interrupted, if any.
    std::expected<void, Error> checkCall(QJSEngine& engine);

    /**
     * A JavaScript object handed to C++ as an \a Object::Ptr.
     *
     * The engine converts slot arguments of types it does not know through
     * QMetaType, so a converter registered once per process turns a QJSValue
     * into an \a Object::Ptr. A QJSValue does not know its engine, which the
     * converter needs; prepareEngine() therefore gives every object of an
     * engine a hidden way back to it. On the way back the engine consults
     * no converter, so an \a Object::Ptr reaches a script as an
     * \a ObjectValue.
     *
     * Once the engine is gone, calls fail with an error instead of crashing.
     */
    class JsObject : public Object
    {
        QPointer<QJSEngine> m_engine;
        QJSValue m_value;
    public:
        JsObject(QJSEngine* engine, const QJSValue& value);

        /// Registers the conversions from JavaScript and the value type for the way back, once per process.
        static void registerTypes();
        static void prepareEngine(QJSEngine& engine);

        QJSValue value() const { return m_value; }

        std::expected<QVariant, Error> callMethod(const QString& name, const QVariantList& args = QVariantList()) override;
        QStringList methodNames() override;
    private:
        static Object::Ptr fromValue(const QJSValue& value);
    };

    /**
     * What an \a Object::Ptr is in JavaScript: the engine wraps a C++ value
     * of a registered value type in an object with the type's methods, and
     * substitutes nothing else for a C++ type, so the object itself cannot
     * come back the way it does in the other backends.
     */
    struct ObjectValue : private Object::Ptr
    {
        Q_GADGET
        QML_VALUE_TYPE(scriptObject)
        QML_FOREIGN(Qross::Object::Ptr)
        QML_EXTENDED(Qross::ObjectValue)
    public:
        /// \return the JavaScript value the object was made from, null for an empty pointer and undefined for an object of another backend.
        Q_INVOKABLE QJSValue value() const;
    };
}
