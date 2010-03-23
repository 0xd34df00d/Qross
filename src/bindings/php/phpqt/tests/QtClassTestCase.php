<?php

    /**
     * test of Qt based objects:
     * - Signals/Slots
     * - constructors
     */

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');

    require_once('config.php');
    require_once($tests_path.'/testHelper.php');

    class QtClassTestCase extends PHPUnit_Framework_TestCase {

	private $app;

	public function __construct($name="") {
	    parent::__construct($name);
		$this->createQApplicationInstance();
	}

	/**
	 * test of creating an instance of QApplication if none exists
	 */

	public function createQApplicationInstance()
	{
	    if( !QCoreApplication::instance() )
	    {
		$argc=1;
		$argv=array("argv");
		$this->app = new QApplication($argc,$argv);
	    } else {
		$this->app = QCoreApplication::instance();
	    }
	}

	/**
	 * tests of emitting signals
	 * - emitting a signal defined in PHP: testSignal() -> testSlot()
	 * - emitting a signal defined in PHP that calls a C++ slot: testSignal() -> show()
	 * - emitting a C++ signal that calls a PHP slot: testSignalSignal() -> clicked()
	 * - emitting a C++ signal that calls a C++ slot: clicked() -> toggle()
	 * - emitting a C++ signal that emits a PHP signal: pressed() -> testSignalSignal()
	 * - emitting a C++ signal that emits a C++ signal: released() -> pressed()
	 * - emitting a C++ signal with a primitive argument: clicked(true) -> setChecked(bool)
	 */

	public function testEmitSignal()
	{
		$m = new MyButton();
		
		echo "testing emitting a PHP signal ";
		emit( $m->testSignal() );
		$this->assertEquals( $m->slotTester, "slot called", "Signal could not be emitted or testSlot() could not be called\n" ); 
		echo "done\n";
		
		$m->slotTester = ""; // reset

		echo "testing emitting a PHP signal that calls a C++ slot ";
		emit( $m->testSignal() );
		echo "done\n";
		
		// emitting a C++ signal that calls a PHP slot
		echo "testing emitting a PHP signal that emits a C++ signal: testSignalSignal() -> clicked() ";
		emit( $m->testSignalSignal() );
		echo "done\n";
		
		// emitting a C++ signal that calls a C++ slot
		echo "testing emitting a C++ signal that calls a C++ slot: clicked() -> toggle() ";
		emit( $m->clicked() );
		echo "done\n";
		
		echo "testing emitting a C++ signal that emits a PHP signal: pressed() -> testSignalSignal() ";
		emit( $m->pressed() );
		echo "done\n";
		
		echo "testing emitting a C++ signal that emits a C++ signal: released() -> pressed() ";
		emit( $m->released() );
		echo "done\n";
		
		// calling signal/slots using basic type arguments
		echo "testing emitting a C++ signal with a boolean argument clicked(true) -> setChecked(bool) ";
		emit( $m->clicked(true) );
		$this->assertTrue( $m->isChecked(), "Could not emit signal with boolean argument" );
		echo "done\n";
		
		// calling signal/slots using basic type arguments
		echo "testing emitting a C++ signal with a boolean argument clicked(false) -> setChecked(bool) ";
		emit( $m->clicked(false) );
		$this->assertFalse( $m->isChecked(), "Could not emit signal with boolean argument" );
		echo "done\n";
		
		// TODO calling signal/slots using object type arguments
		
	}

    /**
     * cases:
     *	- Qt object exists, zval has been deleted, recreate at marshalling
     *	- Qt and zval exist, marshalling
     *	- Qt object deletion
     *	- zval deletion (explicit using destruct)
     *  - zval deletion (using refcount/garbage collection)
     */


    /**
     * copy an object using the copy constructor and check with them changing 
     * values of the original and the copy
     */

    function testCopyConstructor()
    {
	echo "testing copy constructor ";
	$color_a = new QColor(5,3,7);
	$color_b = new QColor($color_a);

	$this->assertEquals( 7, $color_a->blue() );
	$this->assertEquals( 7, $color_b->blue() );
	echo "passed\n";

	echo "testing changing the value at the copy ";
	$color_b->setBlue( 24 );

	$this->assertEquals( 7, $color_a->blue() );
	$this->assertEquals( 24, $color_b->blue() );
	echo "passed\n";
	
	echo "testing destroying the original ";
	$color_a->__destruct();
	unset( $color_a );
	$this->assertEquals( 24, $color_b->blue() );
	echo "passed\n";
    }

    function testShowHide()
    {
    		echo "\ntesting virtual method call 'sizeHint()' in a loop: ";

		$m = new myWidget();
		for( $i = 0; $i < 10; $i++ )
		{
			QTimer::singleShot(10,$m,SLOT("show()"));
			usleep(20000);
			$m->hide();
		}
		echo " passed";
    }

    /**
     * test model-view. It uses virtual methods a lot and new zvals for the same Qt object are created very often
     * 
     */

    function testModelView()
    {
		echo "\ntesting Model-View: ";

		$model_a = new MyItemModel();

    	$treeView = new QTableView();
    	$treeView->setModel( $model_a );

    	$treeView->show();

//    	QTimer::singleShot(10,QApplication::instance(),SLOT("quit()"));
//    	$this->app->exec();

		echo "passed\n";

    }

}

?>