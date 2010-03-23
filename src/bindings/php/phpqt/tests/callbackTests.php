<?php

require_once( 'cannonfield.php' );
require_once( 'lcdrange.php' );

class MyWidget extends QWidget
{

  private $angle;
  private $quit;
  private $cannonField;

  public function __construct()
  {
    parent::__construct();
  }

  public function paintEvent( $event )
  {
    echo ".";
  }

  /*
   * will be called by the unittest
   */

  public function invokeSetValue( $value )
  {
    echo $this->angle->setValue( $value );
    echo ".";
  }

  public function setupConnections()
  {

    $this->quit = new QPushButton(tr("Quit"));
    $this->quit->setFont(new QFont("Times", 18, QFont::Bold));

    QObject::connect($this->quit, SIGNAL('clicked()'), QApplication::instance(), SLOT('quit()'));
    
    $this->angle = new LCDRange();
       $this->angle->setRange(5, 70);
       /*
    $this->cannonField = new CannonField();
    */
    //    QObject::connect($this->angle, SIGNAL('valueChanged(int)'), $this->cannonField, SLOT('setAngle(int)'));
    //    QObject::connect($this->cannonField, SIGNAL('angleChanged(int)'), $this->angle, SLOT('setValue(int)'));

  }

}

$app = new QApplication( $argc, $argv );
$m = new MyWidget();
__phpqt_unittest_invoke( $m );

?>