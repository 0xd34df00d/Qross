/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <qross/core/metafunction.h>
#include <QCoreApplication>
#include <QRect>
#include <QRegularExpression>
#include <QTest>

class Emitter : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
Q_SIGNALS:
    void nothing();
    void number(int value);
    void text(const QString& value);
    void several(int a, const QString& b, const QStringList& c);
    void object(QObject* obj);
    void rect(const QRect& r);
};

class Recorder : public Qross::MetaFunction
{
    QList<QVariantList> m_calls;
public:
    using MetaFunction::MetaFunction;

    const QList<QVariantList>& calls() const
    {
        return m_calls;
    }
protected:
    void callback(const QVariantList& args) override
    {
        m_calls.append(args);
    }
};

class tst_MetaFunction : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void forwardsArguments()
    {
        Emitter e;
        Recorder r(&e, QMetaMethod::fromSignal(&Emitter::several));
        QVERIFY(r.isConnected());
        QCOMPARE(r.signalSender(), &e);
        QCOMPARE(r.signal().name(), QByteArray("several"));

        Q_EMIT e.several(42, "forty-two", QStringList { "a", "b" });

        QCOMPARE(r.calls().size(), 1);
        const auto& args = r.calls()[0];
        QCOMPARE(args.size(), 3);
        QCOMPARE(args[0].typeId(), int(QMetaType::Int));
        QCOMPARE(args[0].toInt(), 42);
        QCOMPARE(args[1].typeId(), int(QMetaType::QString));
        QCOMPARE(args[1].toString(), QString("forty-two"));
        QCOMPARE(args[2].typeId(), int(QMetaType::QStringList));
        QCOMPARE(args[2].toStringList(), QStringList({ "a", "b" }));
    }

    void forwardsNoArguments()
    {
        Emitter e;
        Recorder r(&e, QMetaMethod::fromSignal(&Emitter::nothing));
        QVERIFY(r.isConnected());
        Q_EMIT e.nothing();
        Q_EMIT e.nothing();
        QCOMPARE(r.calls().size(), 2);
        QVERIFY(r.calls()[0].isEmpty());
    }

    void forwardsPointersAndValueTypes()
    {
        Emitter e;
        Recorder objects(&e, QMetaMethod::fromSignal(&Emitter::object));
        Recorder rects(&e, QMetaMethod::fromSignal(&Emitter::rect));

        Q_EMIT e.object(&e);
        Q_EMIT e.rect(QRect(1, 2, 3, 4));

        QCOMPARE(objects.calls().size(), 1);
        QCOMPARE(objects.calls()[0][0].value<QObject*>(), &e);
        QCOMPARE(rects.calls().size(), 1);
        QCOMPARE(rects.calls()[0][0].toRect(), QRect(1, 2, 3, 4));
    }

    void looksUpBySignature()
    {
        Emitter e;
        Recorder r(&e, QByteArray("text( const QString & )"));
        QVERIFY(r.isConnected());
        Q_EMIT e.text("hello");
        QCOMPARE(r.calls().size(), 1);
        QCOMPARE(r.calls()[0][0].toString(), QString("hello"));
    }

    void refusesInvalidSignals()
    {
        Emitter e;
        QTest::ignoreMessage(QtWarningMsg, QRegularExpression("not a signal"));
        Recorder invalid(&e, QMetaMethod());
        QVERIFY(!invalid.isConnected());

        QTest::ignoreMessage(QtWarningMsg, QRegularExpression("not a signal"));
        Recorder unknown(&e, QByteArray("noSuchSignal()"));
        QVERIFY(!unknown.isConnected());

        QTest::ignoreMessage(QtWarningMsg, QRegularExpression("not a signal"));
        const QMetaMethod slot = e.metaObject()->method(e.metaObject()->indexOfSlot("deleteLater()"));
        QVERIFY(slot.isValid());
        Recorder notASignal(&e, slot);
        QVERIFY(!notASignal.isConnected());

        QTest::ignoreMessage(QtWarningMsg, QRegularExpression("no sender"));
        Recorder noSender(nullptr, QMetaMethod::fromSignal(&Emitter::nothing));
        QVERIFY(!noSender.isConnected());

        QObject plain;
        QTest::ignoreMessage(QtWarningMsg, QRegularExpression("does not belong"));
        Recorder wrongClass(&plain, QMetaMethod::fromSignal(&Emitter::nothing));
        QVERIFY(!wrongClass.isConnected());
    }

    void survivesSenderDeletion()
    {
        auto* e = new Emitter;
        Recorder r(e, QMetaMethod::fromSignal(&Emitter::number));
        QVERIFY(r.isConnected());
        delete e;
        QVERIFY(!r.isConnected());
        QVERIFY(r.signalSender() == nullptr);
    }

    void stopsAfterRelayDeletion()
    {
        Emitter e;
        auto* r = new Recorder(&e, QMetaMethod::fromSignal(&Emitter::number));
        QVERIFY(r->isConnected());
        delete r;
        Q_EMIT e.number(1); // must not reach the deleted relay
    }

    void stopsAfterDisconnect()
    {
        Emitter e;
        Recorder r(&e, QMetaMethod::fromSignal(&Emitter::number));
        Q_EMIT e.number(1);
        r.disconnectSignal();
        QVERIFY(!r.isConnected());
        Q_EMIT e.number(2);
        QCOMPARE(r.calls().size(), 1);
    }

    void deliversQueuedCalls()
    {
        Emitter e;
        Recorder r(&e, QMetaMethod::fromSignal(&Emitter::several), Qt::QueuedConnection);
        QVERIFY(r.isConnected());

        Q_EMIT e.several(7, "seven", QStringList { "x" });
        QCOMPARE(r.calls().size(), 0);

        QCoreApplication::processEvents();
        QCOMPARE(r.calls().size(), 1);
        QCOMPARE(r.calls()[0][0].toInt(), 7);
        QCOMPARE(r.calls()[0][1].toString(), QString("seven"));
        QCOMPARE(r.calls()[0][2].toStringList(), QStringList { "x" });
    }
};

QTEST_GUILESS_MAIN(tst_MetaFunction)

#include "tst_metafunction.moc"
