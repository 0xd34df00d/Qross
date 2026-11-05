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
#include "../core/manager.h"
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
    for (const auto& [name, object] : Manager::self().objects().asKeyValueRange())
        publish(global, name, object);
    for (const auto& [name, object] : script()->objects().asKeyValueRange())
        publish(global, name, object);
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

    const QString file = script()->file().isEmpty() ? script()->name() : script()->file();
    QStringList trace;
    const QJSValue result = engine.evaluate(code, file, 1, &trace);
    if (result.isError() || !trace.isEmpty())
        return std::unexpected(errorOf(result, trace));

    connectSignals(engine);
    return {};
}

void JsContext::connectSignals(QQmlEngine& engine)
{
    const QJSValue global = engine.globalObject();
    const QHash<QString, ChildrenInterface::Options> options = script()->objectOptions();
    for (auto it = options.cbegin(); it != options.cend(); ++it)
    {
        if (!(it.value() & ChildrenInterface::AutoConnectSignals))
            continue;
        QObject* const sender = script()->object(it.key());
        if (!sender)
            continue;

        // Overloads share a name and a wrapper property, so one connection per name.
        QSet<QString> connected;
        const QJSValue wrapper = global.property(it.key());
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

QStringList JsContext::functionNames()
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
    if (engine.hasError())
        return std::unexpected(errorOf(engine.catchError()));
    return result.toVariant();
}

std::expected<QVariant, Error> JsContext::evaluate(const QByteArray& code)
{
    QStringList trace;
    const QJSValue result = ensureEngine().evaluate(QString::fromUtf8(code), {}, 1, &trace);
    if (result.isError() || !trace.isEmpty())
        return std::unexpected(errorOf(result, trace));
    return result.toVariant();
}
