/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/action.h>
#include <qross/core/manager.h>
#include <qross/core/object.h>
#include <qross/core/script.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QPointer>
#include <QtQml/QJSEngine>
#include <QtTest/QTest>

class Host : public QObject
{
    Q_OBJECT

    Qross::Object::Ptr m_kept;
public:
    enum Mode
    {
        Fast = 1,
        Slow = 2
    };
    Q_ENUM(Mode)

    Qross::Object::Ptr kept() const { return m_kept; }
    void forget() { m_kept.reset(); }
Q_SIGNALS:
    void fired(int n);
    void named(const QString& name);
public Q_SLOTS:
    QObject* self() { return this; }
    void keep(Qross::Object::Ptr object) { m_kept = object; }
    bool isNull(Qross::Object::Ptr object) { return object.isNull(); }
    QStringList methods(Qross::Object::Ptr object) { return object ? object->methodNames() : QStringList(); }
    QVariant call(Qross::Object::Ptr object, const QString& method, const QVariantList& args = QVariantList())
    {
        return object ? object->callMethod(method, args) : QVariant();
    }
};

class tst_JavaScript : public QObject
{
    Q_OBJECT

    Host m_global;

    static std::unique_ptr<Qross::Action> run(const QByteArray& code, QObject* local = nullptr, Qross::ChildrenInterface::Options options = Qross::ChildrenInterface::NoOption)
    {
        auto action = std::make_unique<Qross::Action>(nullptr, QStringLiteral("tst"));
        action->setInterpreter(QStringLiteral("javascript"));
        action->setCode(code);
        if (local)
            action->addObject(local, QStringLiteral("Local"), options);
        action->trigger();
        return action;
    }
private Q_SLOTS:
    void initTestCase()
    {
        m_global.setObjectName(QStringLiteral("Global"));
        Qross::Manager::self().addObject(&m_global);
    }

    void loads()
    {
        Qross::Manager& manager = Qross::Manager::self();
        QVERIFY(manager.interpreters().contains(QStringLiteral("javascript")));
        QVERIFY(!manager.interpreters().contains(QStringLiteral("qtscript")));
        QCOMPARE(manager.interpreternameForFile(QStringLiteral("dir/test.js")), QStringLiteral("javascript"));
        QCOMPARE(manager.interpreternameForFile(QStringLiteral("test.es")), QStringLiteral("javascript"));
        QVERIFY(manager.interpreter(QStringLiteral("javascript")));
    }

    void acceptsTheOldName()
    {
        Qross::Manager& manager = Qross::Manager::self();
        QVERIFY(manager.hasInterpreterInfo(QStringLiteral("qtscript")));
        QCOMPARE(manager.interpreter(QStringLiteral("qtscript")), manager.interpreter(QStringLiteral("javascript")));

        Qross::Action action(nullptr, QStringLiteral("old"));
        action.setInterpreter(QStringLiteral("qtscript"));
        action.setCode("var answer = 42;");
        action.trigger();
        QVERIFY(!action.hadError());
        QCOMPARE(action.evaluate("answer").toInt(), 42);
    }

    void reportsSyntaxErrors()
    {
        const auto action = run("var ok = 1;\nfoo(");
        QVERIFY(action->hadError());
        QVERIFY(action->errorMessage().startsWith(QStringLiteral("SyntaxError")));
        QCOMPARE(action->errorLineNo(), 2);
    }

    void reportsThrownErrors()
    {
        const auto action = run(R"js(
            function boom() {
                throw new Error('boom');
            }
            boom();
        )js");
        QVERIFY(action->hadError());
        QCOMPARE(action->errorMessage(), QStringLiteral("Error: boom"));
        QCOMPARE(action->errorLineNo(), 3);
        QVERIFY(action->errorTrace().contains(QStringLiteral("boom")));
    }

    void reportsThrownValues()
    {
        const auto action = run("throw 42;");
        QVERIFY(action->hadError());
        QCOMPARE(action->errorMessage(), QStringLiteral("42"));
        QVERIFY(!action->errorTrace().isEmpty());
    }

    void skipsTheShebang()
    {
        const auto action = run("#!/usr/bin/env qross\nvar line = 2;\nfoo(");
        QVERIFY(action->hadError());
        QCOMPARE(action->errorLineNo(), 3);
    }

    void listsFunctions()
    {
        const auto action = run(R"js(
            function first() {}
            var second = function() {};
            var notAFunction = 1;
            let third = () => 0;
        )js");
        QVERIFY(!action->hadError());
        QCOMPARE(action->functionNames(), QStringList({ QStringLiteral("first"), QStringLiteral("second") }));
    }

    void callsFunctions()
    {
        const auto action = run(R"js(
            function add(a, b) { return a + b; }
            function same(x) { return x; }
            function nothing() {}
        )js");
        QVERIFY(!action->hadError());
        QCOMPARE(action->callFunction(QStringLiteral("add"), { 40, 2 }).toInt(), 42);
        QCOMPARE(action->callFunction(QStringLiteral("same"), { QStringLiteral("text") }).toString(), QStringLiteral("text"));
        const QVariantList list({ 1, QStringLiteral("a") });
        QCOMPARE(action->callFunction(QStringLiteral("same"), { QVariant(list) }).toList(), list);
        const QVariantMap map({ { QStringLiteral("k"), 1 } });
        QCOMPARE(action->callFunction(QStringLiteral("same"), { QVariant(map) }).toMap(), map);
        QVERIFY(!action->callFunction(QStringLiteral("nothing")).isValid());
        QVERIFY(!action->script()->hadError());

        QVERIFY(!action->callFunction(QStringLiteral("missing")).isValid());
        QVERIFY(action->script()->hadError());
        QVERIFY(action->script()->errorMessage().contains(QStringLiteral("missing")));
    }

    void reportsExceptionsFromCalls()
    {
        const auto action = run(R"js(
            function bad(x) {
                throw new TypeError('bad ' + x);
            }
            function plain() { throw 'plain'; }
        )js");
        QVERIFY(!action->callFunction(QStringLiteral("bad"), { 1 }).isValid());
        QVERIFY(action->script()->hadError());
        QCOMPARE(action->script()->errorMessage(), QStringLiteral("TypeError: bad 1"));
        QCOMPARE(action->script()->errorLineNo(), 3);

        QVERIFY(!action->callFunction(QStringLiteral("plain")).isValid());
        QCOMPARE(action->script()->errorMessage(), QStringLiteral("plain"));
    }

    void evaluates()
    {
        const auto action = run("var base = 40;");
        QCOMPARE(action->evaluate("base + 2").toInt(), 42);
        QVERIFY(!action->script()->hadError());

        const QVariant null = action->evaluate("null");
        QVERIFY(null.isValid());
        QVERIFY(null.isNull());
        QVERIFY(!action->evaluate("undefined").isValid());

        QVERIFY(!action->evaluate("(").isValid());
        QVERIFY(action->script()->hadError());
        QVERIFY(action->script()->errorMessage().startsWith(QStringLiteral("SyntaxError")));
    }

    void publishesObjects()
    {
        Host local;
        local.setObjectName(QStringLiteral("Local"));
        const auto action = run(R"js(
            var ok = self.name() === 'tst'
                && Qross.interpreters().indexOf('javascript') >= 0
                && Global.objectName === 'Global'
                && Local.objectName === 'Local'
                && Global.self() === Global
                && Global.Fast === 1 && Local.Slow === 2 && Global.self().Slow === 2;
        )js",
            &local);
        QVERIFY(!action->hadError());
        QVERIFY(action->evaluate("ok").toBool());
    }

    void connectsSignalsAutomatically()
    {
        Host local;
        const auto action = run(R"js(
            var got = null;
            function fired(n) { got = n; }
        )js",
            &local, Qross::ChildrenInterface::AutoConnectSignals);
        QVERIFY(!action->hadError());
        Q_EMIT local.fired(7);
        Q_EMIT local.named(QStringLiteral("ignored"));
        QCOMPARE(action->evaluate("got").toInt(), 7);
    }

    void keepsPublishedObjectsAlive()
    {
        QPointer<Host> orphan = new Host;
        const auto action = run(R"js(
            var copy = Local.self();
            copy = null;
            gc();
        )js",
            orphan);
        QVERIFY(!action->hadError());
        action->evaluate("gc()");
        QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete);
        QVERIFY(orphan);
        delete orphan;
    }

    void wrapsScriptObjects()
    {
        const auto action = run(R"js(
            function Counter(start) { this.n = start; this.next = function() { return ++this.n; }; }
            class Greeter { greet(name) { return 'hi ' + name; } }
            var counter = new Counter(41);
            var results = {
                first: Global.call(counter, 'next'),
                second: Global.call(counter, 'next'),
                greeting: Global.call(new Greeter(), 'greet', ['bob']),
                methods: Global.methods(new Greeter()),
                plain: Global.call({ twice: function(x) { return x * 2; } }, 'twice', [21]),
                nullObject: Global.isNull(null),
                missing: Global.call(counter, 'nope'),
            };
        )js");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("results.first").toInt(), 42);
        QCOMPARE(action->evaluate("results.second").toInt(), 43);
        QCOMPARE(action->evaluate("results.greeting").toString(), QStringLiteral("hi bob"));
        QCOMPARE(action->evaluate("results.methods").toStringList(), QStringList(QStringLiteral("greet")));
        QCOMPARE(action->evaluate("results.plain").toInt(), 42);
        QCOMPARE(action->evaluate("results.nullObject").toBool(), true);
        QVERIFY(!action->evaluate("results.missing").isValid());
    }

    void callsScriptObjectsFromOutside()
    {
        const auto action = run("Global.keep({ answer: function() { return 42; } });");
        QVERIFY(!action->hadError());
        const Qross::Object::Ptr kept = m_global.kept();
        m_global.forget();
        QVERIFY(kept);
        QCOMPARE(kept->callMethod(QStringLiteral("answer")).toInt(), 42);
        QVERIFY(!kept->hadError());

        action->finalize();
        QVERIFY(!kept->callMethod(QStringLiteral("answer")).isValid());
        QVERIFY(kept->hadError());
        QVERIFY(kept->methodNames().isEmpty());
    }

    void startsAfreshOnRerun()
    {
        const auto action = run(R"js(
            var runs = (typeof runs === 'number' ? runs : 0) + 1;
            let fresh = true;
        )js");
        QVERIFY(!action->hadError());
        action->trigger();
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("runs").toInt(), 1);
    }

    void exposesTheEngine()
    {
        const auto action = run("var answer = 42;");
        QObject* engine = nullptr;
        QVERIFY(QMetaObject::invokeMethod(action->script(), "engine", Q_RETURN_ARG(QObject*, engine)));
        auto* const jsEngine = qobject_cast<QJSEngine*>(engine);
        QVERIFY(jsEngine);
        QCOMPARE(jsEngine->evaluate(QStringLiteral("answer")).toInt(), 42);
    }
};

QTEST_MAIN(tst_JavaScript)
#include "tst_javascript.moc"
