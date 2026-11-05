#!/usr/bin/env qrosstest
/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

// Run by qrosstest, which publishes TestObject1 and TestObject2 through
// the manager and TestObject3 and TestObject4 through the action.

function UnitTest() {
    var passed = 0;
    var failed = 0;

    function same(actual, expected) {
        if (Array.isArray(expected)) {
            if (actual === null || actual === undefined || actual.length !== expected.length)
                return false;
            for (var i = 0; i < expected.length; ++i)
                if (!same(actual[i], expected[i]))
                    return false;
            return true;
        }
        if (expected !== null && typeof expected === 'object') {
            if (actual === null || typeof actual !== 'object')
                return false;
            var keys = Object.keys(expected);
            if (Object.keys(actual).length !== keys.length)
                return false;
            return keys.every(function(key) { return same(actual[key], expected[key]); });
        }
        return actual === expected;
    }

    this.assert = function(actual, expected, what) {
        if (same(actual, expected)) {
            ++passed;
        } else {
            ++failed;
            print('FAILED ' + what + ': actual=' + JSON.stringify(actual) + ' expected=' + JSON.stringify(expected));
        }
    };

    this.throws = function(what, fn) {
        try {
            fn();
        } catch (e) {
            ++passed;
            return;
        }
        ++failed;
        print('FAILED ' + what + ': no exception');
    };

    this.finish = function() {
        print('Tests passed: ' + passed + ', failed: ' + failed);
        if (failed > 0)
            throw new Error(failed + ' checks failed');
    };
}

var test = new UnitTest();
var obj1 = TestObject1;
var obj2 = TestObject2;

// objects
test.assert(obj1.name(), 'TestObject1', 'name of a manager object');
test.assert(obj2.objectName, 'TestObject2', 'objectName property');
test.assert(TestObject3.name(), 'TestObject3', 'name of an action object');
test.assert(TestObject4.name(), 'TestObject4', 'name of an action object');
test.assert(self.name(), 'MyAction', 'self');
test.assert(self.interpreter(), 'javascript', 'interpreter name');
test.assert(Qross.interpreters().indexOf('javascript') >= 0, true, 'Qross.interpreters()');
test.assert(obj1.myself() === obj1, true, 'identity of a returned QObject');
test.assert(obj1.myself2() === obj1, true, 'identity through a subclass pointer');
test.assert(obj1.func_qobject_qobject(obj2) === obj2, true, 'QObject round trip');
test.assert(obj1.func_testobject_testobject(obj2) === obj2, true, 'TestObject round trip');
test.assert(obj1.func_testobject_qobject(obj2) === obj2, true, 'QObject in, TestObject out');
test.assert(obj1.func_qobject_qobject(null), null, 'null QObject');
test.assert(obj1.func_qwidget_qwidget(null), null, 'null QWidget');
test.assert(obj1.func_createChildTestObject('MyChildObject').name(), 'MyChildObject', 'created child');
test.assert(obj1.func_otherobject('other').testObject() === obj1, true, 'OtherObject');
test.assert(obj1.func_otherobject_otherobject(obj1.func_otherobject('other')).objectName, 'other', 'OtherObject round trip');
test.throws('unknown method', function() { obj1.noSuchMethod(); });

// numbers and strings
test.assert(obj1.func_bool_bool(true), true, 'bool');
test.assert(obj1.func_bool_bool(false), false, 'bool');
test.assert(obj1.func_int_int(0), 0, 'int');
test.assert(obj1.func_int_int(177321), 177321, 'int');
test.assert(obj1.func_int_int(-98765), -98765, 'int');
test.assert(obj1.func_uint_uint(0), 0, 'uint');
test.assert(obj1.func_uint_uint(177321), 177321, 'uint');
test.assert(obj1.func_double_double(0.0), 0.0, 'double');
test.assert(obj1.func_double_double(1773.2177), 1773.2177, 'double');
test.assert(obj1.func_double_double(-548993.271993), -548993.271993, 'double');
test.assert(obj1.func_qlonglong_qlonglong(0), 0, 'qlonglong');
test.assert(obj1.func_qlonglong_qlonglong(7379), 7379, 'qlonglong');
test.assert(obj1.func_qlonglong_qlonglong(-6384673), -6384673, 'qlonglong');
test.assert(obj1.func_qulonglong_qulonglong(0), 0, 'qulonglong');
test.assert(obj1.func_qulonglong_qulonglong(378972), 378972, 'qulonglong');
test.assert(obj1.func_qstring_qstring(''), '', 'QString');
test.assert(obj1.func_qstring_qstring(' '), ' ', 'QString');
test.assert(obj1.func_qstring_qstring(' Another \n\r Test!   $%&" '), ' Another \n\r Test!   $%&" ', 'QString');
test.assert(obj1.func_qstring_qstring_int('x', 5), 'x,5', 'two arguments');

// byte arrays
var bytes = obj1.func_qbytearray_qbytearray('bytes');
test.assert(bytes instanceof ArrayBuffer, true, 'QByteArray comes back as an ArrayBuffer');
test.assert(Array.from(new Uint8Array(bytes), function(b) { return String.fromCharCode(b); }).join(''), 'bytes', 'QByteArray content');
test.assert(obj1.func_qbytearray_qbytearray(bytes).byteLength, 5, 'ArrayBuffer in');

// lists and maps
test.assert(obj1.func_qstringlist_qstringlist([]), [], 'empty QStringList');
test.assert(obj1.func_qstringlist_qstringlist(['abc', 'def']), ['abc', 'def'], 'QStringList');
test.assert(obj1.func_qvariantlist_qvariantlist([]), [], 'empty QVariantList');
test.assert(obj1.func_qvariantlist_qvariantlist(['abc', 426, -842, 96.23, true, null]), ['abc', 426, -842, 96.23, true, null], 'QVariantList');
test.assert(obj1.func_qvariantlist_qvariantlist([[1, 2], { k: 'v' }]), [[1, 2], { k: 'v' }], 'nested QVariantList');
var map = { key1: ' MyValue ', key2: '', key3: 1764, key4: -8772, key5: true, key6: false, key7: 978.216, key8: -692.967, key9: [], key10: ['one', 'two'] };
test.assert(obj1.func_qvariantmap_qvariantmap(map), map, 'QVariantMap');
test.assert(obj1.func_qvariantmap_qvariantmap({}), {}, 'empty QVariantMap');
test.assert(obj1.func_qvariantlist2qobject(obj1.func_qobject2qvariantlist(obj2)) === obj2, true, 'QObject through a QVariantList');
test.assert(obj1.myself3().length, 1, 'list of subclass pointers');
test.assert(obj1.func_testobjectlist_testobjectlist([obj1, obj2])[1] === obj2, true, 'list of subclass pointers round trip');

// variants
test.assert(obj1.func_qvariant_qvariant(true), true, 'QVariant with a bool');
test.assert(obj1.func_qvariant_qvariant(1892), 1892, 'QVariant with an int');
test.assert(obj1.func_qvariant_qvariant(8529.54), 8529.54, 'QVariant with a double');
test.assert(obj1.func_qvariant_qvariant(' String '), ' String ', 'QVariant with a string');
test.assert(obj1.func_qvariant_qvariant(['One', 'Two']), ['One', 'Two'], 'QVariant with an array');
test.assert(obj1.func_qvariant_qvariant({ a: 1 }), { a: 1 }, 'QVariant with an object');
test.assert(obj1.func_qvariant_qvariant(null), null, 'QVariant with null');
test.assert(obj1.func_qvariant_qvariant(obj2) === obj2, true, 'QVariant with a QObject');

// value types
test.assert(obj1.func_qcolor_qcolor('#ff0000').toString(), '#ff0000', 'QColor from a string');
test.assert(obj1.func_qcolor_qcolor(obj1.func_qcolor_qcolor('#00ff00')).toString(), '#00ff00', 'QColor round trip');
var size = obj1.func_qsize_qsize({ width: 12, height: 34 });
test.assert([size.width, size.height], [12, 34], 'QSize');
test.assert(obj1.func_qsize_qsize(Qt.size(5, 6)).height, 6, 'QSize from Qt.size()');
var sizef = obj1.func_qsizef_qsizef({ width: 12.5, height: 34.25 });
test.assert([sizef.width, sizef.height], [12.5, 34.25], 'QSizeF');
var point = obj1.func_qpoint_qpoint({ x: 12, y: 34 });
test.assert([point.x, point.y], [12, 34], 'QPoint');
test.assert(obj1.func_qpoint_qpoint(Qt.point(1, 2)).y, 2, 'QPoint from Qt.point()');
var pointf = obj1.func_qpointf_qpointf({ x: 1.5, y: -2.5 });
test.assert([pointf.x, pointf.y], [1.5, -2.5], 'QPointF');
var rect = obj1.func_qrect_qrect({ x: 12, y: 34, width: 56, height: 78 });
test.assert([rect.x, rect.y, rect.width, rect.height, rect.right, rect.bottom], [12, 34, 56, 78, 67, 111], 'QRect');
test.assert(obj1.func_qrect_qrect(rect).width, 56, 'QRect round trip');
test.assert(obj1.func_qrect_qrect(Qt.rect(1, 2, 3, 4)).width, 3, 'QRect from Qt.rect()');
var rectf = obj1.func_qrectf_qrectf({ x: 1.5, y: 2.5, width: 3.5, height: 4.5 });
test.assert([rectf.x, rectf.y, rectf.width, rectf.height], [1.5, 2.5, 3.5, 4.5], 'QRectF');

// urls
test.assert(obj1.func_qurl_qurl('http://nowhere.anywhere/path?arg=val').toString(), 'http://nowhere.anywhere/path?arg=val', 'QUrl from a string');
test.assert(obj1.func_qurl_qurl('/home/me').toString(), '/home/me', 'QUrl from a path');
test.assert(obj1.func_qurl_qurl(obj1.func_qurl_qurl('file:///home/me/file.txt')).toString(), 'file:///home/me/file.txt', 'QUrl round trip');

// dates and times
var when = new Date(2020, 0, 2, 3, 4, 5);
test.assert(obj1.func_qdatetime_qdatetime(when).getTime(), when.getTime(), 'QDateTime');
test.assert(obj1.func_qtime_qtime(when).getMinutes(), 4, 'QTime');
var day = new Date(Date.UTC(2020, 0, 2));
test.assert(obj1.func_qdate_qdate(day).getTime(), day.getTime(), 'QDate');

// properties
obj1.boolProperty = true;
test.assert(obj1.boolProperty, true, 'bool property');
obj1.intProperty = 5278;
test.assert(obj1.intProperty, 5278, 'int property');
obj1.doubleProperty = 928.581;
test.assert(obj1.doubleProperty, 928.581, 'double property');
obj1.stringProperty = 'StRiNg';
test.assert(obj1.stringProperty, 'StRiNg', 'QString property');
obj1.stringListProperty = ['a', 'b'];
test.assert(obj1.stringListProperty, ['a', 'b'], 'QStringList property');
obj1.listProperty = [1, 'x'];
test.assert(obj1.listProperty, [1, 'x'], 'QVariantList property');

// enumerations
test.assert(obj1.TESTENUM1, 1, 'enum key');
test.assert(obj2.TESTENUM4, 8, 'enum key');
test.assert(obj1.myself().TESTENUM2, 2, 'enum key on a returned object');

// signals
var received = null;
obj1.signalString.connect(function(s) { received = s; });
obj1.emitSignalString('more beer');
test.assert(received, 'more beer', 'signal with a string');
obj1.signalObject.connect(function(o) { received = o; });
obj1.emitSignalObject(obj2);
test.assert(received === obj2, true, 'signal with an object');
function onInt(i) { received = i; }
obj1.signalInt.connect(onInt);
obj1.signalInt(9);
test.assert(received, 9, 'signal emitted from the script');
obj1.signalInt.disconnect(onInt);
obj1.emitSignalInt(10);
test.assert(received, 9, 'disconnected signal');

// the script
function myValueFunction(arg) { return arg; }
test.assert(self.functionNames().indexOf('myValueFunction') >= 0, true, 'functionNames()');

// script objects handed to C++
function MyClass(result) {
    this.myMethod = function() { return result; };
}
var instance = new MyClass('my string');
test.assert(obj1.call_qrossobject_method(instance, 'myMethod'), 'my string', 'Qross::Object method call');
test.assert(obj1.get_qrossobject_methods(instance), ['myMethod'], 'Qross::Object method names');
test.assert(obj1.call_qrossobject_method(obj1.func_qrossobject_qrossobject(instance), 'myMethod'), 'my string', 'Qross::Object round trip');
test.assert(obj1.call_qrossobject_method({ add: function(a, b) { return a + b; } }, 'add', [40, 2]), 42, 'Qross::Object method call with arguments');

test.finish();
