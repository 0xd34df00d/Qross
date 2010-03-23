<?php
class TreeModel extends QAbstractItemModel
{
	/**
	 * @var TreeItem
	 */
	private $rootItem;
	
	public function __construct( QString $data, QObject $parent = NULL )
	{
		parent::__construct($parent);
		$rootData = array();
		array_push($rootData,"Title");
		array_push($rootData,"Summary");
		$this->rootItem = new TreeItem($rootData);
		$this->setupModelData(explode("\n",$data), $this->rootItem);
	}
	
	/**
	 * @param QModelIndex $index
	 * @param int $role
	 * @return QVariant
	 */
	public function data( QModelIndex $index, $role )
	{
		if(!$index->isValid())
			return new QVariant;

		if($role != Qt::DisplayRole)
			return new QVariant;

		$item = $index->internalPointer();

		return $item->data($index->column());
	}
	
	/**
	 * @param QModelIndex $index
	 * @return Qt::ItemFlags
	 */
	public function flags( QModelIndex $index )
	{
		if(!$index->isValid())
			return 0;
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
	
	/**
	 * @param int $section
	 * @param Qt::Orientation $orientation
	 * @param int role
	 * @return QVariant
	 */
	public function headerData( $section, $orientation, $role = Qt::DisplayRole)
	{
		if($orientation == Qt::Horizontal && $role == Qt::DisplayRole)
			return $this->rootItem->data($section);
		return new QVariant;
	}
	
	/**
	 * @param int $row
	 * @param int column
	 * @param QModelIndex $parent
	 * @return QModelIndex
	 */
	public function index( $row, $column, QModelIndex $parent )
	{
		if(!$this->hasIndex($row, $column, $parent))
			return new QModelIndex;

		$parentItem = new TreeItem;

		if(!$parent->isValid())
			$parentItem = $this->rootItem;
		else
			$parentItem = $parent->internalPointer();

		$childItem = $parentItem->child($row);
		if($childItem)
			return $this->createIndex($row, $column, $childItem);
		else
			return new QModelIndex;
	}
	
	/**
	 * @param QModelIndex $index
	 * @return QModelIndex
	 */
	public function parentIndex( QModelIndex $index )
	{
		if(!$index->isValid())
			return new QModelIndex;

		$childItem = $index->internalPointer();
		$parentItem = $childItem->parent();

		if($parentItem == $this->rootItem)
			return new QModelIndex;

		return $this->createIndex($parentItem->row(), 0, $parentItem);
	}
	
	/**
	 * @param QModelIndex $parent
	 * @return int
	 */
	public function rowCount( QModelIndex $parent )
	{
		$parentItem = new TreeItem;
		if($parent->column() > 0)
			return 0;

		if(!$parent->isValid())
			$parentItem = $this->rootItem;
		else
			$parentItem = $parent->internalPointer();

		return $parentItem->childCount();
	}
	
	/**
	 * @param QModelIndex $parent
	 * @return int
	 */
	public function columnCount( QModelIndex $parent )
	{
		if($parent->isValid())
			return $parent->internalPointer()->columnCount();
		else
			return $this->rootItem->columnCount();
	}

	private function setupModelData( QStringList $lines, TreeItem $parent )
	{
		$parents = array();
		$indentations = array();
		array_push($parents,$parent);
		array_push($indentations,0);

		$number = 0;

		while($number < $lines->count()) {
			$position = 0;
			while($position < $lines[$number]->length()) {
				if($lines[$number]->mid($position, 1) != " ")
					break;
				$position++;
	         }

			$lineData = new QString($lines[$number]->mid($position)->trimmed());
	
			if(!$lineData->isEmpty()) {
				// Read the column data from the rest of the line.
				$columnStrings = $lineData->split("\t", QString::SkipEmptyParts);
				$columnData = array();
				for($column = 0; $column < $columnStrings->count(); ++$column)
					array_push($columnData,$columnStrings[$column]);
	
				if($position > $indentations[count($indentations)]) {
					// The last child of the current parent is now the new parent
					// unless the current parent has no children.
	
					if($parents[count($parents)]->childCount() > 0) {
						array_push($parent, $parents[count($parents)]->child($parents[count($parents)]->childCount()-1));
						array_push($indentations, $position);
	                 }
				}
				else {
					while($position < $indentations[count($indentations)] && count($parents) > 0) {
						array_pop($parents);
						array_pop($indentations);
	                 }
	             }
	
				// Append a new item to the current parent's list of children.
				$parents[count($parents)]->appendChild(new TreeItem($columnData, $parents[count($parents)]));
	         }
			$number++;
		}
	}
}
?>