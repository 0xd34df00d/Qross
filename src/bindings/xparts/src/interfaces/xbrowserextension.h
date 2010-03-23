#ifndef __xpart_browser_h__
#define __xpart_browser_h__

#include <dcopref.h>

class XBrowserExtension : public DCOPObject
{
    K_DCOP
    
k_dcop:
    virtual void setBrowserSignals( const DCOPRef &ref) = 0;

    virtual QByteArray saveState() = 0;
    virtual void restoreState( QByteArray state ) = 0;
};

#endif
