<?php
require_once 'treeitem.php';
require_once 'treemodel.php';

$app = new QApplication($argc, $argv);

$file = new QFile("default.txt");
$file->open(QIODevice::ReadOnly);
$model = new TreeModel($file->readAll());
$file->close();

$view = new QTreeView;
$view->setModel($model);
$view->setWindowTitle(QObject::tr("Simple Tree Model"));
$view->show();
$app->exec();
?>