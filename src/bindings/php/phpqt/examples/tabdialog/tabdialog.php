<?php
class GeneralTab extends QWidget
{
	public function __construct( QFileInfo $fileInfo, QWidget $parent = NULL )
	{
		parent::__construct($parent);
		$fileNameLabel = new QLabel(tr("File Name:"));
		$fileNameEdit = new QLineEdit($fileInfo->fileName());

		$pathLabel = new QLabel(tr("Path:"));
		$pathValueLabel = new QLabel($fileInfo->absoluteFilePath());
		$pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		$sizeLabel = new QLabel(tr("Size:"));
		$size = $fileInfo->size()/1024;
		$sizeValueLabel = new QLabel(tr("%1 K")->arg($size));
		$sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		$lastReadLabel = new QLabel(tr("Last Read:"));
		$lastReadValueLabel = new QLabel($fileInfo->lastRead()->toString());
		$lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		$lastModLabel = new QLabel(tr("Last Modified:"));
		$lastModValueLabel = new QLabel($fileInfo->lastModified()->toString());
		$lastModValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		$mainLayout = new QVBoxLayout;
		$mainLayout->addWidget($fileNameLabel);
		$mainLayout->addWidget($fileNameEdit);
		$mainLayout->addWidget($pathLabel);
		$mainLayout->addWidget($pathValueLabel);
		$mainLayout->addWidget($sizeLabel);
		$mainLayout->addWidget($sizeValueLabel);
		$mainLayout->addWidget($lastReadLabel);
		$mainLayout->addWidget($lastReadValueLabel);
		$mainLayout->addWidget($lastModLabel);
		$mainLayout->addWidget($lastModValueLabel);
		$mainLayout->addStretch(1);
		$this->setLayout($mainLayout);
	}
}

class PermissionsTab extends QWidget
{
	public function __construct( QFileInfo $fileInfo, QWidget $parent = NULL )
	{
		parent::__construct($parent);
		$permissionsGroup = new QGroupBox(tr("Permissions"));

		$readable = new QCheckBox(tr("Readable"));
		if($fileInfo->isReadable())
			$readable->setChecked(true);

		$writable = new QCheckBox(tr("Writable"));
		if( $fileInfo->isWritable() )
			$writable->setChecked(true);

		$executable = new QCheckBox(tr("Executable"));
		if( $fileInfo->isExecutable() )
			$executable->setChecked(true);

		$ownerGroup = new QGroupBox(tr("Ownership"));

		$ownerLabel = new QLabel(tr("Owner"));
		$ownerValueLabel = new QLabel($fileInfo->owner());
		$ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		$groupLabel = new QLabel(tr("Group"));
		$groupValueLabel = new QLabel($fileInfo->group());
		$groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		$permissionsLayout = new QVBoxLayout;
		$permissionsLayout->addWidget($readable);
		$permissionsLayout->addWidget($writable);
		$permissionsLayout->addWidget($executable);
		$permissionsGroup->setLayout($permissionsLayout);

		$ownerLayout = new QVBoxLayout;
		$ownerLayout->addWidget($ownerLabel);
		$ownerLayout->addWidget($ownerValueLabel);
		$ownerLayout->addWidget($groupLabel);
		$ownerLayout->addWidget($groupValueLabel);
		$ownerGroup->setLayout($ownerLayout);

		$mainLayout = new QVBoxLayout;
		$mainLayout->addWidget($permissionsGroup);
		$mainLayout->addWidget($ownerGroup);
		$mainLayout->addStretch(1);
		$this->setLayout($mainLayout);
	}
}

class ApplicationsTab extends QWidget
{
	public function __construct( QFileInfo $fileInfo, QWidget $parent = NULL )
	{
		parent::__construct($parent);
		$topLabel = new QLabel(tr("Open with:"));

		$applicationsListBox = new QListWidget;
		$applications = array();

		for($i = 1; $i <= 30; ++$i)
			$applications[] = tr("Application %1")->arg($i);
			$applicationsListBox->insertItems(0, $applications);

		$alwaysCheckBox = new QCheckBox;

		if($fileInfo->suffix()->isEmpty())
			$alwaysCheckBox = new QCheckBox(tr("Always use this application to "
             ."open this type of file"));
		else
			$alwaysCheckBox = new QCheckBox(tr("Always use this application to "
             ."open files with the extension '%1'").arg($fileInfo->suffix()));

		$layout = new QVBoxLayout;
		$layout->addWidget($topLabel);
		$layout->addWidget($applicationsListBox);
		$layout->addWidget($alwaysCheckBox);
		$this->setLayout($layout);
	}
}

class TabDialog extends QDialog
{
	/**
 	 * @var QTabWidget
 	 */
	private $tabWidget;
	/**
	 * @var QDialogButtonBox
	 */
	private $buttonBox;
	
 	public function __construct( $fileName, QWidget $parent = NULL )
 	{
 		parent::__construct($parent);
		$fileInfo = new QFileInfo($fileName);

		$this->tabWidget = new QTabWidget;
		$this->tabWidget->addTab(new GeneralTab($fileInfo), tr("General"));
		$this->tabWidget->addTab(new PermissionsTab($fileInfo), tr("Permissions"));
		$this->tabWidget->addTab(new ApplicationsTab($fileInfo), tr("Applications"));

		$this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);

		$this->connect($this->buttonBox, SIGNAL("accepted()"), $this, SLOT("accept()"));
		$this->connect($this->buttonBox, SIGNAL("rejected()"), $this, SLOT("reject()"));

		$mainLayout = new QVBoxLayout;
		$mainLayout->addWidget($this->tabWidget);
		$mainLayout->addWidget($this->buttonBox);
		$this->setLayout($mainLayout);

		$this->setWindowTitle(tr("Tab Dialog"));
 	}

}
?>