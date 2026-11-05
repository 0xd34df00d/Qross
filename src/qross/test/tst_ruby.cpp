/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/context.h>
#include <qross/core/manager.h>
#include <qross/core/object.h>
#include <qross/core/script.h>
#include <csignal>
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

class tst_Ruby : public QObject
{
    Q_OBJECT

    Host m_global;
    struct sigaction m_termination = {};

    static std::unique_ptr<Qross::Script> run(const QByteArray& code, QObject* local = nullptr, Qross::ChildrenInterface::Options options = Qross::ChildrenInterface::NoOption)
    {
        auto action = std::make_unique<Qross::Script>(nullptr, QStringLiteral("tst"));
        action->setInterpreter(QStringLiteral("ruby"));
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
        sigaction(SIGTERM, nullptr, &m_termination);
    }

    void loads()
    {
        Qross::Manager& manager = Qross::Manager::self();
        QVERIFY(manager.interpreters().contains(QStringLiteral("ruby")));
        QCOMPARE(manager.interpreternameForFile(QStringLiteral("dir/test.rb")), QStringLiteral("ruby"));
        QVERIFY(manager.interpreter(QStringLiteral("ruby")));
    }

    void keepsSignalsWithTheApplication()
    {
        QVERIFY(Qross::Manager::self().interpreter(QStringLiteral("ruby")));
        struct sigaction termination = {};
        sigaction(SIGTERM, nullptr, &termination);
        QCOMPARE(reinterpret_cast<void*>(termination.sa_handler), reinterpret_cast<void*>(m_termination.sa_handler));
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
        const auto action = run(R"rb(
def boom
  raise ArgumentError, 'boom'
end

boom
)rb");
        QVERIFY(action->hadError());
        QCOMPARE(action->errorMessage(), QStringLiteral("ArgumentError: boom"));
        QCOMPARE(action->errorLineNo(), 3);
        QVERIFY2(action->errorTrace().contains(QStringLiteral("boom")), qPrintable(action->errorTrace()));
        QVERIFY2(action->errorTrace().contains(QStringLiteral("tst:3")), qPrintable(action->errorTrace()));
    }

    void listsFunctions()
    {
        const auto action = run(R"rb(
require 'set'

def first
end

second = lambda { 0 }

class Third
end

def fourth(x) = x

not_a_function = 1
)rb");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QStringList names = action->functionNames();
        names.sort();
        QCOMPARE(names, QStringList({ QStringLiteral("first"), QStringLiteral("fourth") }));
    }

    void callsFunctions()
    {
        const auto action = run(R"rb(
def add(a, b) = a + b

def same(x) = x

def nothing
end
)rb");
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

        // Qt methods of the action are not functions of the script.
        QVERIFY(!action->callFunction(QStringLiteral("trigger")).isValid());
        QVERIFY(action->context()->hadError());
    }

    void reportsExceptionsFromCalls()
    {
        const auto action = run(R"rb(
def bad(x)
  raise TypeError, 'bad ' + x.to_s
end
)rb");
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
        QVERIFY(!action->evaluate("nil").isValid());

        QCOMPARE(action->evaluate("extra = 5").toInt(), 5);
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
        const auto action = run(R"rb(
checks = [
  name == 'tst',
  self.name == 'tst',
  Qross.interpreters.include?('ruby'),
  Global.objectName == 'Global',
  Local.objectName == 'Local',
  Local() == Local,
  Global.self == Global,
  Global.self != Local,
  Global.Fast == 1 && Local.Slow == 2 && Global.self.Slow == 2,
  Global.class::Fast == 1,
  Global.className == 'Host',
  Global.is_a?(::Qross::QObject),
  Global.class.name == 'Qross::Host',
  Global.respond_to?(:fired),
  Global.respond_to?(:objectName=),
  Global.inspect.include?('Global'),
  [Global, Global.self].uniq.size == 1,
]
ok = checks.all?
)rb",
            &local);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QVERIFY2(action->evaluate("ok").toBool(), qPrintable(action->evaluate("checks.inspect").toString()));
    }

    void connectsSignalsAutomatically()
    {
        Host local;
        const auto action = run(R"rb(
@got = nil

def fired(n)
  @got = n
end
)rb",
            &local, Qross::ChildrenInterface::AutoConnectSignals);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        Q_EMIT local.fired(7);
        Q_EMIT local.named(QStringLiteral("ignored"));
        QCOMPARE(action->evaluate("@got").toInt(), 7);
    }

    void connectsSignalsFromScripts()
    {
        Host local;
        const auto action = run(R"rb(
@got = []

def on_fired(n)
  @got << n * 10
end

handler = Local.connect(:fired) { |n| @got << n }
Local.fired(3)
Local.disconnect(:fired, handler)
Local.fired(4)

Local.connect('fired(int)', method(:on_fired))
Local.fired(5)
Local.disconnect(:fired, method(:on_fired))
Local.fired(6)

Local.connect(:fired) { |n| @got << -n }
Local.disconnect(:fired)
Local.fired(7)
)rb",
            &local);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("@got").toList(), QVariantList({ 3, 50 }));

        QVERIFY(!action->evaluate("Local.connect(:named)").isValid());
        QVERIFY(action->context()->errorMessage().startsWith(QStringLiteral("ArgumentError")));
        QVERIFY(!action->evaluate("Local.connect(:self) {}").isValid());
        QVERIFY(action->context()->errorMessage().startsWith(QStringLiteral("ArgumentError")));
    }

    void deliversSignalsFromOtherThreads()
    {
        Host local;
        const auto action = run(R"rb(
@got = nil

def fired(n)
  @got = n
end
)rb",
            &local, Qross::ChildrenInterface::AutoConnectSignals);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        std::thread([&local] { Q_EMIT local.fired(9); }).join();
        QCoreApplication::processEvents();
        QCOMPARE(action->evaluate("@got").toInt(), 9);
    }

    void refusesOtherThreads()
    {
        const auto action = run("answer = 42");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QVariant result;
        std::thread([&] { result = action->evaluate("answer"); }).join();
        QVERIFY(!result.isValid());
        QVERIFY2(action->context()->errorMessage().contains(QStringLiteral("thread")), qPrintable(action->context()->errorMessage()));
        QCOMPARE(action->evaluate("answer").toInt(), 42);
    }

    void wrapsScriptObjects()
    {
        const auto action = run(R"rb(
class Counter
  def initialize(start)
    @n = start
  end

  def next
    @n += 1
  end
end

class Greeter
  def greet(name) = 'hi ' + name
end

counter = Counter.new(41)
results = {
  'first' => Global.call(counter, 'next'),
  'second' => Global.call(counter, 'next'),
  'greeting' => Global.call(Greeter.new, 'greet', ['bob']),
  'methods' => Global.methods(Greeter.new),
  'identity' => Global.same(counter).equal?(counter),
  'nullObject' => Global.isNull(nil),
  'missing' => Global.call(counter, 'nope'),
}
)rb");
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
        const auto action = run(R"rb(
class Answer
  def answer = 42
end

Global.keep(Answer.new)
)rb");
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

    void survivesGarbageCollection()
    {
        Host local;
        const auto action = run(R"rb(
class Kept
  def answer = 42
end

@got = []
Local.connect(:fired) { |n| @got << n }
Global.keep(Kept.new)
wrapper = Local.self
GC.start
GC.compact
1000.times { Object.new }
GC.start
Local.fired(1)
)rb",
            &local);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("@got").toList(), QVariantList({ 1 }));
        QCOMPARE(action->evaluate("wrapper.objectName").toString(), QString());
        QCOMPARE(action->evaluate("wrapper == Local").toBool(), true);
        const Qross::Object::Ptr kept = m_global.kept();
        m_global.forget();
        QCOMPARE(kept->callMethod(QStringLiteral("answer")).toInt(), 42);
    }

    void startsAfreshOnRerun()
    {
        const auto action = run("@runs = (@runs || 0) + 1");
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        action->trigger();
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        QCOMPARE(action->evaluate("@runs").toInt(), 1);
    }

    void refusesDeletedObjects()
    {
        auto* const local = new Host;
        const auto action = run(R"rb(
def name_of = Local.objectName
)rb",
            local);
        QVERIFY2(!action->hadError(), qPrintable(action->errorMessage()));
        delete local;
        QVERIFY(!action->callFunction(QStringLiteral("name_of")).isValid());
        QVERIFY(action->context()->errorMessage().startsWith(QStringLiteral("RuntimeError")));
    }
};

QTEST_MAIN(tst_Ruby)
#include "tst_ruby.moc"
