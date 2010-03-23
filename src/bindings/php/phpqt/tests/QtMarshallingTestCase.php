<?php

require_once('PHPUnit/Framework/TestCase.php');
require_once('PHPUnit/Framework/TestSuite.php');

/**
 * tests: marshalling arguments
 */

class QtMarshallingTestCase extends PHPUnit_Framework_TestCase {

	private $app;
    
	public function __construct($name="") {
	    parent::__construct($name);
	}

	/**
	 * return numbers		  <br><br>
	 * <code>
	 *  $date = new QDate(2007,3,24); <br>
	 *  $date->day();		  <br>
	 * </code>
	 */
	function testReturnNum() {
	    echo "\ntesting numbers";
	    $date = new QDate(2007,3,24);
	    $this->assertTrue((gettype($date->day()) == "integer"), "Value returned is not integer type, ".gettype($date->day())." detected!");
	    $this->assertTrue(($date->day() == 24), "Value returned is wrong!");
	    echo " passed";
	}
	
	// test returning double
	// test returning array
	// test returning null
	
	/**
	 * return boolean			<br><br>
	 * <code>
	 * $date = new QDate(2007,3,24);	<br>
	 * $date->setDate(2007,3,24))		<br>
	 * </code>
	 */
	function testReturnBool() {
	    echo "\ntesting bool";
	    $date = new QDate(2007,3,24);
	    $this->assertTrue((gettype($date->setDate(2007,3,24)) == "boolean"), "Value returned is not boolean type, ".gettype($date->setDate(2007,3,24))." detected!");
	    $this->assertTrue(($date->setDate(2007,3,24) == true), "Value returned is wrong!");
	    echo " passed";
	}
	
	/**
	 * return object			<br><br>
	 * <code>
	 *  $parent = new QObject();		<br>
	 *  $object = new QObject($parent);	<br>
	 * </code>
	 */
	function testReturnObject() {
	    echo "\ntesting objects";
	    $parent = new QObject();
	    $object = new QObject($parent);
	    $parent__ = $object->parent();
	    $this->assertTrue(($parent === $parent__),"Object returned by QObject->parent() is not the same as parent!");
	    echo " passed";
	}

	/**
	 * return of a new object		<br><br>
	 * <code>
	 * $date = new QDate(2007,3,24);	<br>
	 * $date__ = $date->addDays(2);		<br>
	 * </code>
	 * \todo return references
	 * \todo return pointers
	 */
	function testReturnNewObject() {
	    echo "\ntesting new objects";
	    $date = new QDate(2007,3,24);
	    $date__ = $date->addDays(2);
	    $this->assertFalse(($date === $date__),"new Object returned by QObject->parent() is the same as parent!");
	    echo " passed";
	}
	
	/**
	 * return string			<br><br>
	 * <code>
	 * $object = new QObject();		<br>
	 * $object->setObjectName("hello");	<br>
	 * $string = $object->objectName();	<br>
	 * </code>
	 */
	function testReturnQString() {
	    echo "\ntesting QString as return";
	    $object = new QObject();
	    $object->setObjectName("hello");
	    $string = $object->objectName();
	    $this->assertTrue(is_object($string), "String is not a QString!");
	    $this->assertEquals($string->toAscii(), "hello", "Return object does not contain the same text!");
	    echo " passed";
	}

	/**
	 * QString as argument			<br><br>
	 * <code>
	 * $object = new QObject();				<br>
	 * $object->setObjectName(new QString("hello string"));	<br>
	 * $s = $object->objectName();		     		<br>
	 * $s->toAscii()					<br>
	 * </code>
	 */
	function testAddQString() {
	    echo "\ntesting QString as argument";
	    $object = new QObject();
	    $object->setObjectName(new QString("hello string"));
	    $s = $object->objectName();
	    $this->assertEquals($s->toAscii(),"hello string", "Return object does not contain the same text!");
	    echo " passed";
	}

	function testNumArgument() {
		echo "TODO\n";
	}	
	
	function testStringArgument() {
		echo "TODO\n";
	}
	
	function testQStringArgument() {
		echo "TODO\n";
	}
	
	
	function testBoolArgument() {
		echo "TODO\n";
	}
	
	function testObjectArgument() {
		echo "TODO\n";
	}
	
	function testConstReferenceArgument() {
		echo "TODO\n";
	}
	
	function testPointerArgument() {
		echo "TODO\n";
	}

} // Test Case

?>
