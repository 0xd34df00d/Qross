/*!
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2006 - 2009
 * Thomas Moenicke <tm at php-qt.org>
 * Katrina Niolet <katrina at niolet.name>
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

#include <QtCore/QHash>

#include "php_qt.h"
#include "zphp/z_extension.h"
#include <zend_API.h>
#include "context.h"
#include "smokephp.h"
#include "phpqt_internals.h"
#include "pDebug.h"
#include "EmitSignal.h"
#include "MethodCall.h"

#include "zphp/z_handler.h"
#include "ext/standard/info.h"

#include <QStack>

extern "C" void init_qt_Smoke();
extern TypeHandler Qt_handlers[];
void install_handlers(TypeHandler *);
//! object list
static int le_php_qt_hashtype;
//! object handler  * @internal
extern zend_object_handlers php_qt_handler;

// context, threadsafe
QStack<QByteArray*> methodNameStack_;

// cached, readonly
Smoke::Index qbool;
Smoke::Index qstring;
Smoke::Index cachedQObjectSmokeId;
extern zend_class_entry* qobject_ce;
extern zend_class_entry* qstring_ce;

extern void 	_register_QString();

PHP_INI_BEGIN()
    PHP_INI_ENTRY("qt.codec", "UTF8", PHP_INI_ALL, NULL)
PHP_INI_END()

/*! php_qt_functions[]
 *
 * Every user visible function must have an entry in php_qt_functions[].
 */
#undef emit
function_entry php_qt_functions[] = {
	PHP_FE(confirm_php_qt_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(SIGNAL,	NULL)
	PHP_FE(SLOT,	NULL)
	PHP_FE(emit,	NULL)
	PHP_FE(qDebug,	NULL)
	PHP_FE(qWarning,	NULL)
	PHP_FE(qCritical,	NULL)
	PHP_FE(qAbs, 		NULL)
	PHP_FE(qRound,		NULL)
	PHP_FE(qRound64,	NULL)
	PHP_FE(qMin,		NULL)
	PHP_FE(qMax,		NULL)
	PHP_FE(qBound,		NULL)
	PHP_FE(qPrintable,	NULL)
	PHP_FE(qFuzzyCompare,	NULL)
	PHP_FE(qIsNull,		NULL)
	PHP_FE(qIntCast,	NULL)
	PHP_FE(qVersion,	NULL)
	PHP_FE(PHPQtVersion,	NULL)
	PHP_FE(QiDiVersion,	NULL)
	PHP_FE(qSharedBuild,		NULL)
	PHP_FE(qMalloc,		NULL)
	PHP_FE(qFree,		NULL)
	PHP_FE(qRealloc,	NULL)
	PHP_FE(qMemCopy,	NULL)
	PHP_FE(qt_noop,		NULL)
	PHP_FE(qt_assert,	NULL)
	PHP_FE(qt_assert_x,	NULL)
	PHP_FE(Q_ASSERT,	NULL)
	PHP_FE(Q_ASSERT_X,	NULL)
	PHP_FE(qt_check_pointer,	NULL)
	PHP_FE(qobject_cast,	phpqt_cast_arginfo)
	PHP_FE(tr,	NULL)
	PHP_FE(check_qobject,	NULL)
	PHP_FE(Q_UNUSED,	NULL)
	PHP_FE(qstatic_cast,    NULL)
	PHP_FE(__phpqt_unittest_invoke,  NULL)
	{NULL, NULL, NULL}	/* Must be the last line in php_qt_functions[] */
};

/*! php_qt_module_entry
 */
zend_module_entry php_qt_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"php_qt",
	php_qt_functions,
	PHP_MINIT(php_qt),
	PHP_MSHUTDOWN(php_qt),
	PHP_RINIT(php_qt),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(php_qt),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(php_qt),
#if ZEND_MODULE_API_NO >= 20010901
	PHPQT_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHP_QT
ZEND_GET_MODULE(php_qt)
#endif

/**
 *	generic object
 */

static zend_function_entry php_qt_generic_methods[] = {
    ZEND_ME(php_qt_generic_class,__construct,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(php_qt_generic_class,__destruct,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(php_qt_generic_class,__toString,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(php_qt_generic_class,emit,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(php_qt_generic_class,proxyMethod,NULL,ZEND_ACC_PUBLIC)
    ZEND_ME(php_qt_generic_class,staticProxyMethod,NULL,ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
    {NULL,NULL,NULL}
};

    extern "C" {

/* emit does nothing */
ZEND_METHOD(php_qt_generic_class, emit)
{
    Q_UNUSED(return_value_ptr);
    Q_UNUSED(this_ptr);
    Q_UNUSED(return_value_used);
    Q_UNUSED(ht);
    Q_UNUSED(return_value);
}

ZEND_METHOD(php_qt_generic_class, __toString)
{
    Q_UNUSED(return_value_ptr);
    Q_UNUSED(this_ptr);
    Q_UNUSED(return_value_used);
    Q_UNUSED(ht);
    RETURN_STRING("", 1);
}

/*
 * zend engine creates a dummy zval with the correct object handle, we'll take that one
 * when destroying the smokephp_object, we take also care for the corresponding zval* and delete it
 */

ZEND_METHOD(php_qt_generic_class, __destruct)
{
    Q_UNUSED(return_value_ptr);
    Q_UNUSED(return_value_used);
    Q_UNUSED(ht);
    Q_UNUSED(return_value);

    pDebug( PHPQt::Destruct ) << "__destruct handle" << getThis()->value.obj.handle;
    if( getThis()->type == IS_OBJECT )
    {
        if( PHPQt::SmokePHPObjectExists( getThis() ) )
        {
            smokephp_object *o = PHPQt::getSmokePHPObjectFromZval( getThis() );
            pDebug( PHPQt::Destruct ) << "removing" << getThis()->value.obj.handle << o->ce_ptr()->name;
            //! it is not a reference
            if(!PHPQt::unmapSmokePHPObject(getThis()))
                pNotice() << "tried to unmap unregistered php object";

    /*			if( o->allocated() )
            {
                Smoke::Index nameId = o->smoke()->idMethodName("delete");
                Smoke::Index method = o->smoke()->findMethod( o->classId(), nameId );
                Smoke::Method &m = o->smoke()->methods[ o->smoke()->methodMaps[method].method ];
                const Smoke::ClassFn fn = o->smoke()->classes[ m.classId ].classFn;
                Smoke::StackItem stack[1];
                (*fn)( m.method, o->mPtr(), stack );
            }*/
            if ( !PHPQt::unmapSmokePHPObject(o) )
                pNotice() << "tried to unmap unregistered smoke object";
#ifdef TEMP_DISABLED
	    efree( (void*) o->zval_ptr() );
#endif
            delete o;
        }
	} // is object
}

extern "C" ZEND_METHOD(php_qt_generic_class, __construct)
{
    Q_UNUSED(return_value_ptr);
    Q_UNUSED(return_value_used);
    Q_UNUSED(return_value);

    Context::setCallType( Context::ConstructorCall );

    // find parents
    zend_class_entry *ce = Z_OBJCE_P(getThis());
    zend_class_entry *ce_parent = Z_OBJCE_P(getThis());

    while ( PHPQt::smoke()->idClass(ce->name).index <= 0 ) {
        ce = ce->parent; // ce_parent
    }

    // get arguments
    const int argc = ZEND_NUM_ARGS();
    zval **args = (zval **) safe_emalloc(argc, sizeof(zval*), 0);
    if(_zend_get_parameters_array(ht,argc, args) == FAILURE) {
        efree(args);   WRONG_PARAM_COUNT;
    }

    Context::setMethodName( ce->name );
    PHPQt::prepareMethodName( args, argc );	// #, $, ?
    const Smoke::Index method = PHPQt::findMethod( ce->name, Context::methodName()->constData(), ZEND_NUM_ARGS(), args );

    pDebug( PHPQt::Construct ) << Context::methodName()->constData();
    MethodCall c(PHPQt::smoke(), method, getThis(), args, getThis());
    c.next();

    // smokephp_object is created above in c.next()
    smokephp_object* o = PHPQt::getSmokePHPObjectFromZval(getThis());
    o->setParentCePtr(ce_parent); // = ce if no parent
    o->setAllocated( true );

    // Metaobject
    // TODO only if derived
    if( PHPQt::isQObject( PHPQt::smoke()->idClass(ce->name).index ) )
        PHPQt::createMetaObject(o, getThis());

    // cleanup
    efree(args);
    Context::removeMethodName();
    return;
}

extern "C" ZEND_METHOD(php_qt_generic_class, proxyMethod)
{
    Q_UNUSED(return_value_used);

    zend_class_entry *ce;

    Context::setCallType( Context::MethodCall );
    ce = Z_OBJCE_P( getThis() );

    //! - find parent class entries
    while (PHPQt::smoke()->idClass(ce->name).index <= 0) {
        ce = ce->parent;
    }
    //! - get number of arguments and argument list
    const int argc = ZEND_NUM_ARGS();
    zval **args = (zval**) safe_emalloc(argc, sizeof( zval* ), 0);

    if(_zend_get_parameters_array(ht, argc, args) == FAILURE){
        efree(args);
        WRONG_PARAM_COUNT;
    }

    //! - prepare method information
    PHPQt::prepareMethodName(args, argc);
    const Smoke::Index method = PHPQt::findMethod(ce->name, Context::methodName()->constData(), argc, args);

    //! - if method ID is 0 it might be a signal
    if(method <= 0) { // it is a user signal
        if( Context::methodName()->constData() ) {
            // is it a signal?
            if(getThis()){
                smokephp_object* o = PHPQt::getSmokePHPObjectFromZval(getThis());
                if( o && o->meta() != 0){
                    Context::setCallType( Context::SignalCall );
                    const QMetaObject* mo = o->meta();
                    QByteArray signalName( Context::methodName()->constData() );
                    signalName.replace("$","");
                    signalName.replace("#","");
                    signalName.replace("?","");
                    MocArgument *mocStack = new MocArgument[argc+1]; // first entry is return value
                    signalName.append( PHPQt::getSignature( argc, args, mocStack ) );
                    // seems to be a signal
                    // TODO QMultiMap
                    const int index = mo->indexOfSignal( signalName );
                    if( index >= 0 ) {
                        QObject *qobj = static_cast<QObject*> ( o->smoke()->cast(
                                const_cast<void*>(o->ptr()),
                                o->classId(),
                                o->smoke()->idClass("QObject").index
                        ) );
                        pDebug( PHPQt::Signal ) << signalName.constData() << endl;
                        zval* result;
                        EmitSignal signal(qobj, index, argc, mocStack, args, result);
                        signal.next();
                        RETURN_NULL();
                    }
                }
            }

            QString types;
            for( int i = 0; i < argc; i++ )
            {
                types += PHPQt::printType( args[i]->type );
                if(i != argc-1) types.append(',');
            }
            QString methodName( Context::methodName()->constData() );
            methodName.replace( "$", "" );
            methodName.replace( "#", "" );
            php_error(E_ERROR,"Call to undefined method %s::%s() or wrong arguments: %s", ce->name, methodName.toLatin1().constData(), types.toLatin1().constData() );

        }
        else
            php_error(E_ERROR,"Call to undefined method!");
    }

    //! - do the method call @see MethodCall
    //! the return zval will be replaced (calling dtor)
    zval_dtor( return_value );
    pDebug( PHPQt::Method ) << ce->name << "::" << Context::methodName()->constData();
    MethodCall c( PHPQt::smoke(), method, getThis(), args, return_value );
    c.next();

    *return_value_ptr = return_value;

    // cleanup
    efree(args);
    Context::removeMethodName();

    return;
} // proxyMethod

ZEND_METHOD(php_qt_generic_class, staticProxyMethod)
{
    Context::setCallType( Context::StaticMethodCall );

    ALLOC_INIT_ZVAL( this_ptr );
    object_init_ex( this_ptr, Context::activeCe() );
    Context::removeActiveCe();

    // forward to proxyMethod
    zim_php_qt_generic_class_proxyMethod(ht, return_value, return_value_ptr, this_ptr, return_value_used);
    Context::setCallType( Context::MethodCall );
}

/*!
 * list destructor for le_php_qt_hashtype
 * @param rsrc
 */
static void destroyHashtable(zend_rsrc_list_entry *rsrc)
{
    pDebug( PHPQt::NoLevel ) << "Hashtable destroyed. Shutdown PHP-Qt.";
}

/*!
 *  entry function called when the module is loaded into the zend engine
 */

PHP_MINIT_FUNCTION(php_qt)
{
    Q_UNUSED(type);
    Context::createContext();

    //! - register php.ini entries
    REGISTER_INI_ENTRIES();
    //! - init codec
    init_codec();
    //! - install Qt specific handlers
    install_handlers(Qt_handlers);
    //! - set object list
    le_php_qt_hashtype = zend_register_list_destructors_ex( destroyHashtable, NULL, "PHP-Qt object list", module_number);
    //! - install overridden handlers
    ZProxyHandlers::installProxyHandlers();
    PHPQt::init();

    //! - cache class entries for multiple inheritance
    QHash<const char*, zend_class_entry*> tmpCeTable;

    //! loop for all classes to create and register class entries
    for(Smoke::Index i = 1; i <= PHPQt::smoke()->numClasses; i++)
    {
        zend_function_entry* t = static_cast<zend_function_entry*>( safe_emalloc(7, sizeof(zend_function_entry), 0) );
        zend_function_entry* p = t;

        // register
        PHP_QT_ME( php_qt_generic_class, __construct,		phpqt_cast_arginfo, ZEND_ACC_PUBLIC );
        PHP_QT_ME( php_qt_generic_class, __destruct,		NULL, ZEND_ACC_PUBLIC );
        PHP_QT_ME( php_qt_generic_class, __toString,		NULL, ZEND_ACC_PUBLIC );
        PHP_QT_ME( php_qt_generic_class, emit,				NULL, ZEND_ACC_PUBLIC );
        PHP_QT_ME( php_qt_generic_class, proxyMethod,		phpqt_cast_arginfo, ZEND_ACC_PUBLIC );
        PHP_QT_ME( php_qt_generic_class, staticProxyMethod,	phpqt_cast_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC );
        t->fname = NULL;

        //! - register zend classes
        zend_class_entry ce;
        INIT_CLASS_ENTRY( ce, PHPQt::smoke()->classes[i].className, p );
        ce.name_length = strlen( PHPQt::smoke()->classes[i].className );
        zend_class_entry* ce_ptr = zend_register_internal_class( &ce TSRMLS_CC );
        tmpCeTable[ PHPQt::smoke()->classes[i].className ] = ce_ptr;

        if(cachedQObjectSmokeId == i) // cache
            qobject_ce = ce_ptr;
    } // end loop classes

    //! - do inheritance, all classes must be defined before
    for( Smoke::Index i=1; i < PHPQt::smoke()->numClasses; i++ ) {
        zend_class_entry* ce = tmpCeTable[ PHPQt::smoke()->classes[i].className ];
        for( Smoke::Index *p = PHPQt::smoke()->inheritanceList + PHPQt::smoke()->classes[i].parents; *p; p++ ) {
            if( PHPQt::smoke()->classes[*p].className != 0 ) {
                zend_class_entry *parent_ce = tmpCeTable[PHPQt::smoke()->classes[*p].className];
                zend_do_inheritance(ce, parent_ce TSRMLS_CC);
            }
        }
    }

    //! - cache some stuff
    cachedQObjectSmokeId = PHPQt::smoke()->idClass("QObject").index;
    //! - register QString
    _register_QString();

    return SUCCESS;
} // PHP_MINIT

extern QHash<const zend_object_handle, smokephp_object*> obj_x_smokephp;
extern QHash<const void*, smokephp_object*> SmokeQtObjects;

/* PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(php_qt)
{
    Q_UNUSED(type);
    Q_UNUSED(module_number);
    Context::destroyContext();

    SmokeQtObjects.clear();
    obj_x_smokephp.clear();
    Smoke::classMap.clear();

    return SUCCESS;
}

/*! PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(php_qt)
{
    Q_UNUSED(type);
    Q_UNUSED(module_number);
	return SUCCESS;
}

/*! PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(php_qt)
{
    Q_UNUSED(type);
    Q_UNUSED(module_number);
    return SUCCESS;
}

/*! PHP_MINFO_FUNCTION
 * shows information and php.ini settings on the php info table
 */
PHP_MINFO_FUNCTION(php_qt)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "PHP-Qt support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

} // extern C

