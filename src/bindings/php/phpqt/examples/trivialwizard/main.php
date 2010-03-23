<?php
/**
 * @return  QWizardPage
 */
function createIntroPage()
{
	$page = new QWizardPage;
	$page->setTitle("Introduction");

	$label = new QLabel("This wizard will help you register your copy "
                                ."of Super Product Two.");
	$label->setWordWrap(true);

	$layout = new QVBoxLayout;
	$layout->addWidget($label);
	$page->setLayout($layout);

	return $page;
}

/**
 * @return QWizardPage
 */
function createRegistrationPage()
{
	$page = new QWizardPage;
	$page->setTitle("Registration");
	$page->setSubTitle("Please fill both fields.");
	
	$nameLabel = new QLabel("Name:");
	$nameLineEdit = new QLineEdit;

	$emailLabel = new QLabel("Email address:");
	$emailLineEdit = new QLineEdit;

	$layout = new QGridLayout;
	$layout->addWidget($nameLabel, 0, 0);
	$layout->addWidget($nameLineEdit, 0, 1);
	$layout->addWidget($emailLabel, 1, 0);
	$layout->addWidget($emailLineEdit, 1, 1);
	$page->setLayout($layout);

	return $page;
}

/**
 * @return QWizardPage
 */
function createConclusionPage()
{
	$page = new QWizardPage;
	$page->setTitle("Conclusion");

	$label = new QLabel("You are now successfully registered. Have a "
                                ."nice day!");
	$label->setWordWrap(true);

	$layout = new QVBoxLayout;
	$layout->addWidget($label);
	$page->setLayout($layout);

	return $page;
}

$app = new QApplication($argc, $argv);

$translatorFileName = new QString("qt_");
$translatorFileName += QLocale->system()->name();
$translator = new QTranslator($app);
if($translator->load($translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
         $app->installTranslator($translator);

$wizard = new QWizard;
$wizard->addPage(createIntroPage());
$wizard->addPage(createRegistrationPage());
$wizard->addPage(createConclusionPage());

$wizard->setWindowTitle("Trivial Wizard");
$wizard->show();

$app->exec();
?>