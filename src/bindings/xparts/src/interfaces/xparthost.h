#ifndef __xkparts_parthost_h__
#define __xkparts_parthost_h__

#include <dcopobject.h>
#include <dcopref.h>

class XPartHost : public DCOPObject
{
    K_DCOP
public:
    XPartHost(QCString name) : DCOPObject(name) {}
    
k_dcop:

    /** The XPart should register itself to its host when it is created */
    virtual DCOPRef registerXPart( const DCOPRef &part ) = 0;

    /** Returns the registered part */
    virtual DCOPRef part() = 0;

    /** The XPart informs its host about its available actions.
     * the actions are sent to the XPart using XPart::activateAction */
    virtual ASYNC createActions( const QCString &xmlActions ) = 0;

    /** DCOP signal emitted by the XPart and received here, to be 
     * forwarded to the KPartHost. See KParts documentation for
     * more details. */
    virtual ASYNC setWindowCaption( const QString &caption ) = 0;

    /** DCOP signal emitted by the XPart and received here, to be 
     * forwarded to the KPartHost. See KParts documentation for
     * more details. */
    virtual ASYNC setStatusBarText( const QString &text ) = 0;


    /** DCOP signal emitted by the XPart and received here, to be 
     * forwarded to the KPartHost. See KParts documentation for
     * more details. */
    virtual ASYNC started() = 0;

    /** DCOP signal emitted by the XPart and received here, to be 
     * forwarded to the KPartHost. See KParts documentation for
     * more details. */
    virtual ASYNC completed() = 0;

    /** DCOP signal emitted by the XPart and received here, to be 
     * forwarded to the KPartHost. See KParts documentation for
     * more details. */
    virtual ASYNC canceled( const QString &errMsg ) = 0;

};

#endif
