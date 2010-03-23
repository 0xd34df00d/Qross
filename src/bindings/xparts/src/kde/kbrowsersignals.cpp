#include "kbrowsersignals.h"
#include "xparthost_kpart.h"
#include "xbrowserextension_stub.h"
#include <kurl.h>

KBrowserSignals::KBrowserSignals( XPartHost_KPart *_part, DCOPRef extension )
    : KParts::BrowserExtension( _part )
{
    qDebug("KBrowserSignals constructor");
    part = _part;
    ext = new XBrowserExtension_stub( extension.app(), extension.object() );
    ext->setBrowserSignals( DCOPRef( this ) );
}

KBrowserSignals::~KBrowserSignals()
{
    delete ext;
}

void KBrowserSignals::openURLRequest( const QCString &url)
{
    KURL u = QString(url);
    emit KParts::BrowserExtension::openURLRequest(u);
}

void KBrowserSignals::createNewWindow( const QCString &url )
{
}

#include "kbrowsersignals.moc"

