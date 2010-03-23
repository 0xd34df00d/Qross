<?php

    /**
     */

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');

    class MyApplication extends QApplication
    {

	private $slots = array("mySlot()");
	private $signals = array("");
    
	public function __construct($argc, $argv)
	{
	    parent::__construct($argc, $argv);
	}
	
	function mySlot()
	{
	    echo " mySlot() ";
	}

    }

    class MyWidget extends QWidget
    {
	private $button;    

	public function __construct()
	{
	    parent::__construct();
	    $this->button = new QPushButton(tr("quit"), $this);
	    $this->connect($this->button, SIGNAL('clicked()'), QCoreApplication::instance(), SLOT('quit()'));
	}
    
    }

    class QtApplicationTestCase extends PHPUnit_Framework_TestCase {

	private $app;

	public function __construct($name="") {
	    parent::__construct($name);
	    $argc=1;
	    $argv=array("argv");
	    $this->app = new QApplication($argc,$argv);
	}

	// try to get the same object
	function testQApplicationInstance() {
	    echo "\ntesting getting object back";
	    $this->assertEquals(is_object(QApplication::instance()), true, "Could not fetch instance of QApplication!");
	    // we need this, otherwise ZE would destroy $app too early
	    QTimer::singleShot(100,QApplication::instance(),SLOT("quit()"));
	    echo " passed";
	}


	function testVirtualMethod() {
	    echo "\ntesting calling a virtual method";

/*    	    $argc=1;
	    $argv=array("argv");
	    $app = new MyApplication($argc, $argv);
*/
	    $myWidget = new MyWidget();
	    $myWidget->show();
	    $this->app->exec();

	    echo " passed";


	}

	function testCallingSlot()
	{
#return;
//            $clickedButton = qobject_cast($this->sender(), new QToolButton());
/*
    	    $argc=1;
	    $argv=array("argv");
	    $app = new MyApplication($argc, $argv);
*/
	    QTimer::singleShot(100,$this->app,SLOT("mySlot()"));
print "OK";
	    QTimer::singleShot(100,$this->app,SLOT("quit()"));
print "OK";
#	    $app->exec();
	}

    }

?>