/*!
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2006 - 2009
 * Thomas Moenicke <tm at php-qt.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QString>
#include <QtCore/QMetaMethod>
#include <QtCore/QHash>
#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QDebug>
#include <QByteArray>

#include "phpqt_internals.h"
#include "php_qt.h"
#include "context.h"

#include "smokephp.h"
#include "VirtualMethodCall.h"
#include "InvokeSlot.h"
#include "pDebug.h"

#define ALLOCA_N(type,n) (type*) alloca(sizeof(type)*(n))

extern zend_class_entry* qstring_ce;
extern zend_class_entry* qobject_ce;
extern QHash<const void*, smokephp_object*> SmokeQtObjects;
extern "C" void init_qt_Smoke();

/**
 * Binding class that handles virtual calls and deletion of objects
 */
class PHPQtSmokeBinding : public SmokeBinding
{
public:
    PHPQtSmokeBinding(Smoke *s) : SmokeBinding(s) {}

    /**
     * called by destructors in shell classes of smoke, e.g. from within
     * ~x_QByteArray(), ~QMetaObject(), ~QObject(), ~x_QModelIndex(), ~x_QTextStream(),~x_QVariant(),
     * ~x_QDomDocument(), ~x_QDomElement(), ~x_QIODevice()
     * @param classId
     * @param ptr
     */
    void deleted( Smoke::Index classId, void* ptr ) {
        pDebug( PHPQt::Destruct ) << "deleting p" << ptr;
        if( PHPQt::SmokePHPObjectExists(ptr) ) {
            smokephp_object *o = (smokephp_object*) PHPQt::getSmokePHPObjectFromQt(ptr);
            if(!o->allocated()) {
                delete static_cast<QObject*> ( ptr );
                delete (o);
            } else {
                o->setPtr(0);
            }
            pDebug( PHPQt::Destruct ) << "p" << ptr << "z" << o->zval_ptr() << "o" << o;
            SmokeQtObjects.remove( o->ptr() );
            o->setAllocated( false );
            pDebug( PHPQt::MapPtr ) << "unmapping" << o->ptr();
            // now o is still mapped to the zval, deleteing it happens at __destruct
    	}
    }

    /**
     * every virtual C++ method call causes a callMethod() to call the PHP method if there is one
     * @param method
     * @param QtPtr
     * @param args
     * @param pureVirtual
     * @return  true if succeeded
     */
    bool callMethod(Smoke::Index method, void* QtPtr, Smoke::Stack args, bool pureVirtual) {

        //! - get a corresponding smokephp_object
        smokephp_object *o = (smokephp_object*) PHPQt::getSmokePHPObjectFromQt(QtPtr);

        //! - return false if there is no related smokephp_object
        if(!o)
            return false;

        QByteArray methodName( smoke->methodNames[smoke->methods[method].name] );

        //! - in case of a metaObject() call:
        //! set the MetaObject created in getMoc() and return true respectivly false if there is one or not
        if( methodName == "metaObject" ){
            if( o->meta() ) {
                args[0].s_class = const_cast<QMetaObject*>( o->meta() );
                return true;
            } else
                return false;
        }

        //! - in case of a qt_metacall(): call PHPQt::qt_metacall()
        if( methodName == "qt_metacall" )
            return PHPQt::qt_metacall( o, args );

        //! - check if method is implemented in PHP and call it
        //! @see PHPQt::methodExists()
        //! @see VirtualMethodCall
        if( PHPQt::methodExists( o->ce_ptr(), methodName.constData() ) ) {
            Context::setCallType( Context::VirtualMethodCall );
            pDebug( PHPQt::VirtualMethod ) << methodName << "with" << smoke->methods[method].numArgs << "arguments";
            zval** zmem = (zval**) safe_emalloc( smoke->methods[method].numArgs, sizeof(zval*), 0 );

            // ALLOC_INIT_ZVAL allocates memory using emalloc and
            // initialized the zval to type IS_NULL
            for( int i=0; i<smoke->methods[method].numArgs; i++ ) {
                ALLOC_INIT_ZVAL( zmem[i] );
            }
//          zval* zmem = ALLOCA_N(zval, smoke->methods[method].numArgs);
            VirtualMethodCall c(smoke, method, args, const_cast<zval*>( o->zval_ptr() ), zmem);
            c.next();
            efree(zmem);
            return true;
        }

        //! - throw an error for pure virtual functions
        if( pureVirtual ) {
            pError() << "pure virtual method " << methodName << " is not implemented. You need to implement it in PHP in order to get this class working.";
        }
        return false;
    }

    virtual char *className(Smoke::Index classId) {
        // return a new[] copy of the language-specific name of this Smoke class
        // poorly designed function, but oh well. Sorry.

        const char *className = smoke->className(classId);
        char *buf = new char[strlen(className) + 1];
        strcpy(buf, className);
        return buf;
    }

    virtual ~PHPQtSmokeBinding() {}
};


bool SmokeType::operator ==(const SmokeType &b) const
{
    const SmokeType &a = *this;
    if(a.name() == b.name()) return true;
    if(a.name() && b.name() && qstrcmp(a.name(), b.name()) == 0)
        return true;
    return false;
}

bool SmokeClass::operator ==(const SmokeClass &b) const
{
    const SmokeClass &a = *this;
    if(a.className() == b.className()) return true;
    if(a.className() && b.className() && qstrcmp(a.className(), b.className()) == 0)
        return true;
    return false;
}

extern Smoke* qt_Smoke;
extern SmokeBinding* qt_binding;

void PHPQt::init()
{
    if (qt_Smoke != 0L)
        php_error(E_ERROR,"could not initialize smoke");

    init_qt_Smoke();

    if(PHPQt::smoke()->numClasses <= 0)
        php_error(E_ERROR,"could not initialize smoke (no class definitions)");

    qt_binding = new PHPQtSmokeBinding( PHPQt::smoke() );
}
