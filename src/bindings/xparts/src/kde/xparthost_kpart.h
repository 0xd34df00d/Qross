#ifndef __xparthost_kpart_h__
#define __xparthost_kpart_h__

#include <xparthost.h>

#include <kparts/part.h>

class XPart_stub;
class KBrowserSignals;
class QXEmbed;


/** 
 * This class is the middle class between the host of the KPart (usually a
 * KParts::MainWindow) and the XPart. It transfer calls from the XPart to the
 * KPartHost host and from the KPartHost to the XPart. 
 *
 * Note : In the XPart white paper, this class is named KXPartHost 
 */
class XPartHost_KPart : public KParts::ReadOnlyPart, public XPartHost
{
    Q_OBJECT
public:
    XPartHost_KPart( QWidget *parentWidget, const char *widgetName,
	             QObject *parent, const char *name );
    virtual ~XPartHost_KPart();

    // DCOP stuff

	/** The XPart uses this function to register itself */
    virtual DCOPRef registerXPart( const DCOPRef &part );

	/** Return the XPart DCOPRef to someone willing to communicate with it */
    virtual DCOPRef part();

    // KPart signals

	/** Emitted by the XPart, to be transfered to the KPart host */
    virtual ASYNC createActions( const QCString &xmlActions );
	/** Emitted by the XPart, to be transfered to the KPart host */
    virtual ASYNC setWindowCaption( const QString &caption );
	/** Emitted by the XPart, to be transfered to the KPart host */
    virtual ASYNC setStatusBarText( const QString &text );

	/** Emitted by the XPart, to be transfered to the KPart host */
    virtual ASYNC started();
	/** Emitted by the XPart, to be transfered to the KPart host */
    virtual ASYNC completed();
	/** Emitted by the XPart, to be transfered to the KPart host */
    virtual ASYNC canceled( const QString &errMsg );

    // reimplemented from KReadOnlyPart
	/** function called by the KPart host to be forwarded to the XPart */
    virtual bool openURL( const KURL &url );
	/** function called by the KPart host to be forwarded to the XPart */
    virtual bool closeURL();

protected:
  virtual bool openFile() { return false; }

private slots:
    void actionActivated();

signals:
    void actionsInitialized();

private:
    DCOPRef m_part;
    XPart_stub *m_stub;
    KBrowserSignals *be;
    QXEmbed *embed;
};

#endif
