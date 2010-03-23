<?php

    /**
     *	This file tests if the module loads properly
     */

    require_once('config.php');
    require_once($tests_path.'/testModelView.php');

    require_once('PHPUnit/Framework/TestCase.php');
    require_once('PHPUnit/Framework/TestSuite.php');


    class QtModelViewTestCase extends PHPUnit_Framework_TestCase {
    
	public function __construct($name="") {
	    parent::__construct($name);
	}

	/**
	 * runs a simple model/view app for a moment
	 */
    
	function testModelView() 
	{
	    if( !QCoreApplication::instance() )
	    {
		$argv = array("");
		$app = new QApplication( 1, $argv );
	    }

	    $model_a = new MyItemModel();
	    $treeView = new QTableView();	    
	    $treeView->setModel( $model_a );
	    $treeView->show();
	    QTimer::singleShot( 100, QCoreApplication::instance(), SLOT("quit()") );
	    $app->exec();
	}

    }    
    
?>