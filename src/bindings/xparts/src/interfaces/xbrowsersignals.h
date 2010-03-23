#ifndef __xpart_browsersignals_h__
#define __xpart_browsersignals_h__

#include <dcopobject.h>

class XBrowserSignals : public DCOPObject
{
    K_DCOP
    
k_dcop:
    virtual ASYNC openURLRequest( const QCString &url) = 0;
    virtual ASYNC createNewWindow( const QCString &url ) = 0;
};

#endif
