# Qross

Qross embeds scripting into Qt 6 applications. The application publishes
QObjects, and scripts in JavaScript, Python or Ruby call their slots and
invokables, read and write their properties, connect to their signals and
use their enums, all through the metaobject system. The C++ side needs no
binding generator and no dependency on Qross: any QObject will do.

Qross is a fork of KDE's Kross with the KDE parts removed. It depends on
Qt only.

## Backends

| Language   | Interpreter name | Files           | Built on                |
| ---------- | ---------------- | --------------- | ----------------------- |
| JavaScript | `javascript`     | `*.js`, `*.es`  | QQmlEngine              |
| Python     | `python`         | `*.py`          | CPython 3.12 or later   |
| Ruby       | `ruby`           | `*.rb`          | Ruby 3.2 or later       |

`qtscript` is still accepted as a name for the JavaScript backend. Each
backend is a plugin loaded on first use, so an application pays only for
the languages its scripts use, and each can be left out of the build with
the matching option: `QROSS_WITH_JAVASCRIPT`, `QROSS_WITH_PYTHON`,
`QROSS_WITH_RUBY`.

## Building

Qross needs CMake 4.3, a C++26 compiler (GCC 16 is the one it is
developed and tested with), Qt 6.8 or later with Core, Gui, Widgets
and Test, plus Qml for the JavaScript backend, the Python 3.12 embedding
development files for the Python backend and Ruby 3.2 for the Ruby backend.

    cmake -S src/qross -B build -G Ninja
    cmake --build build
    ctest --test-dir build

Installing provides:

- `libqrosscore-qt6`, the headers under `qross/core/` and the pkg-config
  file `qrosscore`;
- the backend plugins `qrossjs-qt6`, `qrosspython-qt6` and `qrossruby-qt6`
  in the library directory;
- `qross-qt6`, which runs the script files named on its command line with
  the backend their extension selects.

Plugins are looked up in the directories listed in `QROSS_PLUGIN_PATH`,
then in the installation's library directory, then in Qt's library paths.
The tests of a build tree point the variable at its `plugins/` directory.

## From the application

```cpp
#include <qross/core/manager.h>
#include <qross/core/script.h>

// Visible to every script, under its object name.
Qross::Manager::self().addObject(document);

Qross::Script greeter({
    .source = Qross::Code { "def greet(name):\n    return 'hello ' + name + ' from ' + Document.title\n", QStringLiteral("greeter") },
    .interpreter = QStringLiteral("python"),
    // Visible to this script only; a script function named like one of
    // the view's signals is connected to it after each run.
    .objects = { { view, QStringLiteral("View"), Qross::AutoConnectSignals } },
});

if (const auto result = greeter.run(); !result)
    qWarning() << result.error().message << "at line" << result.error().line;
const QVariant greeting = greeter.call(QStringLiteral("greet"), { QStringLiteral("world") }).value_or(QVariant());
```

A `Script` is built from a `Config`: a `File` or `Code` source, the
interpreter (deduced from the file extension when left empty), overrides
of the backend's options and the objects the script sees. `run()` runs
the source afresh each time, reading a `File` again; afterwards `call()`
calls a function the script defined, `evaluate()` runs code in the
script's context and `functionNames()` lists what can be called.
`run()`, `call()` and `evaluate()` return `std::expected`, with an
`Error` carrying the message, the trace and the line; `error()` keeps
the latest one. `reset()` drops the state of the runs so far. Objects
can be added with `addObject()` between runs; everything else is fixed
at construction.

Slots and properties exchange the Qt value types, containers of them,
pointers to QObjects and `Qross::Object::Ptr`. The latter carries a
script object, such as a Python instance or a Ruby object, into C++, where
`callMethod()` calls its methods. Handed back to a Python or Ruby script,
it is the same object again; JavaScript gets a value whose `value()` is
the object, since the QML engine substitutes nothing else for a C++
type. For return types the metatype system cannot convert,
such as pointers to classes that are not QObjects, a `MetaTypeHandler`
registered with the `Manager` produces something scripts can use, usually
a QObject implementing `WrapperInterface` so that it unwraps on the way
back.

## From the scripts

Scripts see the script as `self`, the manager as `Qross` and every
published object under its name. Slots, invokables and signals are
methods, calling a signal emits it, properties are attributes and enum
keys are attributes of the object. Given a `Player` with a `volume`
property, a `play(QString)` slot and a `finished(int)` signal:

```js
Player.volume = 50;
Player.play("song.ogg");
Player.finished.connect(function(code) { Player.play("next.ogg"); });
```

```python
Player.volume = 50
Player.play("song.ogg")
Player.finished.connect(lambda code: Player.play("next.ogg"))
```

```ruby
Player.volume = 50
Player.play("song.ogg")
Player.connect(:finished) { |code| Player.play("next.ogg") }
```

A function defined at the top level of the script and named like a signal
of an object published with `AutoConnectSignals` is connected to that
signal once the script has run, in all three languages.

| C++                       | JavaScript                        | Python                 | Ruby                      |
| ------------------------- | --------------------------------- | ---------------------- | ------------------------- |
| QString                   | string                            | str                    | String                    |
| QUrl, QColor              | string in, object with toString() out | str                | String                    |
| QByteArray                | ArrayBuffer                       | bytes                  | String, binary encoding   |
| QVariantList, QStringList | Array                             | list                   | Array                     |
| QVariantMap               | object                            | dict                   | Hash                      |
| QSize, QPoint, QRect      | object with x, y, width, height   | tuple                  | Array of numbers          |
| QDateTime, QDate, QTime   | Date                              | datetime, date, time   | Time, Date, ISO string    |
| QObject*                  | wrapper                           | wrapper                | wrapper                   |
| Qross::Object::Ptr        | value whose value() is the object | the script object      | the script object         |

A `QDateTime` in local time is a naive `datetime` in Python and comes
back as one; any other `QDateTime` carries its offset from UTC both ways.
An offset Qt cannot hold, beyond sixteen hours or with a fraction of a
second, arrives as UTC at the same instant.

Objects stay owned by the application; a wrapper of an object that has
been deleted raises an error when used. The JavaScript engine follows the
QML ownership rules, so a parentless QObject returned from a slot becomes
garbage-collectable by the engine unless it is given a parent or
`QJSEngine::CppOwnership`.

A script runs on the thread that calls its `run()`, `call()` or
`evaluate()`. Python callables can be called from any thread. Ruby runs
only on the thread that started it, and signals emitted elsewhere reach
their Ruby handlers through that thread's event loop. JavaScript engines
must stay on their thread.

The JavaScript backend imports QtQml into every engine, which makes
QModelIndex and its relatives usable from scripts; `.options = { {
QStringLiteral("qml"), false } }` in the script's `Config` turns that
off.

## Status

The API around `Script` and `Manager` was redesigned in this cycle;
CHANGES lists what moved. The last tagged release, 0.3.2, is the Qt 4
and Qt 5 code base.

Qross is distributed under the GNU Lesser General Public License,
version 2.0 or later.
