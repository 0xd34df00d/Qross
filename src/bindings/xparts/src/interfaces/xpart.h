#ifndef __xkparts_part_h__
#define __xkparts_part_h__

#include <dcopobject.h>
#include <dcopref.h>
#include <qglobal.h>

class XPart : public DCOPObject
{
    K_DCOP
k_dcop:

    /** The XPartManager uses the windowId() to embed the part. */
    virtual Q_UINT32 windowId() = 0;

    /** Called when the part should display itself */
    virtual void show() = 0;

    /** sent by the XPartHost to request url opening */
    virtual bool openURL( const QCString& url ) = 0;

    /** sent by the XPartHost to close the url */
    virtual bool closeURL() = 0;

   /** Called when an action (previously registered with 
    *  XPartHost::createActions()) has been activated. Name is the name of the
    * action, state is used with Toggle actions to precise the current state.
    */
    virtual ASYNC activateAction( const QString &name, int state ) = 0;

    /** Are extentions available -> browser extension / TextEditor ? */
    virtual DCOPRef queryExtension( const QCString& extension ) = 0; 
    
};

#endif
