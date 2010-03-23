<?php

    /**
     *	This file contains basic tests
     *
     *	- test fetching constants, the opcode handler has been overwritten
     *	- test __toString()
     *	- test QString
     *	- test returning values and objects
     *  - test returning references
     *
     * @TODO: set bool, empty string
     * @TODO: QColor::getRgb(int* r, int* g, int* b)
     * @TODO: $this->parent()->foo()
     */

    require_once('config.php');
    require_once($tests_path.'/testHelper.php');

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');

    class QtBasicTestCase extends PHPUnit_Framework_TestCase {
    
	private $app;
    
	public function __construct($name="") {
	    parent::__construct($name);
	}

	/**
	 * const opcode handler, fetching a string constant written in PHP 
	 * <code>foo::a</code>
	 */
	function testFetchStringConstant() {
	    echo "\ntesting foo::a";
	    $this->assertEquals(foo::a, "a", "Could not fetch string constant!");
	    echo " passed";
	}

	/**
	 * const opcode handler, fetching a numeric constant written in PHP: 
	 * <code>foo::b</code>
	 */
	function testFetchNumConstant() {
	    echo "\ntesting foo::b";
	    $this->assertEquals(foo::b, 24, "Could not fetch numeric constant!");
	    echo " passed";
	}

	/**
	 * const opcode handler, fetching a Qt constant: 
	 * <code>Qt::Horizontal</code>
	 */
	function testQtConstant() {
	    echo "\ntesting Qt::Horizontal";
	    $this->assertTrue(Qt::Horizontal == 1, "Could not fetch constant from Qt!");
	    echo " passed";
	}

	/**
	 * const opcode handler, fetching a Qt constant: 
	 * <code>QFont::Bold</code>
	 */
	function testQtConstant2() {
	    echo "\ntesting QFont::Bold";
	    $this->assertTrue(Qt::Bold == 75, "Could not fetch constant from Qt!");
	    echo " passed";
	}

	/**
	 * static method opcode handler, calling a static method written in PHP: 
	 * <code>foo::staticMethod();</code>
	 */
	function testCallStaticMethod() {
	    echo "\ntesting foo::staticMethod()";
	    $this->assertEquals(foo::staticMethod(), "staticMethod", "Could not call a static method!");
	    echo " passed";
	}

	/**
	 * static method opcode handler, calling a static method from a Qt parent class:
	 * <code>foo:tr()</code>
	 */
	function testCallStaticQtMethod() {
	    echo "\ntesting foo::tr()";
	    $this->assertEquals(foo::tr("hello") == "hello", "Could not call a static Qt method!");
	    echo " passed";
	}

	/**
	 * inheritance, calling a nonstatic parents method from withing an overwritten nonstatic method: 
	 * the method blockSignals defined in class foo calls the method blockSignals() of it's parent class
	 * 	<code>foo::blockSignals() calls QObject::blockSignals()</code>
	 */
	function testCallParentQtMethod() {
	    echo "\ntesting parent::blockSignals() within foo::blockSignals()";
	    $o = new QObject();
	    $p = new foo($o);
	    // set blockSignals to true, so we can test it
	    $p->blockSignals(true); 
    	    $this->assertTrue($p->blockSignals(true), "Could not call a parent Qt method!");
	    echo " passed";
	}

	/**
	 * inheritance, calling a static parents method from withing another static method:
	 * 	<code>foo->staticTrMethod() calls QObject::tr()</code>
	 */
	function testCallStaticQtMethodWithinStaticPHPMethod() {
	    echo "\ntesting foo::staticTrMethod()";
	    $this->assertEquals(foo::staticTrMethod("hello") == "hello", "Could not call a static Qt method!");
	    echo " passed";
	}

	/**
	 * test of QString::__toString()
	 */
	function testQString() {
	    echo "\ntesting QString::__toString()";
	    $s = new QString("hello");
	    $this->assertEquals($s->__toString(), "hello", "Could not handle __toString()!");
	    echo " passed";
	}

	/**
	 * appending a PHP string to a QString
	 * <code>
	 *  $s = new QString("hello");
	 *  $s->append(" world");
	 * </code>
	 */
	function testQStringAppendString() {
	    echo "\ntesting QString::append(\"hello\")";
	    $s = new QString("hello");
	    $s->append(" world");
	    $this->assertEquals($s->__toString(), "hello world", "Could append simple string to QString!");
	    echo " passed";
	}

	/**
	 * creating an instance of QApplication
	 * <code>
	 *  $argc=1; $argv=array("argv");
	 *  $this->app = new QApplication($argc,$argv);
	 * </code>
	 */
	function testQApplication() {
	    echo "\ntesting creation of QApplication";
	    $argc=1;
	    $argv=array("argv");
	    $this->app = new QApplication($argc,$argv);
	    $this->assertTrue(is_object($this->app), "Could not create an instance of QApplication!");
	    echo " passed";
	}

	/**
	 * appending a QString to another QString:
	 * <code>$firstString->append( $secondString )</code>
	 */
	function testQStringAppendObject() {
	    echo "\ntesting QString::append(new QString(\"hello\"))";
	    $s = new QString("hello");
	    $t = new QString(" world");
	    $s->append($t);
	    $this->assertEquals($s->__toString(), "hello world", "Could not append QString to QString!");
	    echo " passed";
	}

	// test methods of an derivated object
/*
	function testUnknownMethod() {
	    echo "\ntesting derivated object";
	    $date = new QObject();
	    $foo = new foo($date);
	    $foo->parent();
	    $foo->testMethod();
	    $foo->___();	// method not defined
	    echo " passed";
	}
*/

	/**
	 * calling the ambiguous constructor of class QPalette: 
	 * <code>
	 *  QWidget::setPalette( new QPalette(new QColor(250, 250, 200)) );
	 *  QWidget::setPalette( new QPalette( Qt::red ) );
	 * </code>
	 */
	function testAmbiguousConstructorCall() {
	    echo "\ntesting ambiguous constructor";
	    $w = new QWidget();
	    $w->setPalette(new QPalette( new QColor(250, 250, 200))) ;
	    $w->setPalette(new QPalette( Qt::red ));
	    echo " passed";
	}

	/**
	 * calling the ambiguous method update() of class QWidget which takes either a QRect or a QRegion as argument 
	 * <code>
	 *  QWidget->update( new QRect( 1, 2, 3, 4 ) );
	 *  QWidget->update( new QRegion( 1, 2, 3, 4, QRegion::Rectangle ) );
	 * </code>
	 */
	function testAmbiguousMethodCallObject() { 
	    echo "\ntesting ambiguous method call with different objects as arguments";
	    $w = new QWidget();
	    $w->update( 1, 2, 3, 4);
	    $w->update( new QRect( 1, 2, 3, 4 ) );
	    $w->update( new QRegion( 1, 2, 3, 4, QRegion::Rectangle ) );
	    echo " passed";	
	}

	/**
	 * creates a QObject and adds it to a mapping in QSignalMapper
	 * then calls the ambiduous method mapping() which expects either a string or an integer
	 * only one of them returns the right object
	 * original C++ API:
	 * QObject * QSignalMapper::mapping ( int id ) const
	 * QObject * QSignalMapper::mapping ( const QString & id ) const
	 * <code>
	 *  $s->setMapping( $o, 1 );
	 *  $p = $s->mapping( 1 );	 returns $o
	 *  $p = $s->mapping( "1" );	 returns NULL
	 * </code>
	 */
	function testAmbigousMethodCallObjects() {
	 echo "\ntesting ambiguous method call with different objects as arguments:";

	  $o = new QObject();
	  $s = new QSignalMapper();

	  $s->setMapping( $o, 1 );
  	  $p = $s->mapping( 1 );
	  $this->assertSame( $o, $p );

	  $p = $s->mapping( "1" );
	  $this->assertNull( $p );

          echo "done\n";
	}

	/**
	 * test of global function tr():
	 * <code>
	 *  $s = tr("hello world");
	 *  $s->__toString();
	 * </code>
	 */
	function testTr(){
	    echo "\ntesting global tr()";
	    $s = tr("hello world");
	    $this->assertEquals($s->__toString(), "hello world", "tr() doesnt work!");
	    echo " passed";
	}

    }    
    
?>