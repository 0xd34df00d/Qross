/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/manager.h>
#include <qross/core/object.h>
#include <qross/core/script.h>
#include <csignal>
#include <expected>
#include <thread>
#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QPointer>
#include <QtCore/QStringListModel>
#include <QtCore/QTemporaryDir>
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
    int listeners() const { return receivers(SIGNAL(fired(int))) + receivers(SIGNAL(named(QString))); }
Q_SIGNALS:
    void fired(int n);
    void named(const QString& name);
public Q_SLOTS:
    QObject* self() { return this; }
    QAbstractItemModel* model() { return &m_model; }
    void keep(Qross::Object::Ptr object) { m_kept = object; }
    bool isNull(Qross::Object::Ptr object) { return object.isNull(); }
    Qross::Object::Ptr same(Qross::Object::Ptr object) { return object; }
    QVariant echo(const QVariant& value) { return value; }
    QStringList methods(Qross::Object::Ptr object) { return object ? object->methodNames() : QStringList(); }
    QVariant call(Qross::Object::Ptr object, const QString& method, const QVariantList& args = QVariantList())
    {
        return object ? object->callMethod(method, args).value_or(QVariant()) : QVariant();
    }
};

class tst_Ruby : public QObject
{
    Q_OBJECT

    Host m_global;
    struct sigaction m_termination = {};

    static std::unique_ptr<Qross::Script> run(const QByteArray& code, QObject* local = nullptr, Qross::ObjectOptions options = {})
    {
        Qross::Config config { .source = Qross::Code { code, QStringLiteral("tst") }, .interpreter = QStringLiteral("ruby") };
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
        sigaction(SIGTERM, nullptr, &m_termination);
    }

    void loads()
    {
        Qross::Manager& manager = Qross::Manager::self();
        QVERIFY(manager.interpreters().contains(QStringLiteral("ruby")));
        QCOMPARE(manager.interpreterNameForFile(QStringLiteral("dir/test.rb")), QStringLiteral("ruby"));
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
        const auto script = run("ok = 1\nif (");
        QVERIFY(script->error());
        QVERIFY2(script->error()->message.startsWith(QStringLiteral("SyntaxError")), qPrintable(script->error()->message));
        QCOMPARE(script->error()->line, 2);
    }

    void reportsExceptions()
    {
        const auto script = run(R"rb(
def boom
  raise ArgumentError, 'boom'
end

boom
)rb");
        QVERIFY(script->error());
        QCOMPARE(script->error()->message, QStringLiteral("ArgumentError: boom"));
        QCOMPARE(script->error()->line, 3);
        QVERIFY2(script->error()->trace.contains(QStringLiteral("boom")), qPrintable(script->error()->trace));
        QVERIFY2(script->error()->trace.contains(QStringLiteral("tst:3")), qPrintable(script->error()->trace));
    }

    void listsFunctions()
    {
        const auto script = run(R"rb(
require 'set'

def first
end

second = lambda { 0 }

class Third
end

def fourth(x) = x

not_a_function = 1
)rb");
        QVERIFY2(!script->error(), describe(*script).constData());
        QStringList names = script->functionNames();
        names.sort();
        QCOMPARE(names, QStringList({ QStringLiteral("first"), QStringLiteral("fourth") }));
    }

    void callsFunctions()
    {
        const auto script = run(R"rb(
def add(a, b) = a + b

def same(x) = x

def nothing
end
)rb");
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

        // The invokables of self are not functions of the script.
        QVERIFY(!script->call(QStringLiteral("name")));
    }

    void reportsExceptionsFromCalls()
    {
        const auto script = run(R"rb(
def bad(x)
  raise TypeError, 'bad ' + x.to_s
end
)rb");
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
        QVERIFY(!script->evaluate("nil")->isValid());

        QCOMPARE(script->evaluate("extra = 5")->toInt(), 5);
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
        const auto script = run(R"rb(
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
        QVERIFY2(!script->error(), describe(*script).constData());
        QVERIFY2(script->evaluate("ok")->toBool(), qPrintable(script->evaluate("checks.inspect")->toString()));
    }

    void connectsSignalsAutomatically()
    {
        Host local;
        const auto script = run(R"rb(
@got = nil

def fired(n)
  @got = n
end
)rb",
            &local, Qross::AutoConnectSignals);
        QVERIFY2(!script->error(), describe(*script).constData());
        Q_EMIT local.fired(7);
        Q_EMIT local.named(QStringLiteral("ignored"));
        QCOMPARE(script->evaluate("@got")->toInt(), 7);
    }

    void connectsSignalsOfManagerObjects()
    {
        Host shared;
        Qross::Manager::self().addObject(&shared, QStringLiteral("Shared"), Qross::AutoConnectSignals);
        const auto script = run(R"rb(
@got = nil

def fired(n)
  @got = n
end
)rb");
        Qross::Manager::self().removeObject(QStringLiteral("Shared"));
        QVERIFY2(!script->error(), describe(*script).constData());
        Q_EMIT shared.fired(5);
        QCOMPARE(script->evaluate("@got")->toInt(), 5);
    }

    void connectsSignalsFromScripts()
    {
        Host local;
        const auto script = run(R"rb(
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
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("@got")->toList(), QVariantList({ 3, 50 }));

        const auto noHandler = script->evaluate("Local.connect(:named)");
        QVERIFY(!noHandler);
        QVERIFY(noHandler.error().message.startsWith(QStringLiteral("ArgumentError")));
        const auto noSignal = script->evaluate("Local.connect(:self) {}");
        QVERIFY(!noSignal);
        QVERIFY(noSignal.error().message.startsWith(QStringLiteral("ArgumentError")));
    }

    void dropsConnectionsWithTheScript()
    {
        Host local;
        auto script = run(R"rb(
@got = []

Local.connect(:fired) do |n|
  @got << n
  Local.connect(:named) { |name| @got << name }
end
)rb",
            &local);
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(local.listeners(), 1);
        Q_EMIT local.fired(1);
        QCOMPARE(local.listeners(), 2);
        Q_EMIT local.named(QStringLiteral("a"));
        QCOMPARE(script->evaluate("@got")->toList(), QVariantList({ 1, QStringLiteral("a") }));

        (void)script->run();
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(local.listeners(), 1);
        Q_EMIT local.fired(2);
        QCOMPARE(script->evaluate("@got")->toList(), QVariantList({ 2 }));

        script.reset();
        QCOMPARE(local.listeners(), 0);
        Q_EMIT local.fired(3);
    }

    void ownsConnectionsMadeWhileListingMethods()
    {
        Host local;
        auto script = run(R"rb(
class Sneaky
  def public_methods(all = true)
    Local.connect(:fired) { |n| }
    super
  end
end

Global.keep(Sneaky.new)
)rb",
            &local);
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(local.listeners(), 0);
        QVERIFY(m_global.kept()->methodNames().contains(QStringLiteral("public_methods")));
        QCOMPARE(local.listeners(), 1);

        script.reset();
        QCOMPARE(local.listeners(), 0);
        m_global.forget();
    }

    void deliversSignalsFromOtherThreads()
    {
        Host local;
        const auto script = run(R"rb(
@got = nil

def fired(n)
  @got = n
end
)rb",
            &local, Qross::AutoConnectSignals);
        QVERIFY2(!script->error(), describe(*script).constData());
        std::thread([&local] { Q_EMIT local.fired(9); }).join();
        QCoreApplication::processEvents();
        QCOMPARE(script->evaluate("@got")->toInt(), 9);
    }

    void refusesOtherThreads()
    {
        const auto script = run("def answer = 42");
        QVERIFY2(!script->error(), describe(*script).constData());
        std::expected<QVariant, Qross::Error> result;
        QStringList names;
        std::thread([&] {
            result = script->evaluate("answer");
            names = script->functionNames();
        }).join();
        QVERIFY(!result);
        QVERIFY2(result.error().message.contains(QStringLiteral("thread")), qPrintable(result.error().message));
        QVERIFY(names.isEmpty());
        QVERIFY(script->error());
        QVERIFY2(script->error()->message.contains(QStringLiteral("thread")), qPrintable(script->error()->message));
        QCOMPARE(script->evaluate("answer")->toInt(), 42);
        QCOMPARE(script->functionNames(), QStringList { QStringLiteral("answer") });
    }

    void reportsConversionFailures()
    {
        const auto script = run(R"rb(
class Unprintable
  def to_s = raise('no name')
end

class Unplaceable < Time
  def utc? = raise('no zone')
end

class Unoffset < Time
  def utc_offset = raise('no offset')
end
)rb");
        QVERIFY2(!script->error(), describe(*script).constData());

        const auto key = script->evaluate("Global.echo({ Unprintable.new => 1 })");
        QVERIFY(!key);
        QVERIFY2(key.error().message.contains(QStringLiteral("no name")), qPrintable(key.error().message));
        QVERIFY(!script->evaluate("{ Unprintable.new => 1 }"));
        const auto zone = script->evaluate("Global.echo(Unplaceable.now)");
        QVERIFY(!zone);
        QVERIFY2(zone.error().message.contains(QStringLiteral("no zone")), qPrintable(zone.error().message));
        const auto offset = script->evaluate("Global.echo(Unoffset.now)");
        QVERIFY(!offset);
        QVERIFY2(offset.error().message.contains(QStringLiteral("no offset")), qPrintable(offset.error().message));
        QCOMPARE(script->evaluate("Global.echo({ 'k' => 1 })")->toMap().value(QStringLiteral("k")).toInt(), 1);
    }

    void refusesTimesBeyondRange()
    {
        const auto script = run(R"rb(
def huge = Time.at(2**100)

def far = Date.new(2**40, 1, 1)
)rb");
        QVERIFY2(!script->error(), describe(*script).constData());

        const auto huge = script->call(QStringLiteral("huge"));
        QVERIFY(!huge);
        QVERIFY2(huge.error().message.contains(QStringLiteral("range")), qPrintable(huge.error().message));
        const auto far = script->call(QStringLiteral("far"));
        QVERIFY(!far);
        QVERIFY2(far.error().message.startsWith(QStringLiteral("RangeError")), qPrintable(far.error().message));

        const auto passed = script->evaluate("Global.echo(Time.at(2**100))");
        QVERIFY(!passed);
        QVERIFY2(passed.error().message.contains(QStringLiteral("range")), qPrintable(passed.error().message));
        QVERIFY(!script->evaluate("[Time.at(2**100)]"));
        QVERIFY(!script->evaluate("{ 'time' => Time.at(2**100) }"));
        QCOMPARE(script->evaluate("Global.echo(Time.at(0).utc).year")->toInt(), 1970);
    }

    void keepsTimeZones()
    {
        const auto script = run(R"rb(
east = Time.new(2026, 1, 2, 12, 0, 0, '+03:00')
far = Time.new(2026, 1, 2, 12, 0, 0, '+23:00')
checks = [
  Global.echo(east) == east,
  Global.echo(east).utc_offset == 3 * 3600,
  Global.echo(far) == far,
  Global.echo(far).utc?,
]
)rb");
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("checks")->toList(), QVariantList({ true, true, true, true }));
    }

    void wrapsScriptObjects()
    {
        const auto script = run(R"rb(
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
        const auto script = run(R"rb(
class Answer
  def answer = 42
end

Global.keep(Answer.new)
)rb");
        QVERIFY2(!script->error(), describe(*script).constData());
        const Qross::Object::Ptr kept = m_global.kept();
        m_global.forget();
        QVERIFY(kept);
        QCOMPARE(kept->callMethod(QStringLiteral("answer"))->toInt(), 42);

        script->reset();
        QCOMPARE(kept->callMethod(QStringLiteral("answer"))->toInt(), 42);
        QVERIFY(!kept->callMethod(QStringLiteral("nope")));
    }

    void survivesGarbageCollection()
    {
        Host local;
        const auto script = run(R"rb(
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
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("@got")->toList(), QVariantList({ 1 }));
        QCOMPARE(script->evaluate("wrapper.objectName")->toString(), QString());
        QCOMPARE(script->evaluate("wrapper == Local")->toBool(), true);
        const Qross::Object::Ptr kept = m_global.kept();
        m_global.forget();
        QCOMPARE(kept->callMethod(QStringLiteral("answer"))->toInt(), 42);
    }

    void startsAfreshOnRerun()
    {
        const auto script = run("@runs = (@runs || 0) + 1");
        QVERIFY2(!script->error(), describe(*script).constData());
        (void)script->run();
        QVERIFY2(!script->error(), describe(*script).constData());
        QCOMPARE(script->evaluate("@runs")->toInt(), 1);
    }

    void refusesDeletedObjects()
    {
        auto* const local = new Host;
        const auto script = run(R"rb(
def name_of = Local.objectName
)rb",
            local);
        QVERIFY2(!script->error(), describe(*script).constData());
        delete local;
        const auto failed = script->call(QStringLiteral("name_of"));
        QVERIFY(!failed);
        QVERIFY(failed.error().message.startsWith(QStringLiteral("RuntimeError")));
    }

    void reportsAFrozenLoadPath()
    {
        QTemporaryDir first;
        QTemporaryDir second;
        QVERIFY(first.isValid() && second.isValid());
        const auto write = [](const QString& path) {
            QFile file(path);
            return file.open(QIODevice::WriteOnly) && file.write("def answer = 42\n") > 0;
        };
        const QString before = first.filePath(QStringLiteral("before.rb"));
        const QString after = second.filePath(QStringLiteral("after.rb"));
        QVERIFY(write(before) && write(after));

        Qross::Script script(Qross::Config { .source = Qross::File { before }, .interpreter = QStringLiteral("ruby") });
        QVERIFY2(script.run(), describe(script).constData());
        QCOMPARE(script.call(QStringLiteral("answer"))->toInt(), 42);

        // Freezing $LOAD_PATH is for good, which is why this test runs last.
        QVERIFY(!run("$LOAD_PATH.freeze")->error());
        Qross::Script frozen(Qross::Config { .source = Qross::File { after }, .interpreter = QStringLiteral("ruby") });
        const auto result = frozen.run();
        QVERIFY(!result);
        QVERIFY2(result.error().message.contains(QStringLiteral("frozen")), qPrintable(result.error().message));
        QVERIFY(frozen.error());
        QVERIFY(!frozen.evaluate("1"));
    }
};

QTEST_MAIN(tst_Ruby)
#include "tst_ruby.moc"
