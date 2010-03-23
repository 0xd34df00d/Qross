<?php

/*   Usage of the User Interface Compiler:
     phpuic designer.ui -o ui_designer.php
*/

include('ui_designer.php');

$app = new QApplication($argc, $argv);
$window = new QDialog;

$ui = new Ui_Dialog();
$ui->setupUi($window);

$window->show(); 
$app->exec();

?>