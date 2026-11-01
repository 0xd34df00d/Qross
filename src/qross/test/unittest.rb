#!/usr/bin/env qrosstest
# Qross - scripting bridge for Qt applications.
# SPDX-License-Identifier: LGPL-2.0-or-later

# Run by qrosstest, which publishes TestObject1 and TestObject2 through
# the manager and TestObject3 and TestObject4 through the action.

require 'date'
require 'json'

ACTION = self

def testFunction(*args) = args

class Checks
  attr_reader :failures

  def initialize
    @passed = 0
    @failures = []
  end

  def assert(condition, what)
    if condition
      @passed += 1
    else
      @failures << what
    end
  end

  def equal(expected, actual, what)
    assert(expected == actual, "#{what}: expected #{expected.inspect}, got #{actual.inspect}")
  end

  def raises(type, what)
    yield
    @failures << "#{what}: nothing raised"
  rescue type
    @passed += 1
  rescue Exception => e
    @failures << "#{what}: raised #{e.class} instead of #{type}"
  end

  def finish
    puts "#{@passed} checks passed"
    return if @failures.empty?

    @failures.each { |failure| puts "FAIL: #{failure}" }
    raise "#{@failures.size} checks failed"
  end
end

class TestQross
  def initialize(checks)
    @checks = checks
    @object1 = TestObject1
    @object2 = TestObject2
  end

  def run
    public_methods(false).grep(/\Atest/).sort.each do |name|
      send(name)
    rescue Exception => e
      @checks.assert(false, "#{name} raised #{e.class}: #{e.message}")
    end
  end

  def testEnvironment
    @checks.equal('unittest.rb', File.basename(__FILE__), 'the script knows its file')
    @checks.equal('qross', $0, 'the program name')
    @checks.equal({ 'a' => [1, 2] }, JSON.parse('{"a": [1, 2]}'), 'a default gem loads')
    @checks.assert($LOAD_PATH.include?(File.dirname(__FILE__)), 'the script directory is on the load path')
    @checks.assert(@object1.is_a?(::Qross::QObject), 'wrappers derive from Qross::QObject')
    @checks.equal('Qross::TestObject', @object1.class.name, 'wrapper classes are named after the C++ class')
    @checks.assert(@object1.inspect.include?('TestObject1'), 'inspect names the object')
  end

  def testObjects
    @checks.equal('TestObject1', @object1.name, 'name()')
    @checks.equal('TestObject2', @object2.objectName, 'objectName')
    @checks.equal('TestObject3', TestObject3.name, 'action object')
    @checks.equal('TestObject4', TestObject4.name, 'another action object')
    @checks.equal('TestObject', @object1.className, 'className')
    @checks.equal(@object1, @object1.myself, 'QObject* result')
    @checks.equal(@object1, @object1.myself2, 'TestObject* result')
    @checks.assert(@object1 != @object2, 'different objects differ')
    @checks.equal(@object2, @object1.func_qobject_qobject(@object2), 'QObject* argument')
    @checks.equal(@object2, @object1.func_testobject_testobject(@object2), 'TestObject* argument')
    @checks.equal(@object2, @object1.func_testobject_qobject(@object2), 'QObject* argument to TestObject* result')
    @checks.assert(@object1.func_qobject_qobject(nil).nil?, 'null QObject* result')
    @checks.assert(@object1.func_qwidget_qwidget(nil).nil?, 'null QWidget* result')
    @checks.equal('MyChildObject', @object1.func_createChildTestObject('MyChildObject').name, 'new object')
    @checks.assert(@object1.respond_to?(:func_int_int), 'slots are methods')
    @checks.assert(@object1.methods.include?(:func_int_int), 'slots are listed')
    @checks.raises(TypeError, 'a string is no QObject') { @object1.func_qobject_qobject('not an object') }
    @checks.raises(TypeError, 'a TestObject is no QWidget') { @object1.func_qwidget_qwidget(@object2) }
    @checks.raises(ArgumentError, 'argument count') { @object1.func_int_int(1, 2) }
    @checks.raises(NoMethodError, 'unknown method') { @object1.noSuchMethod }
  end

  def testNumbers
    @checks.equal(true, @object1.func_bool_bool(true), 'true')
    @checks.equal(false, @object1.func_bool_bool(false), 'false')
    [0, 177_321, -98_765].each { |v| @checks.equal(v, @object1.func_int_int(v), 'int') }
    [0, 177_321].each { |v| @checks.equal(v, @object1.func_uint_uint(v), 'uint') }
    [0.0, 1773.2177, -548_993.271993].each { |v| @checks.equal(v, @object1.func_double_double(v), 'double') }
    [0, 7379, -6_384_673, -2**40, -2**63].each { |v| @checks.equal(v, @object1.func_qlonglong_qlonglong(v), 'qlonglong') }
    [0, 378_972, 2**63, 2**64 - 1].each { |v| @checks.equal(v, @object1.func_qulonglong_qulonglong(v), 'qulonglong') }
    @checks.equal(42.0, @object1.func_double_double(42), 'an Integer for a double')
    @checks.equal(18, @object1.func_int_int(17.9), 'a Float for an int rounds')
  end

  def testStrings
    ['', ' ', " Another \n\r Test!   $%&\" ", 'áêïòñα', 'α'].each do |v|
      @checks.equal(v, @object1.func_qstring_qstring(v), 'QString')
    end
    @checks.equal('x,5', @object1.func_qstring_qstring_int('x', 5), 'QString and int')
    @checks.equal('bytes'.b, @object1.func_qbytearray_qbytearray('bytes'.b), 'QByteArray')
    @checks.equal(Encoding::ASCII_8BIT, @object1.func_qbytearray_qbytearray('bytes'.b).encoding, 'byte arrays are binary strings')
    @checks.equal('text'.b, @object1.func_qbytearray_qbytearray('text'), 'a text for a QByteArray')
    @checks.equal(Encoding::UTF_8, @object1.func_qstring_qstring('α').encoding, 'strings are UTF-8')
    @checks.equal('sym', @object1.func_qstring_qstring(:sym), 'a Symbol for a QString')
  end

  def testLists
    @checks.equal([], @object1.func_qstringlist_qstringlist([]), 'empty QStringList')
    @checks.equal([' string1', 'string2 '], @object1.func_qstringlist_qstringlist([' string1', 'string2 ']), 'QStringList')
    @checks.equal([], @object1.func_qvariantlist_qvariantlist([]), 'empty QVariantList')
    @checks.equal([[[[]], []]], @object1.func_qvariantlist_qvariantlist([[[[]], []]]), 'nested lists')
    @checks.equal(['A string', [17_539, -8591], [5.32, -842.775]], @object1.func_qvariantlist_qvariantlist(['A string', [17_539, -8591], [5.32, -842.775]]), 'mixed list')
    @checks.equal([[true, [], false, 'Other String'], 'test'], @object1.func_qvariantlist_qvariantlist([[true, [], false, 'Other String'], 'test']), 'mixed list')
    @checks.equal([[17, 52], [], {}, [84.21, 936.821]], @object1.func_qvariantlist_qvariantlist([[17, 52], [], {}, [84.21, 936.821]]), 'list with a hash')
    wrapped = @object1.func_qobject2qvariantlist(@object2)
    @checks.equal([@object2], wrapped, 'objects in a list')
    @checks.equal(@object2, @object1.func_qvariantlist2qobject(wrapped), 'object out of a list')
    @checks.equal([@object1], @object1.myself3, 'QList<TestObject*> result')
    @checks.equal([@object1, @object2], @object1.func_testobjectlist_testobjectlist([@object1, @object2]), 'QList<TestObject*> argument')
  end

  def testMaps
    [{}, { '3' => -837, '1' => 73_682, '2' => 285 }, { 'c' => 84.24, 'a' => -6892.957 }, { 'key1' => true, 'key2' => false },
     { 'key 2' => '  Some String  ', 'key 3' => 'oThEr StRiNg' }, { ' key4 ' => [12.5, true], ' key5 ' => [83.002, 'test'] },
     { '  key7  ' => {}, '  key6  ' => {} }].each do |v|
      @checks.equal(v, @object1.func_qvariantmap_qvariantmap(v), 'QVariantMap')
    end
    @checks.equal({ 'sym' => 1, '2' => 2 }, @object1.func_qvariantmap_qvariantmap({ sym: 1, 2 => 2 }), 'keys become strings')
  end

  def testVariants
    [0.0, true, false, 187_937, -69_825, 8632.274, -8632.351, " Test \n\r This String $%&\"", nil, [1, 'a'], { 'a' => 1 }].each do |v|
      @checks.equal(v, @object1.func_qvariant_qvariant(v), 'QVariant')
    end
    @checks.equal(@object2, @object1.func_qvariant_qvariant(@object2), 'an object as QVariant')
  end

  def testGeometry
    [[0, 0], [12, -94], [-7264, 6224]].each do |v|
      @checks.equal(v, @object1.func_qsize_qsize(v), 'QSize')
      @checks.equal(v, @object1.func_qpoint_qpoint(v), 'QPoint')
    end
    [[0.0, 0.0], [-956.0, 75.21], [-14.21, -535.0]].each do |v|
      @checks.equal(v, @object1.func_qsizef_qsizef(v), 'QSizeF')
      @checks.equal(v, @object1.func_qpointf_qpointf(v), 'QPointF')
    end
    [[0, 0, 0, 0], [-1, -2, 3, 4], [10, 20, -30, -40]].each do |v|
      @checks.equal(v, @object1.func_qrect_qrect(v), 'QRect')
    end
    [[0.0, 0.0, 0.0, 0.0], [-1.1, -2.2, 3.3, 4.4]].each do |v|
      @checks.equal(v, @object1.func_qrectf_qrectf(v), 'QRectF')
    end
    @checks.raises(TypeError, 'two numbers are no QRect') { @object1.func_qrect_qrect([1, 2]) }
  end

  def testColorsAndUrls
    @checks.assert(@object1.func_qcolor_qcolor(nil).nil?, 'invalid QColor')
    @checks.equal('#0066ff', @object1.func_qcolor_qcolor('#0066ff'), 'QColor')
    @checks.equal('#800066ff', @object1.func_qcolor_qcolor('#800066ff'), 'QColor with alpha')
    @checks.equal('', @object1.func_qurl_qurl(nil), 'empty QUrl')
    ['/home/myuser', 'file:///home/myuser/myfile.txt', 'http://myname:mypass@qross.dipe.org?404.cgi?test=123&test2=456'].each do |v|
      @checks.equal(v, @object1.func_qurl_qurl(v), 'QUrl')
    end
  end

  def testDates
    at = Time.new(2020, 1, 2, 3, 4, Rational(5006, 1000))
    @checks.equal(at, @object1.func_qdatetime_qdatetime(at), 'QDateTime')
    @checks.assert(@object1.func_qdatetime_qdatetime(at).is_a?(Time), 'date-times are Time objects')
    utc = Time.utc(2020, 1, 2, 3, 4, 5)
    @checks.equal(utc, @object1.func_qdatetime_qdatetime(utc), 'QDateTime in UTC')
    @checks.assert(@object1.func_qdatetime_qdatetime(utc).utc?, 'UTC stays UTC')
    @checks.equal(Date.new(2020, 1, 2), @object1.func_qdate_qdate(Date.new(2020, 1, 2)), 'QDate')
    @checks.equal(Date.new(2020, 1, 2), @object1.func_qdate_qdate(at), 'a Time for a QDate')
    @checks.equal('03:04:05.006', @object1.func_qtime_qtime('03:04:05.006'), 'QTime as an ISO string')
  end

  def testProperties
    @object1.boolProperty = true
    @checks.equal(true, @object1.boolProperty, 'bool property')
    @object1.intProperty = 20
    @checks.equal(20, @object1.intProperty, 'int property')
    @object1.doubleProperty = 7436.671
    @checks.equal(7436.671, @object1.doubleProperty, 'double property')
    @object1.stringProperty = ' SoMe StRiNg '
    @checks.equal(' SoMe StRiNg ', @object1.stringProperty, 'string property')
    @object1.stringListProperty = ['TestString', ' Other String ']
    @checks.equal(['TestString', ' Other String '], @object1.stringListProperty, 'string list property')
    @object1.listProperty = [true, [2464, -8295], -572.07516, 'test', []]
    @checks.equal([true, [2464, -8295], -572.07516, 'test', []], @object1.listProperty, 'list property')
    @checks.raises(NoMethodError, 'unknown property') { @object1.noSuchProperty = 1 }
    @checks.raises(TypeError, 'wrong type for a property') { @object1.intProperty = [1, 2] }

    @object1.setProperty('intProperty', -75_825)
    @checks.equal(-75_825, @object1.property('intProperty'), 'property()')
    @checks.equal(-75_825, @object1.intProperty, 'setProperty()')
    @checks.equal(['Some String', 99], @object1.property('dynamicProperty'), 'dynamic property through property()')
    @checks.equal(['Some String', 99], @object1.dynamicProperty, 'dynamic property as a method')
    @checks.assert(@object1.respond_to?(:dynamicProperty), 'dynamic properties answer respond_to?')
    @object1.setProperty('newDynamicProperty', 'New Dynamic Property')
    @checks.equal('New Dynamic Property', @object1.newDynamicProperty, 'new dynamic property')
    @object1.newDynamicProperty = 5
    @checks.equal(5, @object1.property('newDynamicProperty'), 'dynamic property assignment')
  end

  def testEnumerations
    @checks.equal(1, @object1.TESTENUM1, 'enum key as a method')
    @checks.equal(2, @object1.TESTENUM2, 'enum key as a method')
    @checks.equal(4, @object1.TESTENUM3, 'enum key as a method')
    @checks.equal(8, @object1.TESTENUM4, 'enum key as a method')
    @checks.equal(2, @object1.myself.TESTENUM2, 'enum key on a returned wrapper')
    @checks.equal(4, @object1.class::TESTENUM3, 'enum key as a constant')
  end

  def on_int(i)
    @received << i
  end

  def testSignals
    @received = []
    @object1.connect(:signalString) { |s| @received << s }
    @object1.emitSignalString('more beer')
    @checks.equal(['more beer'], @received, 'a block connected to a signal')
    @object1.signalString('direct')
    @checks.equal('direct', @received.last, 'calling a signal emits it')
    @object1.connect(:signalObject) { |o| @received << o.name }
    @object1.emitSignalObject(@object2)
    @checks.equal('TestObject2', @received.last, 'an object as signal argument')

    @object1.connect('signalInt(int)', method(:on_int))
    @object1.emitSignalInt(9)
    @checks.equal(9, @received.last, 'a Method connected to a signal')
    @object1.disconnect(:signalInt, method(:on_int))
    @object1.emitSignalInt(10)
    @checks.equal(9, @received.last, 'disconnect()')
    @checks.raises(ArgumentError, 'a slot is no signal') { @object1.connect(:func_void) { nil } }
    @checks.raises(ArgumentError, 'connect() needs a handler') { @object1.connect(:signalInt) }
  end

  def testAction
    @checks.assert(ACTION.functionNames.include?('testFunction'), 'functionNames()')
    [[], [true, false], [524, -958], [524.98, -958.1257], ['', "  Some\nString  "], [['one', 23, 'two', nil, false]]].each do |v|
      @checks.equal(v, ACTION.callFunction('testFunction', v), 'callFunction()')
    end
    @checks.equal([ACTION], ACTION.callFunction('testFunction', [ACTION]), 'the action as argument')
    @checks.equal(3, ACTION.evaluate('1+2'), 'evaluate()')
    @checks.equal([nil, 99], ACTION.evaluate('testFunction(nil, 99)'), 'evaluate() sees the functions')
  end

  def testScriptObjects
    klass = Class.new do
      def initialize(result)
        @result = result
      end

      def myMethod = @result

      def add(a, b) = a + b
    end
    instance = klass.new('my string')
    @checks.equal('my string', @object1.call_qrossobject_method(instance, 'myMethod'), 'calling a method of a Ruby object')
    @checks.equal(42, @object1.call_qrossobject_method(instance, 'add', [40, 2]), 'calling with arguments')
    @checks.equal(%w[add myMethod], @object1.get_qrossobject_methods(instance), 'listing the methods of a Ruby object')
    @checks.assert(@object1.func_qrossobject_qrossobject(instance).equal?(instance), 'a Ruby object comes back as itself')
  end

  def testOtherObject
    other1 = @object1.func_otherobject('OtherObject1')
    other2 = @object1.func_otherobject('OtherObject2')
    @checks.equal('OtherObject1_wrapper', other1.objectName, 'a handler wraps the result')
    @checks.equal('OtherObject2', other2.parentObject.objectName, 'the wrapper reaches the object')
    @checks.equal(other1.objectName, @object1.func_otherobject_otherobject(other1).objectName, 'the wrapper stands in as argument')
    both = @object1.func_otherobjectlist_otherobjectlist([other1, other2])
    @checks.equal(2, both.size, 'a list of handled objects')
    @checks.equal('OtherObject1_wrapper', both[0].objectName, 'handled list element')
    @checks.equal('OtherObject2', both[1].parentObject.objectName, 'handled list element')
  end
end

checks = Checks.new
TestQross.new(checks).run
checks.finish
