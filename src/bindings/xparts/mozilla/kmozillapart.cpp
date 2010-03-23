#include "kmozillapart.h"

#include <dcopclient.h>
#include <dcopobject.h>
#include <kapplication.h>
#include <kstdaction.h>
#include <kaction.h>
#include <kmainwindow.h>
#include <kprocess.h>
#include <kparts/mainwindow.h>
#include <kdebug.h>
#include <kaboutdata.h>
#include <kparts/genericfactory.h>

typedef KParts::GenericFactory<KMozillaPart> KMozillaPartFactory;
K_EXPORT_COMPONENT_FACTORY( libkmozillapart, KMozillaPartFactory );

KMozillaPart::KMozillaPart(QWidget *parentWidget, const char *widgetName,
	                   QObject *parent, const char *name, const QStringList &)
	: XPartHost_KPart(parentWidget, widgetName, parent, name)
{
    setInstance( KMozillaPartFactory::instance() );

    m_partProcess = new KProcess;
    *m_partProcess << "kmozilla"
		   << kapp->dcopClient()->appId() << objId();
    m_partProcess->start();

    qDebug("---->>>>>> enter loop");
    kapp->enter_loop();
    qDebug("----<<<<<< left loop");
}

KMozillaPart::~KMozillaPart()
{
    delete m_partProcess;
}

void KMozillaPart::createActions( const QCString &xmlActions )
{
    XPartHost_KPart::createActions( xmlActions );
    qDebug("----<<<<<< exit loop");
    kapp->exit_loop();
}

KAboutData *KMozillaPart::createAboutData()
{
    return new KAboutData( "kmozilla", "kmozilla", "0.1" );
}

#include "kmozillapart.moc"
