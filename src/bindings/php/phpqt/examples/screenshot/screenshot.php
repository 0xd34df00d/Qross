<?php

class Screenshot extends QWidget
{

	public $signals = array("");
	public $slots = array( "newScreenshot()",
		"saveScreenshot()",
		"shootScreen()",
		"updateCheckBox()");
	
	/**
	 * @var QPixmap
	 */
	private $originalPixmap;

	/**
	 * @var QLabel
	 */
	private $screenshotLabel;
	
	/**
	 * @var QGroupBox
	 */
	private $optionsGroupBox;
	
	/**
	 * @var QSpinBox
	 */
	private $delaySpinBox;
	
	/**
	 * @var QLabel
	 */
	private $delaySpinBoxLabel;
	
	/**
	 * @var QCheckBox
	 */
	private $hideThisWindowCheckBox;
	
	/**
	 * @var QPushButon
	 */
	private $newScreenshotButton;
	
	/**
	 * @var QPushButton
	 */
	private $saveScreenshotButton;
	/**
	 * @var QPushButton
	 */
	private $quitScreenshotButton;

	/**
	 * @var QVBoxLayout
	 */
	private $mainLayout;
	
	/**
	 * @var QGridLayout
	 */
	private $optionsGroupBoxLayout;
	
	/**
	 * @var QHBoxLayout
	 */
	private $buttonsLayout;
	
	public function __construct()
	{
		parent::__construct();
		$this->screenshotLabel = new QLabel;
		$this->screenshotLabel->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);
		$this->screenshotLabel->setAlignment(Qt::AlignCenter);
		$this->screenshotLabel->setMinimumSize(240, 160);

		$this->createOptionsGroupBox();
		$this->createButtonsLayout();

		$this->mainLayout = new QVBoxLayout;
		$this->mainLayout->addWidget($this->screenshotLabel);
		$this->mainLayout->addWidget($this->optionsGroupBox);
		$this->mainLayout->addLayout($this->buttonsLayout);
		$this->setLayout($this->mainLayout);

		$this->shootScreen();
		$this->delaySpinBox->setValue(5);

		$this->setWindowTitle(tr("Screenshot"));
		$this->resize(300, 200);
	}

	protected function resizeEvent( QResizeEvent $event )
	{
		Q_UNUSED($event);
		$scaledSize = $this->originalPixmap->size();
		$scaledSize->scale($this->screenshotLabel->size(), Qt::KeepAspectRatio);
		if(!$this->screenshotLabel->pixmap() 
			|| $scaledSize != $this->screenshotLabel->pixmap()->size())
				$this->updateScreenshotLabel();
	}

	/**
	 * @slot
	 */
	public function newScreenshot()
	{
		if($this->hideThisWindowCheckBox->isChecked())
			$this->hide();
		$this->newScreenshotButton->setDisabled(true);

		QTimer::singleShot($this->delaySpinBox->value() * 1000, $this, SLOT("shootScreen()"));
	}
	
	/**
	 * @slot
	 */
	public function saveScreenshot()
	{
		$format = new QString("png");
		$initialPath = QDir::currentPath() . tr("/untitled.") . $format;

		$fileName = QFileDialog::getSaveFileName($this, tr("Save As"),
                                $initialPath,
                                tr("%1 Files (*.%2);;All Files (*)")
                                ->arg($format->toUpper())
                                ->arg($format));
		if(!$fileName->isEmpty())
		$this->originalPixmap->save($fileName, $format->toAscii());
	}
	
	/**
	 * @slot
	 */
	public function shootScreen()
	{
		if($this->delaySpinBox->value() != 0)
			QCoreApplication::instance()->beep();
		$this->originalPixmap = QPixmap::grabWindow(QCoreApplication::instance()->desktop()->winId());
		$this->updateScreenshotLabel();

		$this->newScreenshotButton->setDisabled(false);
		if($this->hideThisWindowCheckBox->isChecked())
			$this->show();
	}
	
	/**
	 * @slot
	 */
	public function updateCheckBox()
	{
		if($this->delaySpinBox->value() == 0)
			$this->hideThisWindowCheckBox->setDisabled(true);
		else
			$this->hideThisWindowCheckBox->setDisabled(false);
	}

	private function createOptionsGroupBox()
	{
		$this->optionsGroupBox = new QGroupBox(tr("Options"));

		$this->delaySpinBox = new QSpinBox;
		$this->delaySpinBox->setSuffix(tr(" s"));
		$this->delaySpinBox->setMaximum(60);
     
		$this->connect($this->delaySpinBox, SIGNAL("valueChanged(int)"), $this, SLOT("updateCheckBox()"));

		$this->delaySpinBoxLabel = new QLabel(tr("Screenshot Delay:"));

		$this->hideThisWindowCheckBox = new QCheckBox(tr("Hide This Window"));

		$this->optionsGroupBoxLayout = new QGridLayout;
		$this->optionsGroupBoxLayout->addWidget($this->delaySpinBoxLabel, 0, 0);
		$this->optionsGroupBoxLayout->addWidget($this->delaySpinBox, 0, 1);
		$this->optionsGroupBoxLayout->addWidget($this->hideThisWindowCheckBox, 1, 0, 1, 2);
		$this->optionsGroupBox->setLayout($this->optionsGroupBoxLayout);
	}
	
	private function createButtonsLayout()
	{
		$this->newScreenshotButton = $this->createButton(tr("New Screenshot"),
                                        $this, SLOT("newScreenshot()"));

		$this->saveScreenshotButton = $this->createButton(tr("Save Screenshot"),
                                         $this, SLOT("saveScreenshot()"));

		$this->quitScreenshotButton = $this->createButton(tr("Quit"), $this, SLOT("close()"));

		$this->buttonsLayout = new QHBoxLayout;
		$this->buttonsLayout->addStretch();
		$this->buttonsLayout->addWidget($this->newScreenshotButton);
		$this->buttonsLayout->addWidget($this->saveScreenshotButton);
		$this->buttonsLayout->addWidget($this->quitScreenshotButton);
	}

	/**
	 * @return QPushButton
	 */
	private function createButton( QString $text, QWidget $receiver, $member)
	{
		$button = new QPushButton($text);
		$button->connect($button, SIGNAL("clicked()"), $receiver, (string)$member);
		return $button;
	}
	
	private function updateScreenshotLabel()
	{
		$this->screenshotLabel->setPixmap($this->originalPixmap->scaled(
			$this->screenshotLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
	}

 }

?>