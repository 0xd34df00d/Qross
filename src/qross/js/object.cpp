/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "object.h"
#include <QtCore/QMetaType>
#include <QtQml/QJSEngine>
#include <QtQml/QJSManagedValue>
#include <QtQml/qqml.h>

using namespace Qross;

namespace
{
    const auto EngineLookup = QStringLiteral("__qrossEngine");
}

Error Qross::errorOf(const QJSValue& thrown, const QStringList& trace)
{
    if (thrown.isError())
        return Error { thrown.toString(), thrown.property(QStringLiteral("stack")).toString(), thrown.property(QStringLiteral("lineNumber")).toInt() };
    return Error { thrown.toString(), trace.join(QLatin1Char('\n')) };
}

std::expected<void, Error> Qross::checkCall(QJSEngine& engine)
{
    if (engine.hasError())
        return std::unexpected(errorOf(engine.catchError()));
    // An interrupted call ends without an exception; the error object is the one evaluate() gets from the engine.
    if (engine.isInterrupted())
        return std::unexpected(errorOf(engine.newErrorObject(QJSValue::GenericError, QStringLiteral("Interrupted"))));
    return {};
}

JsObject::JsObject(QJSEngine* engine, const QJSValue& value)
    : m_engine(engine)
    , m_value(value)
{
}

void JsObject::registerTypes()
{
    if (QMetaType::hasRegisteredConverterFunction<QJSValue, Object::Ptr>())
        return;
    QMetaType::registerConverter<QJSValue, Object::Ptr>(&JsObject::fromValue);
    QMetaType::registerConverter<std::nullptr_t, Object::Ptr>([](std::nullptr_t) { return Object::Ptr(); });
    qmlRegisterTypesAndRevisions<ObjectValue>("Qross", 1);
}

QJSValue ObjectValue::value() const
{
    if (isNull())
        return QJSValue(QJSValue::NullValue);
    const auto* const js = dynamic_cast<const JsObject*>(data());
    return js ? js->value() : QJSValue();
}

void JsObject::prepareEngine(QJSEngine& engine)
{
    // The marker is wrapped by this engine only, so qjsEngine() finds the
    // engine from it. The closure keeps the wrapper alive.
    auto* const marker = new QObject(&engine);
    const QJSValue plant = engine.evaluate(QStringLiteral(R"js(
        (function(name, marker) {
            Object.defineProperty(Object.prototype, name, { value: function() { return marker; } });
        })
    )js"));
    plant.call({ EngineLookup, engine.newQObject(marker) });
}

Object::Ptr JsObject::fromValue(const QJSValue& value)
{
    const QJSValue lookup = value.property(EngineLookup);
    QObject* const marker = lookup.isCallable() ? lookup.call().toQObject() : nullptr;
    QJSEngine* const engine = marker ? qjsEngine(marker) : nullptr;
    if (!engine)
    {
        qrosswarning(QStringLiteral("JsObject: cannot find the engine of %1").arg(value.toString()));
        return {};
    }
    return Object::Ptr(new JsObject(engine, value));
}

std::expected<QVariant, Error> JsObject::callMethod(const QString& name, const QVariantList& args)
{
    if (!m_engine)
        return std::unexpected(Error { QStringLiteral("JsObject: the engine of this object is gone") });

    const QJSValue method = m_value.property(name);
    if (!method.isCallable())
        return std::unexpected(Error { QStringLiteral("JsObject: no method \"%1\"").arg(name) });

    QJSValueList arguments;
    for (const QVariant& arg : args)
        arguments << m_engine->toScriptValue(arg);

    const QJSValue result = QJSManagedValue(method, m_engine).callWithInstance(m_value, arguments);
    if (const auto ended = checkCall(*m_engine); !ended)
        return std::unexpected(ended.error());
    return result.toVariant();
}

QStringList JsObject::methodNames()
{
    if (!m_engine)
        return {};

    // Own and inherited methods, except what every object inherits.
    const QJSValue collect = m_engine->evaluate(QStringLiteral(R"js(
        (function(object) {
            var names = [];
            for (var p = object; p && p !== Object.prototype; p = Object.getPrototypeOf(p))
                Object.getOwnPropertyNames(p).forEach(function(name) {
                    if (name !== 'constructor' && names.indexOf(name) < 0 && typeof object[name] === 'function')
                        names.push(name);
                });
            return names;
        })
    )js"));
    return collect.call({ m_value }).toVariant().toStringList();
}
