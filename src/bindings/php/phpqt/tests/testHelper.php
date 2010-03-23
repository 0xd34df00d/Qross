<?php

    // NOTICE for testing pure virtual methods extend a QAbstractButton and check the paintEvent() method

    /* 
     * check if we can fetch constants
     */

    class foo extends QObject {
    	const a = "a";
    	const b = 24;

    	public function __construct($parent)
    	{
    		parent::__construct($parent);
    	}

    	public function testMethod($value = NULL) {
    		if ($value) echo $value."\n";
    	}

    	public static function staticMethod()
    	{
    		return "staticMethod";
    	}

    	//	    parent::tr("");

    	public static function staticTrMethod($arg)
    	{
  			return parent::tr($arg);
    	}

    	public function blockSignals($bool)
    	{
	    return parent::blockSignals($bool);
    	}
    }

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
		public $slotTester;
		
		private $signals = array("testSignal()");
		private $slots = array("testSlot()", "testSignalSignal");
		
		public function __construct()
		{
			parent::__construct();
			$this->button = new QPushButton(tr("quit"), $this);
			$this->connect($this->button, SIGNAL('clicked()'), QCoreApplication::instance(), SLOT('quit()'));
			$this->connect( $this, SIGNAL('testSignal()'), $this, SLOT('testSlot()') );
			$this->connect( $this, SIGNAL('testSignal()'), $this, SLOT('show()') );
			$this->slotTester = "";
		}
		
		public function testSlot()
		{
			$this->slotTester = "slot called";
		}
    }

    class MyWidget2 extends QWidget
    {
    	public function __construct()
    	{
    		parent::__construct();
    	}

    	public function sizeHint()
    	{
    		return parent::sizeHint();
    	}
    }
    
    class MyButton extends QCheckBox
    {
    	public $slotTester;

    	private $signals = array("testSignal()", "testSignalSignal()");
    	private $slots = array("testSlot()");

    	public function __construct()
    	{
    		parent::__construct();

    		$this->connect( $this, SIGNAL('testSignal()'), $this, SLOT('testSlot()') );
    		$this->connect( $this, SIGNAL('testSignal()'), $this, SLOT('show()') );

    		$this->connect( $this, SIGNAL('testSignalSignal()'), $this, SIGNAL('clicked()') );
    		//		$this->connect( $this, SIGNAL('clicked()'), $this, SLOT('testSlot()') );
    		//		$this->connect( $this, SIGNAL('clicked()'), $this, SLOT('toggle()') );
    		$this->connect( $this, SIGNAL('pressed()'), $this, SIGNAL('testSignalSignal()') );
    		$this->connect( $this, SIGNAL('released()'), $this, SIGNAL('pressed()') );

    		$this->connect( $this, SIGNAL('clicked(bool)'), $this, SLOT('setChecked(bool)') );

    		$this->slotTester = "";
    	}

    	public function testSlot()
    	{
    		$this->slotTester = "slot called";
    	}
    }

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
