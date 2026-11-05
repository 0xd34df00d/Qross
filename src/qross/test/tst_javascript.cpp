/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/context.h>
#include <qross/core/manager.h>
#include <qross/core/object.h>
#include <qross/core/script.h>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QCoreApplication>
#include <QtCore/QPointer>
#include <QtCore/QStringListModel>
#include <QtQml/QJSEngine>
#include <QtTest/QTest>

class Host : public QObject
{
    Q_OBJECT

    Qross::Object::Ptr m_kept;
    QStringListModel m_model { QStringList({ QStringLiteral("alpha"), QStringLiteral("beta") }), this };
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
    QAbstractItemModel* model() { return &m_model; }
    void keep(Qross::Object::Ptr object) { m_kept = object; }
    bool isNull(Qross::Object::Ptr object) { return object.isNull(); }
    Qross::Object::Ptr same(Qross::Object::Ptr object) { return object; }
    QStringList methods(Qross::Object::Ptr object) { return object ? object->methodNames() : QStringList(); }
    QVariant call(Qross::Object::Ptr object, const QString& method, const QVariantList& args = QVariantList())
    {
        return object ? object->callMethod(method, args).value_or(QVariant()) : QVariant();
    }
};

class tst_JavaScript : public QObject
{
    Q_OBJECT

    Host m_global;

    static std::unique_ptr<Qross::Script> run(const QByteArray& code, QObject* local = nullptr, Qross::ObjectOptions options = {})
    {
        Qross::Config config { .source = Qross::Code { code, QStringLiteral("tst") }, .interpreter = QStringLiteral("javascript") };
        if (local)
            config.objects << Qross::Published { local, QStringLiteral("Local"), options };
        auto script = std::make_unique<Qross::Script>(std::move(config));
        (void)script->run();
        return script;
    }

    static QByteArray describe(const Qross::Script& script)
    {
        return script.error() ? script.error()->toString().toUtf8() : QByteArray();
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
        QCOMPARE(manager.interpreterNameForFile(QStringLiteral("dir/test.js")), QStringLiteral("javascript"));
        QCOMPARE(manager.interpreterNameForFile(QStringLiteral("test.es")), QStringLiteral("javascript"));
        QVERIFY(manager.interpreter(QStringLiteral("javascript")));
    }

    void importsQtQml()
    {
        // Runs before any other script: the import registers the value types
        // for the whole process.
        Host local;
        {
            Qross::Script plain({ .source = Qross::Code { "var row = Local.model().index(1, 0).row;", QStringLiteral("plain") }, .interpreter = QStringLiteral("javascript"), .options = { { QStringLiteral("qml"), false } }, .objects = { { &local, QStringLiteral("Local") } } });
            QVERIFY(plain.run());
            QVERIFY(!plain.evaluate("row")->isValid());
        }

        const auto script = run("var index = Local.model().index(1, 0);", &local);
        QVERIFY(!script->error());
        QCOMPARE(script->evaluate("index.row")->toInt(), 1);
        QCOMPARE(script->evaluate("index.data()")->toString(), QStringLiteral("beta"));
    }

    void acceptsTheOldName()
    {
        Qross::Manager& manager = Qross::Manager::self();
        QVERIFY(manager.hasInterpreter(QStringLiteral("qtscript")));
        QCOMPARE(manager.interpreter(QStringLiteral("qtscript")), manager.interpreter(QStringLiteral("javascript")));

        Qross::Script old({ .source = Qross::Code { "var answer = 42;", QStringLiteral("old") }, .interpreter = QStringLiteral("qtscript") });
        QVERIFY(old.run());
        QCOMPARE(old.evaluate("answer")->toInt(), 42);
    }

    void rejectsUnknownOptions()
    {
        Qross::Script script({ .source = Qross::Code { "1" }, .interpreter = QStringLiteral("javascript"), .options = { { QStringLiteral("nope"), 1 } } });
        const auto result = script.run();
        QVERIFY(!result);
        QVERIFY(result.error().message.contains(QStringLiteral("nope")));
    }

    void reportsSyntaxErrors()
    {
        const auto script = run("var ok = 1;\nfoo(");
        QVERIFY(script->error());
        QVERIFY(script->error()->message.startsWith(QStringLiteral("SyntaxError")));
        QCOMPARE(script->error()->line, 2);
    }

    void reportsThrownErrors()
    {
        const auto script = run(R"js(
            function boom() {
                throw new Error('boom');
            }
            boom();
        )js");
        QVERIFY(script->error());
        QCOMPARE(script->error()->message, QStringLiteral("Error: boom"));
        QCOMPARE(script->error()->line, 3);
        QVERIFY(script->error()->trace.contains(QStringLiteral("boom")));
    }

    void reportsThrownValues()
    {
        const auto script = run("throw 42;");
        QVERIFY(script->error());
        QCOMPARE(script->error()->message, QStringLiteral("42"));
        QVERIFY(!script->error()->trace.isEmpty());
    }

    void acceptsErrorValues()
    {
        const auto script = run("var error = new Error('normal data');\nerror;");
        QVERIFY2(!script->error(), describe(*script).constData());
        QVERIFY(script->evaluate("error"));
        QCOMPARE(script->evaluate("error.message")->toString(), QStringLiteral("normal data"));
        QVERIFY(!script->evaluate("throw error"));
    }

    void skipsTheShebang()
    {
        const auto script = run("#!/usr/bin/env qross\nvar line = 2;\nfoo(");
        QVERIFY(script->error());
        QCOMPARE(script->error()->line, 3);
    }

    void listsFunctions()
    {
        const auto script = run(R"js(
            function first() {}
            var second = function() {};
            var notAFunction = 1;
            let third = () => 0;
        )js");
        QVERIFY(!script->error());
        QCOMPARE(script->functionNames(), QStringList({ QStringLiteral("first"), QStringLiteral("second") }));
    }

    void callsFunctions()
    {
        const auto script = run(R"js(
            function add(a, b) { return a + b; }
            function same(x) { return x; }
            function nothing() {}
        )js");
        QVERIFY(!script->error());
        QCOMPARE(script->call(QStringLiteral("add"), { 40, 2 })->toInt(), 42);
        QCOMPARE(script->call(QStringLiteral("same"), { QStringLiteral("text") })->toString(), QStringLiteral("text"));
        const QVariantList list({ 1, QStringLiteral("a") });
        QCOMPARE(script->call(QStringLiteral("same"), { QVariant(list) })->toList(), list);
        const QVariantMap map({ { QStringLiteral("k"), 1 } });
        QCOMPARE(script->call(QStringLiteral("same"), { QVariant(map) })->toMap(), map);
        QVERIFY(!script->call(QStringLiteral("nothing"))->isValid());
        QVERIFY(!script->error());

        const auto failed = script->call(QStringLiteral("missing"));
        QVERIFY(!failed);
        QVERIFY(failed.error().message.contains(QStringLiteral("missing")));
    }

    void reportsInterruptedCalls()
    {
        const auto script = run(R"js(
            function spin() { for (var i = 0; i < 10000000; i++) {} return i; }
            Global.keep({ spin: spin });
        )js");
        QVERIFY2(!script->error(), describe(*script).constData());
        QObject* engine = nullptr;
        QVERIFY(QMetaObject::invokeMethod(script->context(), "engine", Q_RETURN_ARG(QObject*, engine)));
        auto* const jsEngine = qobject_cast<QJSEngine*>(engine);
        QVERIFY(jsEngine);

        jsEngine->setInterrupted(true);
        const auto call = script->call(QStringLiteral("spin"));
        QVERIFY(!call);
        QVERIFY2(call.error().message.contains(QStringLiteral("Interrupted")), qPrintable(call.error().message));
        QVERIFY(script->error());
        const auto method = m_global.kept()->callMethod(QStringLiteral("spin"));
        QVERIFY(!method);
        QVERIFY2(method.error().message.contains(QStringLiteral("Interrupted")), qPrintable(method.error().message));
        jsEngine->setInterrupted(false);
        QCOMPARE(script->call(QStringLiteral("spin"))->toInt(), 10000000);
        QVERIFY(!script->error());
        QCOMPARE(m_global.kept()->callMethod(QStringLiteral("spin"))->toInt(), 10000000);
        m_global.forget();
    }

    void reportsExceptionsFromCalls()
    {
        const auto script = run(R"js(
            function bad(x) {
                throw new TypeError('bad ' + x);
            }
            function plain() { throw 'plain'; }
        )js");
        const auto bad = script->call(QStringLiteral("bad"), { 1 });
        QVERIFY(!bad);
        QCOMPARE(bad.error().message, QStringLiteral("TypeError: bad 1"));
        QCOMPARE(bad.error().line, 3);

        const auto plain = script->call(QStringLiteral("plain"));
        QVERIFY(!plain);
        QCOMPARE(plain.error().message, QStringLiteral("plain"));
    }

    void evaluates()
    {
        const auto script = run("var base = 40;");
        QCOMPARE(script->evaluate("base + 2")->toInt(), 42);
        QVERIFY(!script->error());

        const QVariant null = script->evaluate("null").value_or(QVariant());
        QVERIFY(null.isValid());
        QVERIFY(null.isNull());
        QVERIFY(!script->evaluate("undefined")->isValid());

        const auto failed = script->evaluate("(");
        QVERIFY(!failed);
        QVERIFY(failed.error().message.startsWith(QStringLiteral("SyntaxError")));
    }

    void publishesObjects()
    {
        Host local;
        local.setObjectName(QStringLiteral("Local"));
        const auto script = run(R"js(
            var ok = self.name() === 'tst'
                && Qross.interpreters().indexOf('javascript') >= 0
                && Global.objectName === 'Global'
                && Local.objectName === 'Local'
                && Global.self() === Global
                && Global.Fast === 1 && Local.Slow === 2 && Global.self().Slow === 2;
        )js",
            &local);
        QVERIFY(!script->error());
        QVERIFY(script->evaluate("ok")->toBool());
    }

    void connectsSignalsAutomatically()
    {
        Host local;
        const auto script = run(R"js(
            var got = null;
            function fired(n) { got = n; }
        )js",
            &local, Qross::AutoConnectSignals);
        QVERIFY(!script->error());
        Q_EMIT local.fired(7);
        Q_EMIT local.named(QStringLiteral("ignored"));
        QCOMPARE(script->evaluate("got")->toInt(), 7);
    }

    void keepsPublishedObjectsAlive()
    {
        QPointer<Host> orphan = new Host;
        const auto script = run(R"js(
            var copy = Local.self();
            copy = null;
            gc();
        )js",
            orphan);
        QVERIFY(!script->error());
        (void)script->evaluate("gc()");
        QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete);
        QVERIFY(orphan);
        delete orphan;
    }

    void wrapsScriptObjects()
    {
        const auto script = run(R"js(
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
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("results.first")->toInt(), 42);
        QCOMPARE(script->evaluate("results.second")->toInt(), 43);
        QCOMPARE(script->evaluate("results.greeting")->toString(), QStringLiteral("hi bob"));
        QCOMPARE(script->evaluate("results.methods")->toStringList(), QStringList(QStringLiteral("greet")));
        QCOMPARE(script->evaluate("results.plain")->toInt(), 42);
        QCOMPARE(script->evaluate("results.nullObject")->toBool(), true);
        QVERIFY(!script->evaluate("results.missing")->isValid());
    }

    void returnsScriptObjects()
    {
        const auto script = run(R"js(
            var object = { answer: function() { return 42; } };
            var returned = Global.same(object).value();
            var identical = returned === object;
            var answer = returned.answer();
            var empty = Global.same(null).value();
        )js");
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("identical")->toBool(), true);
        QCOMPARE(script->evaluate("answer")->toInt(), 42);
        QVERIFY(script->evaluate("empty")->isNull());
    }

    void callsScriptObjectsFromOutside()
    {
        const auto script = run("Global.keep({ answer: function() { return 42; } });");
        QVERIFY(!script->error());
        const Qross::Object::Ptr kept = m_global.kept();
        m_global.forget();
        QVERIFY(kept);
        QCOMPARE(kept->callMethod(QStringLiteral("answer"))->toInt(), 42);

        script->reset();
        QVERIFY(!kept->callMethod(QStringLiteral("answer")));
        QVERIFY(kept->methodNames().isEmpty());
    }

    void startsAfreshOnRerun()
    {
        const auto script = run(R"js(
            var runs = (typeof runs === 'number' ? runs : 0) + 1;
            let fresh = true;
        )js");
        QVERIFY(!script->error());
        (void)script->run();
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("runs")->toInt(), 1);
    }

    void exposesTheEngine()
    {
        const auto script = run("var answer = 42;");
        QObject* engine = nullptr;
        QVERIFY(QMetaObject::invokeMethod(script->context(), "engine", Q_RETURN_ARG(QObject*, engine)));
        auto* const jsEngine = qobject_cast<QJSEngine*>(engine);
        QVERIFY(jsEngine);
        QCOMPARE(jsEngine->evaluate(QStringLiteral("answer")).toInt(), 42);
    }
};

QTEST_MAIN(tst_JavaScript)
#include "tst_javascript.moc"
