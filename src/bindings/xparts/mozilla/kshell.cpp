
#include "xparthost_kpart.h"

#include <dcopclient.h>
#include <dcopobject.h>
#include <kapplication.h>
#include <kstdaction.h>
#include <kaction.h>
#include <kmainwindow.h>
#include <kprocess.h>
#include <kparts/mainwindow.h>
#include <kdebug.h>

class ShellWindow : public KParts::MainWindow
{
    Q_OBJECT

public:
    ShellWindow()
    {
        m_host = new XPartHost_KPart( this, "parthost" );

        setCentralWidget( m_host->widget() );

        connect(m_host, SIGNAL( actionsInitialized() ), this, SLOT( mergeGUI() ) );

#if 1
        m_partProcess = new KProcess;
        *m_partProcess << "./kmozilla"
                       << kapp->dcopClient()->appId() << m_host->objId();
        m_partProcess->start();
#endif

        KStdAction::quit( this, SLOT( close() ), actionCollection() );
        KSelectAction *s = new KSelectAction( "http://www.kde.org" , 0,
                           actionCollection(), "location" );
        connect( s, SIGNAL(activated( const QString& ) ), this, SLOT( slotOpenUrl( const QString & ) ) );
        s->setEditable(true);
    }
    virtual ~ShellWindow()
    {
        delete m_partProcess;
    }
public slots:
    void slotOpenUrl( const QString &url )
    {
        kdDebug() << "this=" << this;
        kdDebug() << "url=" << url << endl;
        m_host->openURL(url.latin1());
    }
    void mergeGUI()
    {
        qDebug("initGUI");
        setXMLFile("/home/lars/kmozilla/kmozilla/parthost.rc");
        createGUI( m_host );
    }

private:
    XPartHost_KPart *m_host;
    KProcess *m_partProcess;
};

int main( int argc, char **argv )
{
    KApplication app( argc, argv, "xkpartsshell" );

    app.dcopClient()->registerAs("kshell");

    ShellWindow *w = new ShellWindow;
    w->resize(500, 500);
    w->show();

    return app.exec();
}

#include "kshell.moc"
