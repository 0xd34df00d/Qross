<?php
require_once 'screenshot.php';

$app = new QApplication($argc, $argv);
$screenshot = new Screenshot;
$screenshot->show();
$app->exec();
?>