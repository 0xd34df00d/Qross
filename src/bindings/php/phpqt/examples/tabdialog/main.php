<?php
require_once 'tabdialog.php';

$app = new QApplication($argc, $argv);
$filename = new QString;

if($argc >= 2)
	$fileName = $argv[1];
else
	$fileName = ".";

$tabdialog = new TabDialog($fileName);
$tabdialog->exec();
?>