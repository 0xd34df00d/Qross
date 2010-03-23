<?php


    class MyItemModel extends QAbstractItemModel
    {
	public $count;

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
		return 100;
	}

	function data( QModelIndex $index, $role )
	{
		return new QVariant("test".$index->column().$index->row());
	}

	function index( $row, $column )
	{
		return $this->createIndex( $row, $column );
	}

	function parent(QModelIndex $index)
	{
		return new QModelIndex();
	}
    }

?>