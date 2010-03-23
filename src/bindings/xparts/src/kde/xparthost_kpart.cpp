#include "xparthost_kpart.h"
#include "kbrowsersignals.h"
#include "xpart_stub.h"

#include <dcopclient.h>
#include <kapplication.h>

#include <assert.h>

#include <qxembed.h>

#include <qdom.h>
#include <kaction.h>

#include <kdebug.h>

XPartHost_KPart::XPartHost_KPart( QWidget *parentWidget, const char *widgetName, 
	                          QObject *parent, const char *name )
    : KParts::ReadOnlyPart( parent, name ),
      XPartHost("parthost")
{
    m_stub = 0;
    be = 0;
    embed = new QXEmbed(parentWidget, widgetName);
    setWidget(embed);
}

XPartHost_KPart::~XPartHost_KPart()
{
    delete m_stub;
}

DCOPRef XPartHost_KPart::part()
{
    return m_part;
}

DCOPRef XPartHost_KPart::registerXPart( const DCOPRef &part )
{
    m_part = part;

    assert( m_stub == 0 );

    m_stub = new XPart_stub( part.app(), part.object() );

    kdDebug() << "embedding window " << m_stub->windowId() << endl;
    embed->embed( static_cast<WId>( m_stub->windowId() ) );

    m_stub->show();
    embed->show();
     DCOPRef ref = m_stub->queryExtension("browserextension");
     if( !ref.isNull() ) {
	 qDebug(" found browser extension ");
	 be = new KBrowserSignals( this, ref );
     }
    return DCOPRef( kapp->dcopClient()->appId(), objId() );
}


void XPartHost_KPart::createActions( const QCString &xmlActions )
{
    qDebug("--> createActions");
    // creates a set of actions and adds them to the actionCollection
    QDomDocument d;
    d.setContent( xmlActions );

    QDomElement docElem = d.documentElement();

    kdDebug() << "docElement is " << docElem.tagName() << endl;

    QDomNode n = docElem.firstChild();
    while( !n.isNull() ) {
        QDomElement e = n.toElement();
        if( !e.isNull() ) {
            if ( e.tagName() == "Action") {
                QString name = e.attribute("name");
                QString type = e.attribute("type");

                if(type.isEmpty())
                    new KAction( name, 0, this, SLOT( actionActivated() ), actionCollection(), name.latin1() );
                else if( type == "toggle" )
                    new KToggleAction( name, 0, this, SLOT( actionActivated() ), actionCollection(), name.latin1() );
                kdDebug() << "action=" << name << "  type=" << type << endl;
            } else if ( e.tagName() == "XMLFile" ) {
                QString location = e.attribute("location");
                setXMLFile(location);
            }
        }
        n = n.nextSibling();
    }
    emit actionsInitialized();
}


void XPartHost_KPart::setWindowCaption( const QString &caption )
{
    emit KParts::ReadOnlyPart::setWindowCaption( caption );
}

void XPartHost_KPart::setStatusBarText( const QString &text )
{
    emit KParts::ReadOnlyPart::setStatusBarText( text );
}

void XPartHost_KPart::started()
{
    emit KParts::ReadOnlyPart::started( 0 );
}

void XPartHost_KPart::completed()
{
    emit KParts::ReadOnlyPart::completed();
}

void XPartHost_KPart::canceled( const QString &errMsg )
{
    emit KParts::ReadOnlyPart::canceled( errMsg );
}

bool XPartHost_KPart::openURL( const KURL &url )
{
    qDebug("XPartHost_KPart::openUrl()");
    return m_stub->openURL( url.url().latin1() );
}

bool XPartHost_KPart::closeURL()
{
    return m_stub->closeURL();
}


void XPartHost_KPart::actionActivated()
{
    const QObject *o = sender();

    if( !o->inherits("KAction") ) return;

    const KAction *action = static_cast<const KAction *>(o);
    QString name = action->text();
    int state = 0;

    if(action->inherits("KToggleAction")) {
        const KToggleAction *t = static_cast<const KToggleAction *>(action);
        state = t->isChecked();
    }

    m_stub->activateAction(name, state);
}

#include "xparthost_kpart.moc"
