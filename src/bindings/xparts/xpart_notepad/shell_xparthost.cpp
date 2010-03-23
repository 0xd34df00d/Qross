
#include "xparthost_kpart.h"
#include "shell_xparthost.h"

#include <dcopclient.h>
#include <dcopobject.h>
#include <kapplication.h>
#include <kstdaction.h>
#include <kaction.h>
#include <kmainwindow.h>
#include <kprocess.h>
#include <kparts/mainwindow.h>
#include <kdebug.h>

ShellWindow::ShellWindow()
    : KParts::MainWindow()
{
    m_host = new XPartHost_KPart( this, 0, this, "parthost" );

    setCentralWidget( m_host->widget() );

    connect(m_host, SIGNAL( actionsInitialized() ), this, SLOT( mergeGUI() ) );

    // Launch our XPart child.
    m_partProcess = new KProcess;
    *m_partProcess << "./xp_notepad"
                   << kapp->dcopClient()->appId() << m_host->objId();
    m_partProcess->start();

    // Init our Gui
    (void) new KAction( "Hop", 0, this, SLOT(hop()), actionCollection(), "hop" );
    KStdAction::quit( this, SLOT( close() ), actionCollection() );
    KSelectAction *s = new KSelectAction( "http://www.kde.org" , 0,
                                          actionCollection(), "location" );
    connect( s, SIGNAL(activated( const QString& ) ), this, SLOT( slotOpenUrl( const QString & ) ) );
    s->setEditable(true);

    kdDebug() << "KShell window created" << endl;
}

ShellWindow::~ShellWindow()
{
    delete m_partProcess;
}

void ShellWindow::hop()
{
    kdDebug() << "hop called!" << endl;
}

void ShellWindow::slotOpenUrl( const QString &url )
{
    kdDebug() << "this=" << this;
    kdDebug() << "url=" << url << endl;
    m_host->openURL(url.latin1());
}

void ShellWindow::mergeGUI()
{
    qDebug("initGUI");
    setXMLFile("shell_xparthost.rc");
    createGUI( m_host );
    m_host->widget()->setFocus();
    kdDebug() << "focus set to embedded widget" << endl;
}

int main( int argc, char **argv )
{
    KApplication app( argc, argv, "xparthost_shell" );

    app.dcopClient()->registerAs("xparthost_shell");

    ShellWindow *w = new ShellWindow;
    w->resize(500, 500);
    w->show();

    return app.exec();
}

#include "shell_xparthost.moc"
