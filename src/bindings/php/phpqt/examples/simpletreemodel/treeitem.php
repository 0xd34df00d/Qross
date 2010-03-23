<?php
class TreeItem 
{
	public $childItems=array();
	private $itemData=array();
	/**
	 * @var TreeItem
	 */
	private $parentItem;

	public function __construct( array $data, TreeItem $parent = NULL )
	{
		$this->parentItem = $parent;
		$this->itemData = $data;
	}
	
	public function appendChild( TreeItem $child )
	{
		array_push($this->childItems,$child);
	}

	/**
	 * @param int $row
	 * @return TreeItem
	 */
	public function child($row)
	{
		return $this->childItems[$row];
	}
	
	/**
	 * @return int
	 */
	public function childCount()
	{
		return count($this->childItems);
	}
	
	/**
	 * @return int
	 */
	public function columnCount()
	{
		return count($this->itemData);
	}
	
	/**
	 * @param int $column
	 * @return QVariant
	 */
	public function data($column)
	{
		return $this->itemData[$column];
	}
	
	/**
	 * @return int
	 */
	public function row()
	{
		if(isset($this->parentItem) && is_object($this->parentItem) && $this->parentItem instanceof TreeItem)
			return array_search($this,$this->parentItem->childItems);
		return false;
	}
	
	/**
	 * @return TreeItem
	 */
	public function parentItem()
	{
		return $this->parentItem;
	}

}
?>