<?php

/********************************************************************************
** Form generated from reading ui file 'designer.ui'
**
** Created: Fri Feb 29 17:59:31 2008
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

class Ui_Dialog
{
    public $buttonBox; //QDialogButtonBox
    public $textBrowser; //QTextBrowser
    public $lineEdit; //QLineEdit

    public function setupUi(/*QDialog*/ $Dialog)
    {
    if ($Dialog->objectName()->isEmpty())
        $Dialog->setObjectName(QString::fromUtf8("Dialog"));
    $size = new QSize(394, 311);
    $size = $size->expandedTo($Dialog->minimumSizeHint());
    $Dialog->resize($size);
    $this->buttonBox = new QDialogButtonBox($Dialog);
    $buttonBox = $this->buttonBox; // scope
    $buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    $buttonBox->setGeometry(new QRect(40, 270, 341, 32));
    $buttonBox->setOrientation(Qt::Horizontal);
    $buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);
    $this->textBrowser = new QTextBrowser($Dialog);
    $textBrowser = $this->textBrowser; // scope
    $textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    $textBrowser->setGeometry(new QRect(10, 10, 371, 211));
    $this->lineEdit = new QLineEdit($Dialog);
    $lineEdit = $this->lineEdit; // scope
    $lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    $lineEdit->setGeometry(new QRect(10, 230, 371, 25));

    $this->retranslateUi($Dialog);
    QObject::connect($buttonBox, SIGNAL('accepted()'), $Dialog, SLOT('accept()'));
    QObject::connect($buttonBox, SIGNAL('rejected()'), $Dialog, SLOT('reject()'));

    QMetaObject::connectSlotsByName($Dialog);
    } // setupUi

    public function retranslateUi(/*QDialog*/ $Dialog)
    {
    $Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    $buttonBox = $this->buttonBox; // scope
    $textBrowser = $this->textBrowser; // scope
    $lineEdit = $this->lineEdit; // scope
    Q_UNUSED($Dialog);
    } // retranslateUi

}

?>
