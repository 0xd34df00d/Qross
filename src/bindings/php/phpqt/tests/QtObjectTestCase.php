<?php

    /**
     *	This file contains a couple of basic tests
     *
     * - test for references
     */

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');

    $argc=0;
    $argv=array("");

    class myColor extends QColor {
	public $myProperty;
	public function __construct($r,$g,$b,$p) {
		parent::__construct($r,$g,$b);
		$this->myProperty = $p;
	    }
    }

    class myColor2 extends QColor {
	public $myProperty;
	public function __construct($r,$g,$b,$p) {
		parent::__construct($r,$g,$b);
		$this->myProperty = $p;
	    }
	public function __clone()
	    {
		$this->myProperty = $this->myProperty * 2;
	    }
    }

    $app = new QApplication($argc, $argv);

    /**
     *	check objects
     */

    class QtObjectTestCase extends PHPUnit_Framework_TestCase {
    
	public function __construct($name="") {
	    parent::__construct($name);
	}

	/**
	 * test references					<br><br>
	 * <code>
	 * $a = new QPushButton("a text");			<br>
	 * $b = &$a;						<br>
	 * $a->setText("text changed");				<br>
	 * $b->text()->__toString(); // "text changed"		<br>
	 *</code>
	 */
	function testReference() {
	    $a = new QPushButton("a text");
	    $b = &$a;
	    $a->setText("text changed");
	    echo "\ntesting reference";
	    $this->assertEquals($b->text()->__toString(), "text changed", "Creating a reference does not work!");
	    echo " passed";
	}

	/**
	 * test cloning, change the original and check the clone	<br><br>
	 * <code>
	 * $a = new QColor(100,200,255);				<br>
	 * $b = clone $a;						<br>
	 * $a->setBlue(123);						<br>
	 * $b->blue();	// 255						<br>
	 * </code>
	 */
	function testClone() {
	    $a = new QColor(100,200,255);
	    $b = clone $a;
	    $a->setBlue(123);
	    echo "\ntesting clone";
	    $this->assertEquals($b->blue(), 255, "Cloning an object does not work!");
	    echo " passed (check clone)";
	}

	/**
	 * test cloning, change the clone and check the original	<br><br>
	 * <code>
	 * $a = new QColor(100,200,255);				<br>
	 * $b = clone $a;						<br>
	 * $b->setRed(75);						<br>
	 * $a->red(); // 100						<br>
	 * </code>
	 */
	function testClone2() {
	    $a = new QColor(100,200,255);
	    $b = clone $a;
	    echo "\ntesting clone";
	    $b->setRed(75);
	    $this->assertEquals($a->red(), 100, "Cloning an object does not work (error: original has changed)!");
	    echo " passed (check original)";
	}

	/**
	 * test cloning a custom object, change the original and test the clone		<br><br>
	 * <code>
	 * $a = new myColor(100,200,255,24);						<br>
	 * $b = clone $a;								<br>
	 * $b->myProperty; // 24							<br>
	 * </code>
	 */
	function testClone3() {
	    $a = new myColor(100,200,255,24);
	    $b = clone $a;
	    echo "\ntesting clone";
	    $this->assertEquals($b->myProperty, 24, "Cloning a selfwritten object does not work (error: property has changed)!");
	    echo " passed (check childs)";
	}

	/**
	 * test cloning a custom object, overwrite the __clone magic method and test the clone		<br><br>
	 * <code>
	 * $a = new myColor2(100,200,255,24);								<br>
	 * $b = clone $a;										<br>
	 * $b->myProperty; // 48, doubled by __clone()							<br>
	 * </code>
	 */
	function testClone4() {
	    $a = new myColor2(100,200,255,24);
	    $b = clone $a;
	    echo "\ntesting clone";
	    $this->assertEquals($b->myProperty, 48, "Cloning a selfwritten object does not work (error: __clone() was not called)!");
	    echo " passed (check __clone())";
	}

	/**
	 * test cloning a custom object, overwrite the __clone magic method and test the original	<br><br>
	 * <code>
	 * $a = new myColor2(100,200,255,24);								<br>
	 * $b = clone $a;										<br>
	 * $a->myProperty; // 24									<br>
	 * </code>
	 */
	function testClone5() {
	    $a = new myColor2(100,200,255,24);
	    $b = clone $a;
	    echo "\ntesting clone";
	    $this->assertEquals($a->myProperty, 24, "Cloning a selfwritten object does not work (error: original has been modified)!");
	    echo " passed (check original after __clone())";
	}

    function testObjectLifeCycle()
		{
			echo "testing deletion of object ";
			$color_a = new QColor(1,3,5);
			$color_a->__destruct();
			unset($color_a);
			$this->assertFalse( isset( $color_a ), "Object wasn't deleted properly\n" );
			echo "passed\n";
			
			echo "testing returning a Stack item, checking values ";
			$widget_a = new QWidget();
			$widget_a->resize( 24, 28 );
			$size_a = $widget_a->size();
			$this->assertEquals( $size_a->width(), $widget_a->width(), "return value of QWidget::size() is not correct\n" );
			echo "passed\n";
			
			echo "testing returning a Stack item, changing values ";
			$widget_a->resize( 26, 30 );
			$size_b = $widget_a->size();
			$this->assertEquals( $size_b->width(), 26, "" );
			$this->assertEquals( $size_a->width(), 24, "" );
//			$this->assertEquals( $widget_a->size(), $size_b->width() );
		}


    } // end test
    
?>