#!/usr/bin/env php
<?php

############################################################################
#
#  Copyright (C) 2006-2007 Trolltech ASA. All rights reserved.
#
#  This file is part of the example classes of the Qt Toolkit.
#
#  This file may be used under the terms of the GNU General Public
#  License version 2.0 as published by the Free Software Foundation
#  and appearing in the file LICENSE.GPL included in the packaging of
#  this file.  Please review the following information to ensure GNU
#  General Public Licensing requirements will be met:
#  http://trolltech.com/products/qt/licenses/licensing/opensource/
#
#  If you are unsure which license is appropriate for your use, please
#  review the following information:
#  http://trolltech.com/products/qt/licenses/licensing/licensingoverview
#  or contact the sales department at sales@trolltech.com.
#
#  In addition, as a special exception, Trolltech gives you certain
#  additional rights. These rights are described in the Trolltech GPL
#  Exception version 1.0, which can be found at
#  http://www.trolltech.com/products/qt/gplexception/ and in the file
#  GPL_EXCEPTION.txt in this package.
#
#  In addition, as a special exception, Trolltech, as the sole copyright
#  holder for Qt Designer, grants users of the Qt/Eclipse Integration
#  plug-in the right for the Qt/Eclipse Integration to link to
#  functionality provided by Qt Designer and its related libraries.
#
#  Trolltech reserves all rights not expressly granted herein.
#
#  Trolltech ASA (c) 2007
#
#  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
#  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
############################################################################


class Window extends QWidget {

	public $signals = array("");
	public $slots = array( "newScreenshot()",
		"setIcon(int)",
		"iconActivated(QSystemTrayIcon::ActivationReason)",
		"messageClicked()",
		"setVisible(bool)",
		"showMessage()");

    public function __construct() {
		parent::__construct();

        $this->createIconGroupBox();
        $this->createMessageGroupBox();

        $this->iconLabel->setMinimumWidth($this->durationLabel->sizeHint()->width());

        $this->createActions();
        $this->createTrayIcon();

		$this->connect($this->showMessageButton,
                SIGNAL("clicked()"), $this, SLOT("showMessage()"));

        $this->connect($this->iconComboBox,
                SIGNAL("currentIndexChanged(int)"), $this, SLOT("setIcon(int)"));

        $this->connect($this->showIconCheckBox,
                SIGNAL("toggled(bool)"), $this->trayIcon,
                SLOT("setVisible(bool)"));

        $this->connect($this->trayIcon,
                SIGNAL("messageClicked()"), $this, SLOT("messageClicked()"));

        $this->connect($this->trayIcon,
                SIGNAL("activated(QSystemTrayIcon::ActivationReason)"),
                $this, SLOT("iconActivated(QSystemTrayIcon::ActivationReason)"));

        $mainLayout = new QVBoxLayout();
        $mainLayout->addWidget($this->iconGroupBox);
        $mainLayout->addWidget($this->messageGroupBox);
        $this->setLayout($mainLayout);

        $this->iconComboBox->setCurrentIndex(1);
        $this->trayIcon->show();

        $this->setWindowTitle($this->tr("Systray"));
        $this->resize(400, 300);
	}

    public function setVisible($visible) {
        $this->minimizeAction->setEnabled($visible);
        //$this->maximizeAction->setEnabled(! $this->isMaximized());
        $this->restoreAction->setEnabled($this->isMaximized() or !$visible);
		parent::setVisible($visible);
	}

    public function closeEvent($event) {
		/*
        if ($this->trayIcon->isVisible()):
            QtGui.QMessageBox.information($$this->tr("Systray"),
                    $this->tr("The program will keep running in the system ".
                        "tray. To terminate the program, choose <b>Quit</b> ".
                        "in the context menu of the system tray entry."));
            $this->hide();
            event.ignore();

		endif;
		 */
	}

    public function setIcon($index){
        $icon = $this->iconComboBox->itemIcon($index);
        $this->trayIcon->setIcon($icon);
        $this->setWindowIcon($icon);

        $this->trayIcon->setToolTip($this->iconComboBox->itemText($index));

	}

    public function iconActivated($reason) {
		var_dump("** Activated");
		var_dump($reason);
        if ($reason == QSystemTrayIcon::Trigger()
                or $reason == QSystemTrayIcon::DoubleClick()):
            $this->iconComboBox->setCurrentIndex(
                    ($this->iconComboBox->currentIndex() + 1)
                    % $this->iconComboBox->count());
		elseif ($reason == QSystemTrayIcon::MiddleClick()):
            $this->showMessage();
		endif;

	}
    public function showMessage() {

		$index = $this->typeComboBox->currentIndex();
        $strVal = (string)$this->typeComboBox->itemData($index)->toString();
		switch ($index) {
			case 1:
        	$icon = QSystemTrayIcon::Information();
			break;

			case 2:
        	$icon = QSystemTrayIcon::Warning();
			break;

			case 3:
        	$icon = QSystemTrayIcon::Critical();
			break;
		}
		/*
        $icon = QSystemTrayIcon::MessageIcon(
             $this->typeComboBox->itemData($index);

		 */
        $this->trayIcon->showMessage($this->titleEdit->text(),
                $this->bodyEdit->toPlainText(), $icon,
                $this->durationSpinBox->value() * 1000);

	}

    public function messageClicked() {
		$box = new QMessageBox();
		$box->information($this, new QString(tr("Systray")),
		//QMessageBox::information($this, new QString(tr("Systray")),
			tr("Sorry, I already gave what help I could.\nMaybe you should try asking a human?")
			,QMessageBox::Ok, QMessageBox::Cancel
		);
	}

    public function createIconGroupBox() {
        $this->iconGroupBox = new QGroupBox($this->tr("Tray Icon"));

        $this->iconLabel = new QLabel("Icon:");

        $this->iconComboBox = new QComboBox();
        $this->iconComboBox->addItem(new QIcon("./images/bad.svg"),
                $this->tr("Bad"));
        $this->iconComboBox->addItem(new QIcon("./images/heart.svg"),
                $this->tr("Heart"));
        $this->iconComboBox->addItem(new QIcon("./images/trash.svg"),
                $this->tr("Trash"));

        $this->showIconCheckBox = new QCheckBox($this->tr("Show icon"));
        $this->showIconCheckBox->setChecked(True);

        $iconLayout = new QHBoxLayout();
        $iconLayout->addWidget($this->iconLabel);
        $iconLayout->addWidget($this->iconComboBox);
        $iconLayout->addStretch();
        $iconLayout->addWidget($this->showIconCheckBox);
        $this->iconGroupBox->setLayout($iconLayout);

	}
    public function createMessageGroupBox() {
        $this->messageGroupBox = new QGroupBox($this->tr("Balloon Message"));

        $this->typeLabel = new QLabel($this->tr("Type:"));

        $this->typeComboBox = new QComboBox();
        $this->typeComboBox->addItem($this->tr("None"),
                new QVariant(QSystemTrayIcon::NoIcon));
        $this->typeComboBox->addItem($this->style()->standardIcon(
                QStyle::SP_MessageBoxInformation), $this->tr("Information"),
                New QVariant(QSystemTrayIcon::Information));
        $this->typeComboBox->addItem($this->style()->standardIcon(
                QStyle::SP_MessageBoxWarning), $this->tr("Warning"),
                New QVariant(QSystemTrayIcon::Warning));
        $this->typeComboBox->addItem($this->style()->standardIcon(
                QStyle::SP_MessageBoxCritical), $this->tr("Critical"),
                New QVariant(QSystemTrayIcon::Critical));
        $this->typeComboBox->setCurrentIndex(1);

        $this->durationLabel = new QLabel($this->tr("Duration:"));

        $this->durationSpinBox = new QSpinBox();
        $this->durationSpinBox->setRange(5, 60);
        $this->durationSpinBox->setSuffix(" s");
        $this->durationSpinBox->setValue(15);

        $this->durationWarningLabel = new QLabel($this->tr("(some systems might ".
                "ignore this hint)"));
        $this->durationWarningLabel->setIndent(10);

        $this->titleLabel = new QLabel($this->tr("Title:"));

        $this->titleEdit = new QLineEdit($this->tr("Cannot connect to network"));

        $this->bodyLabel = new QLabel($this->tr("Body:"));

        $this->bodyEdit = new QTextEdit();
        $this->bodyEdit->setPlainText($this->tr("Don't believe me. Honestly, I ".
                "don't have a clue.\nClick this balloon for details."));
		/*
		 */

        $this->showMessageButton = new QPushButton($this->tr("Show Message"));
        $this->showMessageButton->setDefault(True);

        $messageLayout = new QGridLayout();
        $messageLayout->addWidget($this->typeLabel, 0, 0);
        $messageLayout->addWidget($this->typeComboBox, 0, 1, 1, 2);
        $messageLayout->addWidget($this->durationLabel, 1, 0);
        $messageLayout->addWidget($this->durationSpinBox, 1, 1);
        $messageLayout->addWidget($this->durationWarningLabel, 1, 2, 1, 3);
        $messageLayout->addWidget($this->titleLabel, 2, 0);
        $messageLayout->addWidget($this->titleEdit, 2, 1, 1, 4);
        $messageLayout->addWidget($this->bodyLabel, 3, 0);
        $messageLayout->addWidget($this->bodyEdit, 3, 1, 2, 4);
        $messageLayout->addWidget($this->showMessageButton, 5, 4);
        $messageLayout->setColumnStretch(3, 1);
        $messageLayout->setRowStretch(4, 1);
        $this->messageGroupBox->setLayout($messageLayout);

	}
    public function createActions() {
        $this->minimizeAction = new QAction($this->tr("Mi&nimize"), $this);
        $this->connect($this->minimizeAction,
                SIGNAL("triggered()"), $this, SLOT("hide()"));

		/*
        $this->maximizeAction = new QAction($this->tr("Ma&ximize"), $this);
        QObject::connect($this->maximizeAction,
               SIGNAL("triggered()"), $this,
               SLOT("showMaximized()"));

		 */
        $this->restoreAction = new QAction($this->tr("&Restore"), $this);
		$this->connect($this->restoreAction,
                SIGNAL("triggered()"), $this,
                SLOT("showNormal()"));

		/*
        $this->quitAction = new QAction($this->tr("&Quit"), $this);
		QObject::connect($this->quitAction, SIGNAL("triggered()"),
                new QApplication(), SLOT("quit()"));
		 */

	}
    public function createTrayIcon() {
         $this->trayIconMenu = new QMenu();
         $this->trayIconMenu->addAction($this->minimizeAction);
         $this->trayIconMenu->addAction($this->restoreAction);
		 /*
         $this->trayIconMenu->addAction($this->maximizeAction);
         $this->trayIconMenu->addSeparator();
         $this->trayIconMenu->addAction($this->quitAction);
		  */

         $this->trayIcon = new QSystemTrayIcon();
         $this->trayIcon->setContextMenu($this->trayIconMenu);
		 $icon = new QIcon("./images/bad.png");
         $this->trayIcon->setIcon($icon);
	}
}

$app = new QApplication($argc, $argv);

if (!QSystemTrayIcon::isSystemTrayAvailable()) {
	die('no tray available');
}
/*
if not QtGui.QSystemTrayIcon.isSystemTrayAvailable():
	QtGui.QMessageBox.critical(None, QtCore.QObject.tr(app, "Systray"),
			QtCore.QObject.tr(app, "I couldn't detect any system tray on "
				"this system."))
	sys.exit(1)
*/

$screenshot = new Window();
$screenshot->show();
$app->exec();