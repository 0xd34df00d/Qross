<?php

    /**
     *	This file contains a couple of QString tests
     *  \todo test QString::args() with giving an object, check __toString() on custom classes and Qt classes
     *  \todo test QStringList (also with different Objects inside)
     *
     *  \todo compare()
     *  \todo chop()
     *  \todo count()
     *  \todo contains()
     *  \todo endsWith()
     *  \todo fill()
     *  \todo indexOf()
     *  \todo insert()
     *  \todo isNull()
     *  \todo lastIndexOf()
     *  \todo left()
     *  \todo leftJustified()
     *  \todo leftRef()
     *  ...
     */

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');

    class QtQStringTestCase extends PHPUnit_Framework_TestCase {
    
	public function __construct($name="") {
	    parent::__construct($name);
	}

	/**
	 * test of different constructors of QString:
	 * <code>
	 * - QString ()
	 * - QString ( const QChar * unicode, int size )	- unsupported, ambiguous
	 * - QString ( QChar ch )    	      	       		- with new QString(40);
	 * - QString ( int size, QChar ch )			- with new QString(3, 40);
	 * - QString ( const QLatin1String & str )		- unsupported
	 * - QString ( const QString & other )			- with new QString($s1);
	 * - QString ( const char * str )			- with new QString("bird");
	 * - QString ( const QByteArray & ba )			- unsupported
	 * </code>
	 */

	function test_construct() {

	    echo "testing QString ( const QLatin1String & str ) unsupported\n";
	    echo "testing QString ( const QByteArray & ba ) unsupported\n";
	    echo "testing QString ( const QChar * unicode, int size ) due ambiguity unsupported\n";

	    echo "testing QString ( const char * str ) ";
	    $s1 = new QString("bird");
	    echo "passed\n";

	    echo "testing QString ( const QString & other ) ";
	    $s2 = new QString($s1);	   // QString ( const QString & other ) 
	    echo "passed\n";

	    echo "testing copy constructor result equals original ";
	    $this->assertEquals($s2->__toString(), "bird", "Could not construct QString!");
	    echo "passed\n";

	    echo "testing QString ( QChar ch ) ";
	    $s3 = new QString(40);	   // QString ( QChar ch ) 
	    $this->assertEquals($s3->__toString(), "(", "Could not construct QString!");
	    echo "passed\n";

	    echo "testing value of QString ";
	    $s4 = new QString("helicopter");
	    $this->assertEquals($s4->__toString(), "helicopter", "Could not construct QString!");
	    echo "passed\n";

	    echo "testing QString ( int size, QChar ch ) ";
	    $s5 = new QString(3, 40);
	    $this->assertEquals($s5->__toString(), "(((", "Could not construct QString!");
	    echo "passed\n";

	    echo "\n=== constructor tests done ===\n\n";
	}

	/**
	 * test of append()
	 * - the test function creates two objects $s1 and $2 of QString with the values "bird" and " plug" and appends $2 to $1
	 * - in the second step the PHP string " helicopter" will be appended to $s1
	 * - in the third step a character '40' which is a '(' will be appended to $1
	 */

	function test_append() {
	    $s1 = new QString("bird");
	    $s2 = new QString(" plug");
	    $s1->append($s2);
	    $this->assertEquals($s1->__toString(), "bird plug", "Could not append QString to QString!");
	    $s1->append(" helicopter");
	    $this->assertEquals($s1->__toString(), "bird plug helicopter", "Could not append string to QString!");
	    $s1->append(40);
	    $this->assertEquals($s1->__toString(), "bird plug helicopter(", "Could not append QChar to QString!");
	    echo "\ntesting QString::append() passed";
	}

	/**
	 * Test of toInt()
	 * - a QString with the value "24" will be created and toInt() turnes it into a PHP integer value.
	 */

	function test_toInt() {
	    $s1 = new QString("24");
	    $this->assertEquals($s1->toInt(), 24, "Could not get integer!");
	    echo "\ntesting QString::toInt() passed";
	}

	/**
	 * Test of toDouble()
	 * - a QString with the value "24.3" will be created and toInt() turnes it into a PHP double value.
	 */

	function test_toDouble() {
	    $s1 = new QString("24.3");
	    $this->assertEquals($s1->toDouble(), 24.3, "Could not get double!");
	    echo "\ntesting QString::toDouble() passed";
	}

	/**
	 * Test of QString::number()
	 * - an integer 24 and a double 24.3 will be given to QString::number() and checked if it returns the correct string value of it.
	 */

	function test_number() {
	    $this->assertEquals(QString::number(24)->__toString(), "24", "Could not get string version of integer!");
	    $this->assertEquals(QString::number(24.3)->__toString(), "24.3", "Could not get string version of double!");
	    echo "\ntesting QString::number() passed";
	}

	/**
	 * Test of isEmpty()
	 * - an empty QString will be created and checked if it contains a value
	 * - in the second step a character will be appended and the object will be checked again
	 */

	function test_isEmpty() {
	    $s1 = new QString();
	    $this->assertTrue($s1->isEmpty(), "Could not ask isEmpty()!");
	    $s1->append("I");
	    $this->assertFalse($s1->isEmpty(), "Could not ask isEmpty()!");
	    echo "\ntesting QString::isEmpty() passed";
	}

	/**
	 * Test of clear()
	 * - a QString will be created and then cleared, check if __toString() returns ""
	 */

	function test_clear() {
	    $s1 = new QString("hello");
	    $s1->clear();
	    $this->assertEquals($s1->__toString(), "", "Could not clear()!");
	    echo "\ntesting QString::clear() passed";
	}
    }
?>