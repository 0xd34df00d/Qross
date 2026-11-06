/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007-2008 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "context.h"
#include <QtCore/QMetaEnum>
#include <QtCore/QMetaMethod>
#include <QtCore/QSet>
#include <QtQml/QJSManagedValue>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>
#include "../core/script.h"
#include "object.h"

using namespace Qross;

namespace
{
    // Loading any QML that imports the module registers its value types,
    // QModelIndex among them, for the whole process; nothing else does.
    void importQtQml(QQmlEngine& engine)
    {
        QQmlComponent component(&engine);
        component.setData("import QtQml\nQtObject {}", {});
    }
}

JsContext::JsContext(Interpreter* interpreter, Script* script)
    : Context(interpreter, script)
{
}

JsContext::~JsContext() = default;

QObject* JsContext::engine()
{
    return &ensureEngine();
}

QQmlEngine& JsContext::ensureEngine()
{
    return m_engine ? *m_engine : createEngine();
}

QQmlEngine& JsContext::createEngine()
{
    m_engine = std::make_unique<QQmlEngine>();
    if (script()->option(QStringLiteral("qml"), true).toBool())
        importQtQml(*m_engine);
    JsObject::prepareEngine(*m_engine);

    QJSValue global = m_engine->globalObject();
    publish(global, QStringLiteral("self"), script());
    for (const Published& published : script()->publishedObjects())
        publish(global, published.name, published.object);
    return *m_engine;
}

void JsContext::publish(QJSValue& global, const QString& name, QObject* object)
{
    QJSEngine::setObjectOwnership(object, QJSEngine::CppOwnership);
    QJSValue wrapper = m_engine->newQObject(object);

    const QMetaObject* const meta = object->metaObject();
    for (int i = 0; i < meta->enumeratorCount(); ++i)
    {
        const QMetaEnum enumerator = meta->enumerator(i);
        for (int j = 0; j < enumerator.keyCount(); ++j)
            wrapper.setProperty(QString::fromLatin1(enumerator.key(j)), enumerator.value(j));
    }

    global.setProperty(name, wrapper);
}

std::expected<void, Error> JsContext::execute()
{
    QQmlEngine& engine = createEngine();

    // A shebang is not JavaScript; its newline stays so that line numbers do.
    QString code = QString::fromUtf8(script()->code());
    if (code.startsWith(QLatin1String("#!")))
    {
        const qsizetype eol = code.indexOf(QLatin1Char('\n'));
        code.remove(0, eol < 0 ? code.size() : eol);
    }

    // The trace is empty exactly when nothing was thrown: even a syntax
    // error carries the frame of its location. An Error object is a value
    // like any other.
    QStringList trace;
    const QJSValue result = engine.evaluate(code, script()->name(), 1, &trace);
    if (!trace.isEmpty() || engine.isInterrupted())
        return std::unexpected(errorOf(result, trace));

    connectSignals(engine);
    return {};
}

void JsContext::connectSignals(QQmlEngine& engine)
{
    const QJSValue global = engine.globalObject();
    for (const Published& published : script()->publishedObjects())
    {
        if (!(published.options & AutoConnectSignals))
            continue;
        QObject* const sender = published.object;

        // Overloads share a name and a wrapper property, so one connection per name.
        QSet<QString> connected;
        const QJSValue wrapper = global.property(published.name);
        const QMetaObject* const meta = sender->metaObject();
        for (int i = 0; i < meta->methodCount(); ++i)
        {
            const QMetaMethod method = meta->method(i);
            if (method.methodType() != QMetaMethod::Signal)
                continue;
            const QString name = QString::fromLatin1(method.name());
            const QJSValue handler = global.property(name);
            if (!handler.isCallable() || connected.contains(name))
                continue;
            connected.insert(name);
            QJSValue signal = wrapper.property(name);
            signal.property(QStringLiteral("connect")).callWithInstance(signal, { handler });
        }
    }
}

std::expected<QStringList, Error> JsContext::functionNames()
{
    const QJSValue names = ensureEngine().evaluate(QStringLiteral(R"js(
        Object.keys(this).filter(function(name) { return typeof this[name] === 'function'; }, this)
    )js"));
    return names.toVariant().toStringList();
}

std::expected<QVariant, Error> JsContext::callFunction(const QString& name, const QVariantList& args)
{
    QQmlEngine& engine = ensureEngine();

    const QJSValue function = engine.globalObject().property(name);
    if (!function.isCallable())
        return std::unexpected(Error { QStringLiteral("No such function \"%1\"").arg(name) });

    QJSValueList arguments;
    for (const QVariant& arg : args)
        arguments << engine.toScriptValue(arg);

    const QJSValue result = QJSManagedValue(function, &engine).call(arguments);
    if (const auto ended = checkCall(engine); !ended)
        return std::unexpected(ended.error());
    return result.toVariant();
}

std::expected<QVariant, Error> JsContext::evaluate(const QByteArray& code)
{
    QQmlEngine& engine = ensureEngine();
    QStringList trace;
    const QJSValue result = engine.evaluate(QString::fromUtf8(code), {}, 1, &trace);
    if (!trace.isEmpty() || engine.isInterrupted())
        return std::unexpected(errorOf(result, trace));
    return result.toVariant();
}
