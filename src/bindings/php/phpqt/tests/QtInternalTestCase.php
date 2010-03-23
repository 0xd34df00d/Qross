<?php

    /**
     *	This file tests if the module loads properly
     */

    require_once('config.php');
    require_once($tests_path.'/callbackTests.php');

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');


    class QtInternalTestCase extends PHPUnit_Framework_TestCase {
    
	public function __construct($name="") {
	    parent::__construct($name);
	}
    
	function testInternals() 
	{
	    if( !QCoreApplication::instance() )
	    {
		$argv = array("");
		$app = new QApplication( 1, $argv );
	    }
	    $m = new MyWidget();	    
	    __phpqt_unittest_invoke( $m );
	}

    }    
    
?>