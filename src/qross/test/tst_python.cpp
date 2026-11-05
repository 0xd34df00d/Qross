/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/context.h>
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
        return object ? object->callMethod(method, args) : QVariant();
    }
};

class tst_Python : public QObject
{
    Q_OBJECT

    Host m_global;

    static std::unique_ptr<Qross::Script> run(const QByteArray& code, QObject* local = nullptr, Qross::ChildrenInterface::Options options = Qross::ChildrenInterface::NoOption)
    {
        auto action = std::make_unique<Qross::Script>(nullptr, QStringLiteral("tst"));
        action->setInterpreter(QStringLiteral("python"));
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
        QVERIFY(manager.interpreters().contains(QStringLiteral("python")));
        QCOMPARE(manager.interpreternameForFile(QStringLiteral("dir/test.py")), QStringLiteral("python"));
        QVERIFY(manager.interpreter(QStringLiteral("python")));
    }

    void reportsSyntaxErrors()
    {
        const auto action = run("ok = 1\nif (");
        QVERIFY(action->hadError());
        QVERIFY2(action->errorMessage().startsWith(QStringLiteral("SyntaxError")), qPrintable(action->errorMessage()));
        QCOMPARE(action->errorLineNo(), 2);
    }

    void reportsExceptions()
    {
        const auto action = run(R"py(
def boom():
    raise ValueError('boom')

boom()
)py");
        QVERIFY(action->hadError());
        QCOMPARE(action->errorMessage(), QStringLiteral("ValueError: boom"));
        QCOMPARE(action->errorLineNo(), 3);
        QVERIFY(action->errorTrace().contains(QStringLiteral("in boom")));
    }

    void listsFunctions()
    {
        const auto action = run(R"py(
import os

def first():
    pass

second = lambda: 0

class Third:
    pass

not_a_function = 1
)py");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->functionNames(), QStringList({ QStringLiteral("first"), QStringLiteral("second"), QStringLiteral("Third") }));
    }

    void callsFunctions()
    {
        const auto action = run(R"py(
def add(a, b):
    return a + b

def same(x):
    return x

def nothing():
    pass
)py");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->callFunction(QStringLiteral("add"), { 40, 2 }).toInt(), 42);
        QCOMPARE(action->callFunction(QStringLiteral("same"), { QStringLiteral("text") }).toString(), QStringLiteral("text"));
        const QVariantList list({ 1, QStringLiteral("a") });
        QCOMPARE(action->callFunction(QStringLiteral("same"), { QVariant(list) }).toList(), list);
        const QVariantMap map({ { QStringLiteral("k"), 1 } });
        QCOMPARE(action->callFunction(QStringLiteral("same"), { QVariant(map) }).toMap(), map);
        QVERIFY(!action->callFunction(QStringLiteral("nothing")).isValid());
        QVERIFY(!action->context()->hadError());

        QVERIFY(!action->callFunction(QStringLiteral("missing")).isValid());
        QVERIFY(action->context()->hadError());
        QVERIFY(action->context()->errorMessage().contains(QStringLiteral("missing")));
    }

    void reportsExceptionsFromCalls()
    {
        const auto action = run(R"py(
def bad(x):
    raise TypeError('bad ' + str(x))
)py");
        QVERIFY(!action->callFunction(QStringLiteral("bad"), { 1 }).isValid());
        QVERIFY(action->context()->hadError());
        QCOMPARE(action->context()->errorMessage(), QStringLiteral("TypeError: bad 1"));
        QCOMPARE(action->context()->errorLineNo(), 3);
    }

    void evaluates()
    {
        const auto action = run("base = 40");
        QCOMPARE(action->evaluate("base + 2").toInt(), 42);
        QVERIFY(!action->context()->hadError());
        QVERIFY(!action->evaluate("None").isValid());

        QVERIFY(!action->evaluate("extra = 5").isValid());
        QVERIFY2(!action->context()->hadError(), qPrintable(action->context()->errorMessage()));
        QCOMPARE(action->evaluate("extra").toInt(), 5);

        QVERIFY(!action->evaluate("(").isValid());
        QVERIFY(action->context()->hadError());
        QVERIFY(action->context()->errorMessage().startsWith(QStringLiteral("SyntaxError")));
    }

    void publishesObjects()
    {
        Host local;
        local.setObjectName(QStringLiteral("Local"));
        const auto action = run(R"py(
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
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QVERIFY(action->evaluate("ok").toBool());
    }

    void connectsSignalsAutomatically()
    {
        Host local;
        const auto action = run(R"py(
got = None

def fired(n):
    global got
    got = n
)py",
            &local, Qross::ChildrenInterface::AutoConnectSignals);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        Q_EMIT local.fired(7);
        Q_EMIT local.named(QStringLiteral("ignored"));
        QCOMPARE(action->evaluate("got").toInt(), 7);
    }

    void connectsSignalsFromScripts()
    {
        Host local;
        const auto action = run(R"py(
got = []

def on(n):
    got.append(n)

Local.fired.connect(on)
Local.fired(3)
Local.fired.disconnect(on)
Local.fired(4)
)py",
            &local);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("got").toList(), QVariantList({ 3 }));
    }

    void deliversSignalsFromOtherThreads()
    {
        Host local;
        const auto action = run(R"py(
got = None

def fired(n):
    global got
    got = n
)py",
            &local, Qross::ChildrenInterface::AutoConnectSignals);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        std::thread([&local] { Q_EMIT local.fired(9); }).join();
        QCoreApplication::processEvents();
        QCOMPARE(action->evaluate("got").toInt(), 9);
    }

    void wrapsScriptObjects()
    {
        const auto action = run(R"py(
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
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("results['first']").toInt(), 42);
        QCOMPARE(action->evaluate("results['second']").toInt(), 43);
        QCOMPARE(action->evaluate("results['greeting']").toString(), QStringLiteral("hi bob"));
        QCOMPARE(action->evaluate("results['methods']").toStringList(), QStringList(QStringLiteral("greet")));
        QCOMPARE(action->evaluate("results['identity']").toBool(), true);
        QCOMPARE(action->evaluate("results['nullObject']").toBool(), true);
        QVERIFY(!action->evaluate("results['missing']").isValid());
    }

    void callsScriptObjectsFromOutside()
    {
        const auto action = run(R"py(
class Answer:
    def answer(self):
        return 42

Global.keep(Answer())
)py");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        const Qross::Object::Ptr kept = m_global.kept();
        m_global.forget();
        QVERIFY(kept);
        QCOMPARE(kept->callMethod(QStringLiteral("answer")).toInt(), 42);
        QVERIFY(!kept->hadError());

        action->finalize();
        QCOMPARE(kept->callMethod(QStringLiteral("answer")).toInt(), 42);
        QVERIFY(!kept->callMethod(QStringLiteral("nope")).isValid());
        QVERIFY(kept->hadError());
    }

    void startsAfreshOnRerun()
    {
        const auto action = run("runs = globals().get('runs', 0) + 1");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        action->trigger();
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("runs").toInt(), 1);
    }

    void refusesDeletedObjects()
    {
        auto* const local = new Host;
        const auto action = run(R"py(
def name():
    return Local.objectName
)py",
            local);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        delete local;
        QVERIFY(!action->callFunction(QStringLiteral("name")).isValid());
        QVERIFY(action->context()->errorMessage().startsWith(QStringLiteral("RuntimeError")));
    }
};

QTEST_MAIN(tst_Python)
#include "tst_python.moc"
