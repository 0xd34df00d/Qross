/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007-2008 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "script.h"
#include <QtCore/QMetaEnum>
#include <QtCore/QMetaMethod>
#include <QtCore/QSet>
#include <QtQml/QJSManagedValue>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>
#include "../core/action.h"
#include "../core/manager.h"
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

JsScript::JsScript(Interpreter* interpreter, Action* action)
    : Script(interpreter, action)
{
}

JsScript::~JsScript() = default;

QObject* JsScript::engine()
{
    return &ensureEngine();
}

QQmlEngine& JsScript::ensureEngine()
{
    return m_engine ? *m_engine : createEngine();
}

QQmlEngine& JsScript::createEngine()
{
    m_engine = std::make_unique<QQmlEngine>();
    if (action()->option(QStringLiteral("qml"), true).toBool())
        importQtQml(*m_engine);
    JsObject::prepareEngine(*m_engine);

    QJSValue global = m_engine->globalObject();
    publish(global, QStringLiteral("self"), action());
    for (const auto& [name, object] : Manager::self().objects().asKeyValueRange())
        publish(global, name, object);
    for (const auto& [name, object] : action()->objects().asKeyValueRange())
        publish(global, name, object);
    return *m_engine;
}

void JsScript::publish(QJSValue& global, const QString& name, QObject* object)
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

void JsScript::execute()
{
    clearError();
    QQmlEngine& engine = createEngine();

    // A shebang is not JavaScript; its newline stays so that line numbers do.
    QString code = QString::fromUtf8(action()->code());
    if (code.startsWith(QLatin1String("#!")))
    {
        const qsizetype eol = code.indexOf(QLatin1Char('\n'));
        code.remove(0, eol < 0 ? code.size() : eol);
    }

    const QString file = action()->file().isEmpty() ? action()->name() : action()->file();
    QStringList trace;
    const QJSValue result = engine.evaluate(code, file, 1, &trace);
    if (result.isError() || !trace.isEmpty())
    {
        storeException(*this, result, trace);
        return;
    }

    connectSignals(engine);
}

void JsScript::connectSignals(QQmlEngine& engine)
{
    const QJSValue global = engine.globalObject();
    const QHash<QString, ChildrenInterface::Options> options = action()->objectOptions();
    for (auto it = options.cbegin(); it != options.cend(); ++it)
    {
        if (!(it.value() & ChildrenInterface::AutoConnectSignals))
            continue;
        QObject* const sender = action()->object(it.key());
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

QStringList JsScript::functionNames()
{
    const QJSValue names = ensureEngine().evaluate(QStringLiteral(R"js(
        Object.keys(this).filter(function(name) { return typeof this[name] === 'function'; }, this)
    )js"));
    return names.toVariant().toStringList();
}

QVariant JsScript::callFunction(const QString& name, const QVariantList& args)
{
    clearError();
    QQmlEngine& engine = ensureEngine();

    const QJSValue function = engine.globalObject().property(name);
    if (!function.isCallable())
    {
        setError(QStringLiteral("No such function \"%1\"").arg(name));
        return {};
    }

    QJSValueList arguments;
    for (const QVariant& arg : args)
        arguments << engine.toScriptValue(arg);

    const QJSValue result = QJSManagedValue(function, &engine).call(arguments);
    if (engine.hasError())
    {
        storeException(*this, engine.catchError());
        return {};
    }
    return result.toVariant();
}

QVariant JsScript::evaluate(const QByteArray& code)
{
    clearError();
    QStringList trace;
    const QJSValue result = ensureEngine().evaluate(QString::fromUtf8(code), {}, 1, &trace);
    if (result.isError() || !trace.isEmpty())
    {
        storeException(*this, result, trace);
        return {};
    }
    return result.toVariant();
}
