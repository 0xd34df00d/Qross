<?php


    class MyItemModel extends QAbstractItemModel
    {
	function __construct()
	{
		parent::__construct();
	}

	function columnCount()
	{
		return 5;
	}
	function rowCount()
	{
		return 2;
	}

	function index( $row, $column )
	{
		return new QModelIndex();
	}
    }

    $app = new QApplication( $argc, $argv );

    $model_a = new MyItemModel();
    $treeView = new QTreeView();
    $treeView->setModel( $model_a );

    $treeView->show();
    $app->exec();

?>