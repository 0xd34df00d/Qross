#!/usr/bin/env qrosstest
# Qross - scripting bridge for Qt applications.
# SPDX-License-Identifier: LGPL-2.0-or-later

# Run by qrosstest, which publishes TestObject1 and TestObject2 through
# the manager and TestObject3 and TestObject4 through the script.

import datetime
import unittest

script = self


class TestQross(unittest.TestCase):
    def setUp(self):
        self.object1 = TestObject1
        self.object2 = TestObject2

    def testObjects(self):
        self.assertEqual(self.object1.name(), "TestObject1")
        self.assertEqual(self.object2.objectName, "TestObject2")
        self.assertEqual(TestObject3.name(), "TestObject3")
        self.assertEqual(TestObject4.name(), "TestObject4")
        self.assertEqual(self.object1.className(), "TestObject")
        self.assertEqual(self.object1.myself(), self.object1)
        self.assertEqual(self.object1.myself2(), self.object1)
        self.assertNotEqual(self.object1, self.object2)
        self.assertEqual(self.object1.func_qobject_qobject(self.object2), self.object2)
        self.assertEqual(self.object1.func_testobject_testobject(self.object2), self.object2)
        self.assertEqual(self.object1.func_testobject_qobject(self.object2), self.object2)
        self.assertIsNone(self.object1.func_qobject_qobject(None))
        self.assertIsNone(self.object1.func_qwidget_qwidget(None))
        self.assertEqual(self.object1.func_createChildTestObject("MyChildObject").name(), "MyChildObject")
        self.assertIn("func_int_int", dir(self.object1))
        with self.assertRaises(TypeError):
            self.object1.func_qobject_qobject("not an object")
        with self.assertRaises(TypeError):
            self.object1.func_qwidget_qwidget(self.object2)
        with self.assertRaises(TypeError):
            self.object1.func_int_int(1, 2)
        with self.assertRaises(AttributeError):
            self.object1.noSuchMethod()

    def testNumbers(self):
        self.assertIs(self.object1.func_bool_bool(True), True)
        self.assertIs(self.object1.func_bool_bool(False), False)
        for value in (0, 177321, -98765):
            self.assertEqual(self.object1.func_int_int(value), value)
        for value in (0, 177321):
            self.assertEqual(self.object1.func_uint_uint(value), value)
        for value in (0.0, 1773.2177, -548993.271993):
            self.assertEqual(self.object1.func_double_double(value), value)
        for value in (0, 7379, -6384673, -2 ** 40):
            self.assertEqual(self.object1.func_qlonglong_qlonglong(value), value)
        for value in (0, 378972, 2 ** 63):
            self.assertEqual(self.object1.func_qulonglong_qulonglong(value), value)

    def testStrings(self):
        for value in ("", " ", " Another \n\r Test!   $%&\" ", "áêïòñα", "α"):
            self.assertEqual(self.object1.func_qstring_qstring(value), value)
        self.assertEqual(self.object1.func_qstring_qstring_int("x", 5), "x,5")
        self.assertEqual(self.object1.func_qbytearray_qbytearray(b"bytes"), b"bytes")
        self.assertEqual(self.object1.func_qbytearray_qbytearray("text"), b"text")

    def testLists(self):
        self.assertEqual(self.object1.func_qstringlist_qstringlist([]), [])
        self.assertEqual(self.object1.func_qstringlist_qstringlist([" string1", "string2 "]), [" string1", "string2 "])
        self.assertEqual(self.object1.func_qstringlist_qstringlist(("a", "b")), ["a", "b"])
        self.assertEqual(self.object1.func_qvariantlist_qvariantlist([]), [])
        self.assertEqual(self.object1.func_qvariantlist_qvariantlist([[[[]], []]]), [[[[]], []]])
        self.assertEqual(self.object1.func_qvariantlist_qvariantlist(["A string", [17539, -8591], [5.32, -842.775]]), ["A string", [17539, -8591], [5.32, -842.775]])
        self.assertEqual(self.object1.func_qvariantlist_qvariantlist([[True, [], False, "Other String"], "test"]), [[True, [], False, "Other String"], "test"])
        self.assertEqual(self.object1.func_qvariantlist_qvariantlist([[17, 52], [], {}, [84.21, 936.821]]), [[17, 52], [], {}, [84.21, 936.821]])
        wrapped = self.object1.func_qobject2qvariantlist(self.object2)
        self.assertEqual(wrapped, [self.object2])
        self.assertEqual(self.object1.func_qvariantlist2qobject(wrapped), self.object2)
        self.assertEqual(self.object1.myself3(), [self.object1])
        self.assertEqual(self.object1.func_testobjectlist_testobjectlist([self.object1, self.object2]), [self.object1, self.object2])

    def testMaps(self):
        for value in ({}, {"3": -837, "1": 73682, "2": 285}, {"c": 84.24, "a": -6892.957}, {"key1": True, "key2": False},
                      {"key 2": "  Some String  ", "key 3": "oThEr StRiNg"}, {" key4 ": [12.5, True], " key5 ": [83.002, "test"]},
                      {"  key7  ": {}, "  key6  ": {}}):
            self.assertEqual(self.object1.func_qvariantmap_qvariantmap(value), value)

    def testVariants(self):
        for value in (0.0, True, False, 187937, -69825, 8632.274, -8632.351, " Test \n\r This String $%&\"", None, [1, "a"], {"a": 1}):
            self.assertEqual(self.object1.func_qvariant_qvariant(value), value)
        self.assertEqual(self.object1.func_qvariant_qvariant(self.object2), self.object2)

    def testGeometry(self):
        for value in ((0, 0), (12, -94), (-7264, 6224)):
            self.assertEqual(self.object1.func_qsize_qsize(value), value)
            self.assertEqual(self.object1.func_qpoint_qpoint(list(value)), value)
        for value in ((0.0, 0.0), (-956.0, 75.21), (-14.21, -535.0)):
            self.assertEqual(self.object1.func_qsizef_qsizef(value), value)
            self.assertEqual(self.object1.func_qpointf_qpointf(value), value)
        for value in ((0, 0, 0, 0), (-1, -2, 3, 4), (10, 20, -30, -40)):
            self.assertEqual(self.object1.func_qrect_qrect(value), value)
        for value in ((0.0, 0.0, 0.0, 0.0), (-1.1, -2.2, 3.3, 4.4)):
            self.assertEqual(self.object1.func_qrectf_qrectf(value), value)
        with self.assertRaises(TypeError):
            self.object1.func_qrect_qrect((1, 2))

    def testColorsAndUrls(self):
        self.assertIsNone(self.object1.func_qcolor_qcolor(None))
        self.assertEqual(self.object1.func_qcolor_qcolor("#0066ff"), "#0066ff")
        self.assertEqual(self.object1.func_qcolor_qcolor("#800066ff"), "#800066ff")
        self.assertEqual(self.object1.func_qurl_qurl(None), "")
        for value in ("/home/myuser", "file:///home/myuser/myfile.txt", "http://myname:mypass@qross.dipe.org?404.cgi?test=123&test2=456"):
            self.assertEqual(self.object1.func_qurl_qurl(value), value)

    def testDates(self):
        when = datetime.datetime(2020, 1, 2, 3, 4, 5, 6000)
        self.assertEqual(self.object1.func_qdatetime_qdatetime(when), when)
        self.assertEqual(self.object1.func_qdate_qdate(when.date()), when.date())
        self.assertEqual(self.object1.func_qtime_qtime(when.time()), when.time())

    def testProperties(self):
        self.object1.boolProperty = True
        self.assertIs(self.object1.boolProperty, True)
        self.object1.intProperty = 20
        self.assertEqual(self.object1.intProperty, 20)
        self.object1.doubleProperty = 7436.671
        self.assertEqual(self.object1.doubleProperty, 7436.671)
        self.object1.stringProperty = " SoMe StRiNg "
        self.assertEqual(self.object1.stringProperty, " SoMe StRiNg ")
        self.object1.stringListProperty = ["TestString", " Other String "]
        self.assertEqual(self.object1.stringListProperty, ["TestString", " Other String "])
        self.object1.listProperty = [True, [2464, -8295], -572.07516, "test", []]
        self.assertEqual(self.object1.listProperty, [True, [2464, -8295], -572.07516, "test", []])
        with self.assertRaises(AttributeError):
            self.object1.noSuchProperty = 1

        self.object1.setProperty("intProperty", -75825)
        self.assertEqual(self.object1.property("intProperty"), -75825)
        self.assertEqual(self.object1.intProperty, -75825)
        self.assertEqual(self.object1.property("dynamicProperty"), ["Some String", 99])
        self.assertEqual(self.object1.dynamicProperty, ["Some String", 99])
        self.object1.setProperty("newDynamicProperty", "New Dynamic Property")
        self.assertEqual(self.object1.newDynamicProperty, "New Dynamic Property")
        self.object1.newDynamicProperty = 5
        self.assertEqual(self.object1.property("newDynamicProperty"), 5)

    def testEnumerations(self):
        self.assertEqual(self.object1.TESTENUM1, 1)
        self.assertEqual(self.object1.TESTENUM2, 2)
        self.assertEqual(self.object1.TESTENUM3, 4)
        self.assertEqual(self.object1.TESTENUM4, 8)
        self.assertEqual(self.object1.myself().TESTENUM2, 2)

    def testSignals(self):
        received = []
        self.object1.signalString.connect(received.append)
        self.object1.emitSignalString("more beer")
        self.assertEqual(received, ["more beer"])
        self.object1.signalString("direct")
        self.assertEqual(received[-1], "direct")
        self.object1.signalObject.connect(lambda o: received.append(o.name()))
        self.object1.emitSignalObject(self.object2)
        self.assertEqual(received[-1], "TestObject2")

        def onInt(i):
            received.append(i)

        self.object1.signalInt.connect(onInt)
        self.object1.emitSignalInt(9)
        self.assertEqual(received[-1], 9)
        self.object1.signalInt.disconnect(onInt)
        self.object1.emitSignalInt(10)
        self.assertEqual(received[-1], 9)
        with self.assertRaises(TypeError):
            self.object1.func_void.connect(onInt)

    def testScript(self):
        self.assertIn("testFunction", script.functionNames())

    def testScriptObjects(self):
        class MyClass:
            def __init__(self, result):
                self.result = result

            def myMethod(self):
                return self.result

            def add(self, a, b):
                return a + b

        instance = MyClass("my string")
        self.assertEqual(self.object1.call_qrossobject_method(instance, "myMethod"), "my string")
        self.assertEqual(self.object1.call_qrossobject_method(instance, "add", [40, 2]), 42)
        self.assertEqual(self.object1.get_qrossobject_methods(instance), ["add", "myMethod"])
        self.assertIs(self.object1.func_qrossobject_qrossobject(instance), instance)

    def testOtherObject(self):
        other1 = self.object1.func_otherobject("OtherObject1")
        other2 = self.object1.func_otherobject("OtherObject2")
        self.assertEqual(other1.objectName, "OtherObject1_wrapper")
        self.assertEqual(other2.parentObject().objectName, "OtherObject2")
        self.assertEqual(self.object1.func_otherobject_otherobject(other1).objectName, other1.objectName)
        both = self.object1.func_otherobjectlist_otherobjectlist([other1, other2])
        self.assertEqual(len(both), 2)
        self.assertEqual(both[0].objectName, "OtherObject1_wrapper")
        self.assertEqual(both[1].parentObject().objectName, "OtherObject2")


def testFunction(*args):
    return args


suite = unittest.defaultTestLoader.loadTestsFromTestCase(TestQross)
result = unittest.TextTestRunner(verbosity=2).run(suite)
if not result.wasSuccessful():
    raise RuntimeError("%d checks failed" % (len(result.failures) + len(result.errors)))
