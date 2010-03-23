#ifndef _kmozillapart_h_
#define _kmozillapart_h_

#include "xparthost_kpart.h"

class KAboutData;
class KProcess;

class KMozillaPart : public XPartHost_KPart
{
    Q_OBJECT

public:
    KMozillaPart(QWidget *parentWidget, const char *widgetName,
	         QObject *parent, const char *name, const QStringList &);
    virtual ~KMozillaPart();

    virtual void createActions( const QCString &xmlActions );

    static KAboutData *createAboutData();

private:
    KProcess *m_partProcess;
};

#endif

