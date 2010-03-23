#ifndef __kbrowsersignals_h__
#define __kbrowsersignals_h__

#include <xbrowsersignals.h>
#include <kparts/browserextension.h>
#include <dcopref.h>

class XBrowserExtension_stub;
class XPartHost_KPart;

class KBrowserSignals : public KParts::BrowserExtension, virtual public XBrowserSignals
{
    Q_OBJECT
public:
    KBrowserSignals( XPartHost_KPart *part, DCOPRef ref );
    virtual ~KBrowserSignals();


    virtual ASYNC openURLRequest( const QCString &url);
    virtual ASYNC createNewWindow( const QCString &url );

protected:
    XPartHost_KPart *part;
    XBrowserExtension_stub *ext;
};

#endif
