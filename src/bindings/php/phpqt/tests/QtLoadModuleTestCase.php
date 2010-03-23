<?php

    /**
     *	This file tests if the module loads properly
     */

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');


    class QtLoadModuleTestCase extends PHPUnit_Framework_TestCase {
    
	public function __construct($name="") {
	    parent::__construct($name);
	}

	/**
	 * test if extension has been loaded
	 */
	function testModule() {
	    $this->assertTrue(extension_loaded('php_qt'), "Module PHP-Qt is not loaded!");
	}

	/**
	 * test if class 'Qt' exist
	 */
	function testClassQt() {
	    $this->assertTrue(class_exists('Qt'), "class Qt not found!");
	}

	/**
	 * test if class QString exist
	 */
	function testClassQString() {
	    $this->assertTrue(class_exists('QString'), "class QString not found!");
	}

    }    
    
?>