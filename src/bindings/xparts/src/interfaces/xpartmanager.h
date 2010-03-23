#ifndef __xkparts_partmanager_h__
#define __xkparts_partmanager_h__

#include <dcopobject.h>
#include <qglobal.h>

class XKPartManager : public DCOPObject
{
    K_DCOP

k_dcop:
    /** Query a XPart able to handle a given mimetype */
    virtual DCOPRef createPart( QString servicetype ) = 0;

    /** Delete a previously created XPart */
    virtual void deletePart( DCOPRef ref ) = 0;
};


#endif
