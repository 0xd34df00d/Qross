/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/manager.h>
#include <qross/core/object.h>
#include <qross/core/script.h>
#include <thread>
#include <QtCore/QCoreApplication>
#include <QtCore/QPointer>
#include <QtCore/QStringListModel>
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

class tst_Python : public QObject
{
    Q_OBJECT

    Host m_global;

    static std::unique_ptr<Qross::Script> run(const QByteArray& code, QObject* local = nullptr, Qross::ObjectOptions options = {})
    {
        Qross::Config config { .source = Qross::Code { code, QStringLiteral("tst") }, .interpreter = QStringLiteral("python") };
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
        QVERIFY(manager.interpreters().contains(QStringLiteral("python")));
        QCOMPARE(manager.interpreterNameForFile(QStringLiteral("dir/test.py")), QStringLiteral("python"));
        QVERIFY(manager.interpreter(QStringLiteral("python")));
    }

    void reportsSyntaxErrors()
    {
        const auto script = run("ok = 1\nif (");
        QVERIFY(script->error());
        QVERIFY2(script->error()->message.startsWith(QStringLiteral("SyntaxError")), qPrintable(script->error()->message));
        QCOMPARE(script->error()->line, 2);
    }

    void reportsExceptions()
    {
        const auto script = run(R"py(
def boom():
    raise ValueError('boom')

boom()
)py");
        QVERIFY(script->error());
        QCOMPARE(script->error()->message, QStringLiteral("ValueError: boom"));
        QCOMPARE(script->error()->line, 3);
        QVERIFY(script->error()->trace.contains(QStringLiteral("in boom")));
    }

    void listsFunctions()
    {
        const auto script = run(R"py(
import os

def first():
    pass

second = lambda: 0

class Third:
    pass

not_a_function = 1
)py");
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->functionNames(), QStringList({ QStringLiteral("first"), QStringLiteral("second"), QStringLiteral("Third") }));
    }

    void callsFunctions()
    {
        const auto script = run(R"py(
def add(a, b):
    return a + b

def same(x):
    return x

def nothing():
    pass
)py");
        QVERIFY2(!script->error(), describe(*script).constData());
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

    void reportsExceptionsFromCalls()
    {
        const auto script = run(R"py(
def bad(x):
    raise TypeError('bad ' + str(x))
)py");
        const auto failed = script->call(QStringLiteral("bad"), { 1 });
        QVERIFY(!failed);
        QCOMPARE(failed.error().message, QStringLiteral("TypeError: bad 1"));
        QCOMPARE(failed.error().line, 3);
    }

    void evaluates()
    {
        const auto script = run("base = 40");
        QCOMPARE(script->evaluate("base + 2")->toInt(), 42);
        QVERIFY(!script->error());
        QVERIFY(!script->evaluate("None")->isValid());

        QVERIFY(!script->evaluate("extra = 5")->isValid());
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("extra")->toInt(), 5);

        const auto failed = script->evaluate("(");
        QVERIFY(!failed);
        QVERIFY(failed.error().message.startsWith(QStringLiteral("SyntaxError")));
    }

    void publishesObjects()
    {
        Host local;
        local.setObjectName(QStringLiteral("Local"));
        const auto script = run(R"py(
ok = (self.name() == 'tst'
      and 'python' in Qross.interpreters()
      and Global.objectName == 'Global'
      and Local.objectName == 'Local'
      and Global.self() == Global
      and Global.self() != Local
      and Global.Fast == 1 and Local.Slow == 2 and Global.self().Slow == 2
      and Global.className() == 'Host'
      and 'fired' in dir(Global))
)py",
            &local);
        QVERIFY2(!script->error(), describe(*script).constData());
        QVERIFY(script->evaluate("ok")->toBool());
    }

    void connectsSignalsAutomatically()
    {
        Host local;
        const auto script = run(R"py(
got = None

def fired(n):
    global got
    got = n
)py",
            &local, Qross::AutoConnectSignals);
        QVERIFY2(!script->error(), describe(*script).constData());
        Q_EMIT local.fired(7);
        Q_EMIT local.named(QStringLiteral("ignored"));
        QCOMPARE(script->evaluate("got")->toInt(), 7);
    }

    void connectsSignalsFromScripts()
    {
        Host local;
        const auto script = run(R"py(
got = []

def on(n):
    got.append(n)

Local.fired.connect(on)
Local.fired(3)
Local.fired.disconnect(on)
Local.fired(4)
)py",
            &local);
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("got")->toList(), QVariantList({ 3 }));
    }

    void deliversSignalsFromOtherThreads()
    {
        Host local;
        const auto script = run(R"py(
got = None

def fired(n):
    global got
    got = n
)py",
            &local, Qross::AutoConnectSignals);
        QVERIFY2(!script->error(), describe(*script).constData());
        std::thread([&local] { Q_EMIT local.fired(9); }).join();
        QCoreApplication::processEvents();
        QCOMPARE(script->evaluate("got")->toInt(), 9);
    }

    void wrapsScriptObjects()
    {
        const auto script = run(R"py(
class Counter:
    def __init__(self, start):
        self.n = start

    def next(self):
        self.n += 1
        return self.n

class Greeter:
    def greet(self, name):
        return 'hi ' + name

counter = Counter(41)
results = {
    'first': Global.call(counter, 'next'),
    'second': Global.call(counter, 'next'),
    'greeting': Global.call(Greeter(), 'greet', ['bob']),
    'methods': Global.methods(Greeter()),
    'identity': Global.same(counter) is counter,
    'nullObject': Global.isNull(None),
    'missing': Global.call(counter, 'nope'),
}
)py");
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("results['first']")->toInt(), 42);
        QCOMPARE(script->evaluate("results['second']")->toInt(), 43);
        QCOMPARE(script->evaluate("results['greeting']")->toString(), QStringLiteral("hi bob"));
        QCOMPARE(script->evaluate("results['methods']")->toStringList(), QStringList(QStringLiteral("greet")));
        QCOMPARE(script->evaluate("results['identity']")->toBool(), true);
        QCOMPARE(script->evaluate("results['nullObject']")->toBool(), true);
        QVERIFY(!script->evaluate("results['missing']")->isValid());
    }

    void callsScriptObjectsFromOutside()
    {
        const auto script = run(R"py(
class Answer:
    def answer(self):
        return 42

Global.keep(Answer())
)py");
        QVERIFY2(!script->error(), describe(*script).constData());
        const Qross::Object::Ptr kept = m_global.kept();
        m_global.forget();
        QVERIFY(kept);
        QCOMPARE(kept->callMethod(QStringLiteral("answer"))->toInt(), 42);

        script->reset();
        QCOMPARE(kept->callMethod(QStringLiteral("answer"))->toInt(), 42);
        QVERIFY(!kept->callMethod(QStringLiteral("nope")));
    }

    void startsAfreshOnRerun()
    {
        const auto script = run("runs = globals().get('runs', 0) + 1");
        QVERIFY2(!script->error(), describe(*script).constData());
        (void)script->run();
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("runs")->toInt(), 1);
    }

    void registersModules()
    {
        const auto first = run(R"py(
import pickle
import sys

class Item:
    def __init__(self, n):
        self.n = n

registered = sys.modules[__name__].Item is Item
copy = pickle.loads(pickle.dumps(Item(7)))
)py");
        QVERIFY2(!first->error(), describe(*first).constData());
        QCOMPARE(first->evaluate("registered")->toBool(), true);
        QCOMPARE(first->evaluate("type(copy) is Item")->toBool(), true);
        QCOMPARE(first->evaluate("copy.n")->toInt(), 7);
        const QString name = first->evaluate("__name__")->toString();
        QCOMPARE(name, QStringLiteral("qross_tst"));

        const auto second = run("import sys");
        QVERIFY2(!second->error(), describe(*second).constData());
        QCOMPARE(second->evaluate("__name__")->toString(), QStringLiteral("qross_tst_2"));
        const QByteArray registered = QStringLiteral("'%1' in sys.modules").arg(name).toUtf8();
        QCOMPARE(second->evaluate(registered)->toBool(), true);
        first->reset();
        QCOMPARE(second->evaluate(registered)->toBool(), false);
    }

    void refusesDeletedObjects()
    {
        auto* const local = new Host;
        const auto script = run(R"py(
def name():
    return Local.objectName
)py",
            local);
        QVERIFY2(!script->error(), describe(*script).constData());
        delete local;
        const auto failed = script->call(QStringLiteral("name"));
        QVERIFY(!failed);
        QVERIFY(failed.error().message.startsWith(QStringLiteral("RuntimeError")));
    }
};

QTEST_MAIN(tst_Python)
#include "tst_python.moc"
