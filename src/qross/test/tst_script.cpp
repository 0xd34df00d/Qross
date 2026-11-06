/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/script.h>
#include <optional>
#include <QtTest/QSignalSpy>
#include <QtTest/QTest>

class tst_Script : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void finishesWithoutAnInterpreter()
    {
        Qross::Script script({ .source = Qross::Code { "1", QStringLiteral("unknown") }, .interpreter = QStringLiteral("unknown") });
        QSignalSpy started(&script, &Qross::Script::started);
        QSignalSpy finished(&script, &Qross::Script::finished);
        std::optional<Qross::Error> seen;
        connect(&script, &Qross::Script::finished, &script, [&] { seen = script.error(); });

        const auto result = script.run();
        QVERIFY(!result);
        QVERIFY2(result.error().message.contains(QStringLiteral("unknown")), qPrintable(result.error().message));
        QCOMPARE(started.count(), 1);
        QCOMPARE(finished.count(), 1);
        QVERIFY(seen);
        QCOMPARE(seen->message, result.error().message);
    }

    void finishesWithoutAFile()
    {
        Qross::Script script({ .source = Qross::File { QStringLiteral("/nonexistent/unknown.js") }, .interpreter = QStringLiteral("unknown") });
        QSignalSpy started(&script, &Qross::Script::started);
        QSignalSpy finished(&script, &Qross::Script::finished);
        std::optional<Qross::Error> seen;
        connect(&script, &Qross::Script::finished, &script, [&] { seen = script.error(); });

        const auto result = script.run();
        QVERIFY(!result);
        QVERIFY2(result.error().message.startsWith(QStringLiteral("Cannot read")), qPrintable(result.error().message));
        QCOMPARE(started.count(), 1);
        QCOMPARE(finished.count(), 1);
        QVERIFY(seen);
        QCOMPARE(seen->message, result.error().message);
    }
};

QTEST_GUILESS_MAIN(tst_Script)
#include "tst_script.moc"
