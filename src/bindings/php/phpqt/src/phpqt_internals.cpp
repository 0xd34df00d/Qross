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

//#include "config.h"

#include <QtCore/QMetaMethod>
#include <QtCore/QHash>
#include <QRegExp>
#include <QDebug>

#include "phpqt_internals.h"
#include "zphp/functions.h"
#include "InvokeSlot.h"
#include "smoke.h"
#include "php_qt.h"
#include "pDebug.h"
#include "context.h"
#include "smokephp.h"

extern zend_object_handlers php_qt_handler;
extern zend_class_entry* qstring_ce;
extern Smoke::Index cachedQObjectSmokeId;

zend_class_entry* qobject_ce;
QHash<const void*, smokephp_object*> SmokeQtObjects;
QHash<const zend_object_handle, smokephp_object*> obj_x_smokephp;

#define ALLOCA_N(type,n) (type*)alloca(sizeof(type)*(n))

// time critical
zval* PHPQt::callPHPMethod(const zval* z_this_ptr, const char* methodName, const zend_uint param_count, zval** args)
{
    if(z_this_ptr == NULL){
        pError() << "could not call PHP method: no related PHP object found.";
    }

    zval *function_name;
    MAKE_STD_ZVAL(function_name);
    ZVAL_STRING(function_name,const_cast<char*>(methodName),1);

    zval* retval;
    ALLOC_INIT_ZVAL( retval );


    if(call_user_function( CG(function_table), const_cast<zval**>(&z_this_ptr), function_name, retval, param_count, args TSRMLS_CC ) == FAILURE){
        smokephp_object* o = PHPQt::getSmokePHPObjectFromZval(z_this_ptr);
        pError() << "could not call method " << o->ce_ptr()->name << "::" << methodName << "(...)";
    }

    // make sure we return the right object
    if(PHPQt::SmokePHPObjectExists(retval)){
        smokephp_object* o = PHPQt::getSmokePHPObjectFromZval(retval);
        retval = const_cast<zval*>(o->zval_ptr());
    }

    efree( function_name );
    return retval;
}

// time critical
bool PHPQt::methodExists(const zend_class_entry* ce_ptr, const char* methodname)
{
    if(ce_ptr == NULL)
        pError() << "no class entry, could not check for message " << methodname;

    char* lcname = zend_str_tolower_dup(methodname, strlen(methodname));

    if(zend_hash_exists(const_cast<HashTable*>(&ce_ptr->function_table), lcname, strlen(methodname)+1)){
        return true;
    }

    efree(lcname);
    return false;
}

/**
 * writes metaObject data as moc would do it in moc_foo.cpp files
 * example: "QWidget\0\0value\0test(int)\0"
 * @param z_this_ptr
 * @param classname
 * @param superdata
 * @param meta_stringdata
 * @param signature
 * @return false if no custom signals and slots are defined in the PHP class
 */

static bool getMocData(zval* z_this_ptr, const char* classname, const QMetaObject* superdata, QString* meta_stringdata, uint* signature)
{
    /*
    // - reads all methods defined in a class
    // - see zend_compile.h for types
    // - case sensitive
    // - types need to be matched

    zend_class_entry* ce_ = Z_OBJCE_P(this_ptr);
    HashTable* function_table = &Z_OBJCE_P(this_ptr)->function_table;
    zend_hash_internal_pointer_reset(function_table);
    zval** prop;
    union _zend_function *fbc;

    if (zend_hash_num_elements( function_table ) > 0) {
        while(zend_hash_has_more_elements(function_table) == SUCCESS)
        {
        zend_hash_get_current_data(function_table,(void**)&fbc);
            zend_hash_move_forward(function_table);
            QByteArray name( (*fbc).common.function_name );
            if( !name.contains("__destruct") &&
                !name.contains("__construct") &&
                !name.contains("__toString") &&
                !name.contains("proxyMethod") &&
                !name.contains("staticProxyMethod") &&
                !name.contains("emit")
            ){
                for( int i=0; i<(*fbc).common.num_args; i++)
                {
                    qDebug() <<"++ "<< (*fbc).common.arg_info[i].name <<","<< (*fbc).common.arg_info[i].array_type_hint;
                }
                qDebug()  << (*fbc).common.function_name;// << fbc->internal_function->function_name;
            }
        }
    }
     */

    /// - readout the slots table
    zval **slotdata;
    zval *zslot;
    zslot = zend_read_property(Z_OBJCE_P(z_this_ptr),z_this_ptr,"slots",5,1);

    zval *zsignal;
    zsignal = zend_read_property(Z_OBJCE_P(z_this_ptr),z_this_ptr,"signals",7,1);

    if((zslot)->type==IS_ARRAY && (zsignal)->type==IS_ARRAY )
    {
        HashTable* slots_hash = HASH_OF(zslot);
        HashTable* signals_hash = HASH_OF(zsignal);

        char* assocKey;
        ulong numKey;
        int signaturecount = 2 + strlen(classname);

#ifdef MOC_DEBUG
        QString qr;
        pDebug( PHPQt::Moc ) << "+== begin metaobject dump ==+\n";
        pDebug( PHPQt::Moc ) << "\t" << classname << "\n\t1 0 0 0 " << zend_hash_num_elements(slots_hash)+zend_hash_num_elements(signals_hash) << " 10 0 0 0 0" << endl << endl;
#endif

        /// - write class signature
        signature[0] = 1;
        signature[4] = zend_hash_num_elements(slots_hash)+zend_hash_num_elements(signals_hash);
        signature[5] = 10;

        /// - write classname
        meta_stringdata->append(classname);
        meta_stringdata->append(QChar::Null);
        meta_stringdata->append(QChar::Null);

        int i = 10;
        zend_hash_internal_pointer_reset(signals_hash);
        while(zend_hash_has_more_elements(signals_hash) == SUCCESS)
        {
            /// - read slot from hashtable
            zend_hash_get_current_key(signals_hash,&assocKey,&numKey,0);
            zend_hash_get_current_data(signals_hash,(void**)&slotdata);
#ifdef MOC_DEBUG
            qr.append(Z_STRVAL_PP(slotdata));
            qr.append(" ");
            pDebug( PHPQt::Moc ) << "\t" << signaturecount << "8 8 8 0x05 ::s" << endl;
#endif

            meta_stringdata->append(Z_STRVAL_PP(slotdata));
            meta_stringdata->append(QChar::Null);

            zend_hash_move_forward(signals_hash);

            /// - write signal signature
            signature[i++] = signaturecount;
            signature[i++] = 8;
            signature[i++] = 8;
            signature[i++] = 8;
            signature[i++] = 0x05;

            signaturecount += strlen(Z_STRVAL_PP(slotdata)) + 1;
        }

        zend_hash_internal_pointer_reset(slots_hash);

        while(zend_hash_has_more_elements(slots_hash) == SUCCESS)
        {
            /// - read slot from hashtable
            zend_hash_get_current_key(slots_hash,&assocKey,&numKey,0);
            zend_hash_get_current_data(slots_hash,(void**)&slotdata);

#ifdef MOC_DEBUG
            qr.append(Z_STRVAL_PP(slotdata));
            qr.append(" ");
            pDebug( PHPQt::Moc ) << "\t" << signaturecount << "8 8 8 0x0a ::s" << endl;
#endif
            meta_stringdata->append(Z_STRVAL_PP(slotdata));
            meta_stringdata->append(QChar::Null);

            zend_hash_move_forward(slots_hash);

            /// - write slot signature
            signature[i++] = signaturecount;
            signature[i++] = 8;
            signature[i++] = 8;
            signature[i++] = 8;
            signature[i++] = 0x0a;

            signaturecount += strlen(Z_STRVAL_PP(slotdata)) + 1;
        }
        // TODO freeing this crashs
        //     efree( assocKey );
#ifdef MOC_DEBUG
        pDebug( PHPQt::Moc ) << qr << endl;
#endif
        pDebug( PHPQt::Moc ) << "+== end metaobject dump ==+" << endl;
        return true;
    } else {
        return false;
    }
} // getMocData

void PHPQt::createMetaObject(smokephp_object* o, zval* this_ptr)
{
    const Smoke::ModuleIndex nameId = o->smoke()->idMethodName("metaObject");
    const Smoke::ModuleIndex classIdx(o->smoke(), o->classId());
    const Smoke::ModuleIndex meth = o->smoke()->findMethod( classIdx, nameId );
    const Smoke::Method &methodId = o->smoke()->methods[ o->smoke()->methodMaps[ meth.index ].method ];
    const Smoke::ClassFn fn = o->smoke()->classes[methodId.classId].classFn;
    Smoke::StackItem i[1];
    //! - call QObject::metaObject()
    (*fn)( methodId.method, const_cast<void*>(o->ptr()), i );

    //! - get the superdata metaobject
    const QMetaObject *superdata = static_cast<QMetaObject *> ( i[0].s_voidp );

    QString phpqt_meta_stringdata;
    uint* phpqt_meta_data = new uint[20*5+10];

    //! - if the PHP class has signals and slots defined: create data as moc would do, if not use superdata
    if( getMocData( this_ptr, o->parent_ce_ptr()->name, superdata, &phpqt_meta_stringdata, phpqt_meta_data ) ) {
        const char* phpqt_meta_stringdata_ = estrndup(phpqt_meta_stringdata.toAscii(), phpqt_meta_stringdata.size());
        //  QByteArray* phpqt_meta_stringdata_ = new QByteArray( phpqt_meta_stringdata.toAscii() );

        QMetaObject ob = { { superdata, phpqt_meta_stringdata_, phpqt_meta_data, 0 } };
        QMetaObject* m = new QMetaObject;
        memcpy(m, &ob, sizeof(ob));
        o->setMetaObject(m);
    } else {
        o->setMetaObject(superdata);
    }
}

// time critical
bool PHPQt::qt_metacall(smokephp_object* o, Smoke::Stack args)
{
    Context::setCallType( Context::SlotCall );
    const QMetaObject* staticMetaObject = o->meta();
    const int _id = args[2].s_int;
    const int offset = staticMetaObject->methodOffset();

    const QByteArray signature( staticMetaObject->method(_id).signature() );
    const QByteArray metaMethodName = signature.left( signature.indexOf("(") );

    //! - if we have a slot overridden in php user space: call it
    //!   @see InvokeSlot
    if( PHPQt::methodExists( o->ce_ptr() , metaMethodName.constData()) ) {
        pDebug( PHPQt::Slot ) << " userspace " << signature << o->ce_ptr()->name;
        const int count = staticMetaObject->method( args[2].s_int ).parameterTypes().count() + 1;
        // zval* zmem = ALLOCA_N(zval, count);
        zval** zmem = (zval**) safe_emalloc( sizeof(zval*), count+1, 0);
        for( int i=0;i<count;i++ )
        {
            ALLOC_INIT_ZVAL( zmem[i] );
        }

        // NOTICE is memory allocation safe here?
        InvokeSlot c( o->smoke(), args, o->zval_ptr(), zmem, _id, staticMetaObject, (void**) args[3].s_voidp, metaMethodName );
        c.next();

        efree(zmem);
        return true;

    } else {
        if ( staticMetaObject->indexOfSlot( signature ) != -1 )
        {
            pDebug( PHPQt::Slot ) << " C++ " << signature;
            // return false means this will be done by smoke
            return false;
        } else {
            // TODO error case for undefined methods, see php_qt proxyMethod
            //			const int i = staticMetaObject->indexOfSignal( signature );
            //			const int offset = staticMetaObject->methodOffset(); // The offset is the summary of all methods in the class's superclasses
            pDebug( PHPQt::Signal ) << signature << staticMetaObject->className() << _id << staticMetaObject->methodOffset();

            /* C++ */	//if( _id < offset ) { qWarning() << "got an id smaller than offset"; }

            /**
            * We go through QMetaObject::activate, because it can either be connected to a C++ Slot or a user space Slot
            * cast to a QObject using smoke cast
            * */
            QObject* ptr = (QObject*) o->smoke()->cast( const_cast<void*>( o->ptr() ), o->classId(), cachedQObjectSmokeId );
            void *_b[] = { 0, ((void**) args[3].s_voidp)[1] };
            QMetaObject::activate( ptr, staticMetaObject, 0, _b );
            return true; // success
        }
    } // else method exist
    return false;
}

// time critical
extern Smoke::Index cachedQObjectSmokeId;
bool PHPQt::isQObject(const Smoke::Index classId)
{
    if( classId == cachedQObjectSmokeId )
        return true;

    const Smoke* smoke = PHPQt::smoke();
    for(Smoke::Index *p = smoke->inheritanceList + smoke->classes[classId].parents; *p; p++)
    {
        if( PHPQt::isQObject(*p) )
            return true;
    }
    return false;
}

// time critical
void PHPQt::prepareMethodName(zval** args, const int argc)
{
    for(int i=0; i<argc; i++){
        const uint type = static_cast<int>( (*args[i]).type );
        switch( type )
        {
        case IS_RESOURCE:
            // TODO add resource type
            break;
        case IS_ARRAY:
            Context::methodName()->append("?");
            break;
        case IS_BOOL:
        case IS_LONG:
        case IS_DOUBLE:
        case IS_STRING:
            Context::methodName()->append("$");
            break;
        case IS_NULL:
            // nothing to do
            break;
        case IS_OBJECT:
            // as default QString is not supported in Smoke
            if( !strcmp( Z_OBJCE_P(args[i])->name, "QString" ) ){
                Context::methodName()->append("$");
            } else {
                Context::methodName()->append("#");
            }
            break;
        default:
            php_error(E_ERROR,"Unknown argument or unsupported type %d at argument %d, cannot prepare method call %s()\n", type, i, Context::methodName()->constData());
            //          exit(FAILURE);
            break;
        }
    }
}

// time critical
QByteArray PHPQt::getSignature(const int argc, zval **argv, MocArgument* mocStack)
{
    mocStack[0].argType = xmoc_bool;    // the return type
    mocStack[0].st = SmokeType( PHPQt::smoke(), PHPQt::smoke()->idType("bool") );

    QByteArray signature( "(" );

    for(int i=0; i<argc; i++) {

        const uint type = static_cast< int >( argv[i]->type );
        mocStack[ i+1 ].st = SmokeType( PHPQt::smoke(), 0 );

        switch( type )
        {
        case IS_RESOURCE:
            // @TODO add resource type
            break;

        case IS_ARRAY:
            // @TODO xmoc_ptr,
            php_error( E_WARNING, "Array given as signal argument" );
            break;

        case IS_BOOL:
            mocStack[i+1].argType = xmoc_bool;
            mocStack[i+1].st = SmokeType( PHPQt::smoke(), PHPQt::smoke()->idType("bool") );
            signature.append( "bool" );
            break;

        case IS_LONG:
            mocStack[i+1].argType = xmoc_int;
            mocStack[i+1].st = SmokeType( PHPQt::smoke(), PHPQt::smoke()->idType("int") );
            signature.append( "int" );
            break;

        case IS_DOUBLE:
            mocStack[i+1].argType = xmoc_double;
            mocStack[i+1].st = SmokeType( PHPQt::smoke(), PHPQt::smoke()->idType("double") );
            signature.append( "double" );
            break;

        case IS_STRING:
            mocStack[i+1].argType = xmoc_charstar;
            mocStack[i+1].st = SmokeType( PHPQt::smoke(), PHPQt::smoke()->idType("char*") );
            signature.append( "string" );
            break;

        case IS_OBJECT:
            if(Z_OBJCE_P( argv[i] ) == qstring_ce)
                mocStack[i+1].argType = xmoc_QString;
            else {
                smokephp_object *o = PHPQt::getSmokePHPObjectFromZval( argv[i] );
                mocStack[i+1].st = SmokeType( PHPQt::smoke(), o->classId() );
                mocStack[i+1].argType = xmoc_void;
            }
            signature.append( "object" );

        default:
            php_error( E_ERROR,"Unknown argument or unsupported argument type %d, type %d, exit\n", i, type );
            exit(FAILURE);
            break;
        } // switch
    }

    signature.append( ")" );
    return signature;
}

// time critical
SmokeBinding *qt_binding;
Smoke::Index PHPQt::findMethod( const char* className, const char* methodName, const int argc, zval** args )
{
    Smoke::ModuleIndex method = PHPQt::smoke()->findMethod(className, methodName); // qt_Smoke->methods
    Smoke::Index i = PHPQt::smoke()->methodMaps[ method.index ].method;

    if(i <= 0)
    {
        i = -i;     // turn into ambiguousMethodList index
        while( PHPQt::smoke()->ambiguousMethodList[i] ) {

            Smoke::Method &methodRef = PHPQt::smoke()->methods[ PHPQt::smoke()->ambiguousMethodList[i] ];

            if ( (methodRef.flags & Smoke::mf_internal) == 0 ) {
                // try to compare smoke types with the php ones
                bool right = false;
                for( int k = 0; k < argc; k++ ) {
                    uint type = static_cast<uint>( (*args[k]).type );
                    switch( (PHPQt::smoke()->types[
                                PHPQt::smoke()->argumentList[
                                                  PHPQt::smoke()->methods[
                                                           PHPQt::smoke()->ambiguousMethodList[i]].args+k]].flags & Smoke::tf_elem) )
                    {
                    case Smoke::t_voidp:
                        if(type == IS_ARRAY)
                            right = true;
                        if(type == IS_STRING)
                            right = true;
                        break;
                    case Smoke::t_bool:
                        if(type == IS_BOOL)
                            right = true;
                        break;
                    case Smoke::t_char:
                    case Smoke::t_uchar:
                    case Smoke::t_short:
                    case Smoke::t_ushort:
                    case Smoke::t_int:
                    case Smoke::t_uint:
                    case Smoke::t_long:
                    case Smoke::t_ulong:
                        if(type == IS_LONG)
                            right = true;
                        break;
                    case Smoke::t_float:
                    case Smoke::t_double:
                        if(type == IS_DOUBLE)
                            right = true;
                        break;
                    case Smoke::t_enum:
                        // TODO implement enum types
                        break;
                    case Smoke::t_class:
                        if(type == IS_OBJECT){
                            QByteArray name(
                                        PHPQt::smoke()->types[
                                                           PHPQt::smoke()->argumentList[
                                                                                     PHPQt::smoke()->methods[
                                                                                                          PHPQt::smoke()->ambiguousMethodList[i]].args+k]].name);
                            name.replace("const ","");
                            name.replace("*","");
                            name.replace("&","");

                            if( name == Z_OBJCE_P( args[k] )->name )
                                right = true;
                        }
                        break;
                    default:
                        php_error(E_ERROR, "unknown argument type");
                        break;
                    }
                }
                if(right){
#ifdef DEBUG
                    php_error(E_NOTICE, "Ambiguous Method %s::%s => %d, %d", className, methodName, PHPQt::smoke()->ambiguousMethodList[i], i);
#endif
                    return PHPQt::smoke()->ambiguousMethodList[i];
                }
            }
            i++;
        }
    }
    return i;
}

void PHPQt::callCppMethod(void *obj, const Smoke::Index method, Smoke::Stack qargs)
{
    const Smoke::Method *m = PHPQt::smoke()->methods + method;
    const Smoke::ClassFn fn = PHPQt::smoke()->classes[m->classId].classFn;
    fn(m->method, obj, qargs);
}

extern Smoke* qt_Smoke;
QList<MocArgument*> PHPQt::QtToMoc( Smoke* smoke, void** a, const QList<QByteArray> methodTypes )
{
    static QRegExp * rx = 0;
    if( rx == 0 )
        rx = new QRegExp("^(bool|int|uint|long|ulong|double|char\\*|QString)&?$");

    QList<MocArgument*> result;

    foreach( QByteArray typeName, methodTypes )
    {
        MocArgument* arg = new MocArgument;
        Smoke::Index typeId = 0;

        if( typeName.isEmpty() ) {
            arg->argType = xmoc_void;
            result.append( arg );
        } else {
            typeName.replace( "const ", "" );
            QString staticType = ( rx->indexIn(typeName) != -1 ? rx->cap(1) : "ptr" );
            if ( staticType == "ptr" ) {
                arg->argType = xmoc_ptr;
                QByteArray targetType = typeName;
                typeId = smoke->idType(targetType.constData());
                if (typeId == 0 && !typeName.contains('*')) {
                    if (!typeName.contains("&")) {
                        targetType += "&";
                    }
                    typeId = smoke->idType(targetType.constData());
                }
            } else if ( staticType == "bool" ) {
                arg->argType = xmoc_bool;
            } else if ( staticType == "int" ) {
                arg->argType = xmoc_int;
            } else if ( staticType == "uint" ) {
                arg->argType = xmoc_uint;
            } else if ( staticType == "long" ) {
                arg->argType = xmoc_long;
            } else if ( staticType == "ulong" ) {
                arg->argType = xmoc_ulong;
            } else if ( staticType == "double" ) {
                arg->argType = xmoc_double;
            } else if ( staticType == "char*" ) {
                arg->argType = xmoc_charstar;
            } else if ( staticType == "QString" ) {
                arg->argType = xmoc_QString;
                typeName += "*";
            }
            typeId = smoke->idType( typeName.constData() );
            smoke = qt_Smoke;
            if( typeId == 0 ) {
                pNotice() << "Cannot handle " << typeName << " as slot argument";
                return result;
            }
            arg->st.set( smoke, typeId );
            result.append( arg );
        }

#ifdef THOMAS_MAYBE_TO_BE_REMOVED
    {
        smokephp_object *o = PHPQt::getSmokePHPObjectFromQt(a[i]);
        mocStack[i].st = SmokeType(PHPQt::smoke(),o->classId());
        mocStack[i].argType = xmoc_void;
    }
#endif

    }
    return result;
}

Smoke* PHPQt::smoke(){ return qt_Smoke; }

extern SmokeBinding* qt_binding;
SmokeBinding* PHPQt::binding(){ return qt_binding; }

const char* PHPQt::findRealMethodName(const char* methodName)
{
    if(!methodName) return "";
    QString _m(methodName);
    // TODO it is slow but safe
    for(Index i=0; i < PHPQt::smoke()->numMethodNames; i++){
        if(_m.compare(PHPQt::smoke()->methodNames[i], Qt::CaseInsensitive) == 0){ return PHPQt::smoke()->methodNames[i]; }
    }
    qFatal("PQ::findRealMethodName(): could not find %s", methodName);
}

const char* PHPQt::checkForOperator(const char* fname){
    return fname;
}

// mapping

void* PHPQt::getQtObjectFromZval( const zval* this_ptr )
{
    if(this_ptr == NULL)
        pError( PHPQt::MapPtr ) << "php object does not exists, Qt object could not be fetched, " << Z_OBJCE_P( const_cast<zval*>(this_ptr) )->name;
    return getSmokePHPObjectFromZval( this_ptr )->mPtr();
}

smokephp_object* PHPQt::getSmokePHPObjectFromZval(const zval* this_ptr)
{
    if(this_ptr == NULL)
        pError( PHPQt::MapPtr ) << "php object does not exists, smokephp_object could not be fetched, " << Z_OBJCE_P( const_cast<zval*>(this_ptr) )->name;
    return obj_x_smokephp.value(this_ptr->value.obj.handle);
}

smokephp_object* PHPQt::getSmokePHPObjectFromQt(const void* QtPtr)
{
    return SmokeQtObjects.value( QtPtr );
}

void PHPQt::setSmokePHPObject(smokephp_object* o)
{
    pDebug( PHPQt::MapPtr ) << "  mapping" << o->ptr() << " o: " << o;
    SmokeQtObjects.insert( o->ptr(), o );
}

bool PHPQt::SmokePHPObjectExists(const zval* this_ptr)
{
    if( this_ptr->type != IS_OBJECT )
        return false;
    return obj_x_smokephp.contains(this_ptr->value.obj.handle);
}

bool PHPQt::SmokePHPObjectExists(const void* ptr)
{
    return (SmokeQtObjects.find(ptr) != SmokeQtObjects.end());
}

bool PHPQt::unmapSmokePHPObject(const zval* zvalue)
{
    pDebug( PHPQt::MapHandle ) << "unmapping" << zvalue->value.obj.handle << PHPQt::getSmokePHPObjectFromZval( zvalue ) << "( zval " << zvalue << ")";
    return obj_x_smokephp.remove( zvalue->value.obj.handle );
}

bool PHPQt::unmapSmokePHPObject(smokephp_object* o)
{
    pDebug( PHPQt::MapPtr ) << "unmapping" << o->ptr() << " o: " << o;
    return SmokeQtObjects.remove( o->ptr() );
}

void PHPQt::mapSmokePHPObject( const zend_object_handle handle, smokephp_object* o )
{
    pDebug( PHPQt::MapHandle ) << "  mapping" << handle << o;
    obj_x_smokephp.insert( handle, o );
}

// object creation

smokephp_object* PHPQt::createObject(zval* zval_ptr, const void* ptr, const zend_class_entry* ce, const Smoke::Index classId)
{
    Q_ASSERT (zval_ptr);
    Q_ASSERT (ptr);

    if(!ce)
        qFatal("no class entry!");

    //! - set class entry for QString if necessary
    if(classId == QSTRING_CLASSID)
        ce = qstring_ce;
    else if (classId == 0)
    {
        qDebug("\nno class id");
        check_qobject(zval_ptr);
        qFatal("php object creation failed");
    }

    //! - set zval type, initialize the zval, create mapping object
    Z_TYPE_P(zval_ptr) = IS_OBJECT;
    object_init_ex(zval_ptr, const_cast<zend_class_entry*>(ce));
    smokephp_object* o = new smokephp_object(PHPQt::smoke(), classId, ptr, ce, zval_ptr);

    //! - set php_qt method handlers
    Z_OBJ_HT_P(zval_ptr) = &php_qt_handler;
    //! - set mapping
    setSmokePHPObject(o);
    PHPQt::mapSmokePHPObject( zval_ptr->value.obj.handle, o );

    //! - increase refcounter
    zval_add_ref(&zval_ptr);
    return o;
}

extern zend_class_entry* php_qt_generic_class;

smokephp_object* PHPQt::cloneObject(zval* zval_ptr, smokephp_object* so, const void* copyPtr)
{
    Q_ASSERT (zval_ptr);
    Q_ASSERT (copyPtr);

    smokephp_object* o = new smokephp_object(PHPQt::smoke(), so->classId(), copyPtr, so->ce_ptr(), zval_ptr);
    Z_OBJ_HT_P(zval_ptr) = &php_qt_handler;
    setSmokePHPObject(o);

    // TODO
    //	o->setAllocated( true );
    //	obj_x_smokephp.insert(zval_ptr->value.obj.handle, o);
    PHPQt::mapSmokePHPObject( zval_ptr->value.obj.handle, o );

    return o;
}

smokephp_object* PHPQt::createOriginal(zval* zval_ptr, void* ptr)
{
    smokephp_object* o = getSmokePHPObjectFromQt(ptr);
    zval_ptr = const_cast<zval*>(o->zval_ptr());
    zval_add_ref(&zval_ptr);
    return o;
}

void PHPQt::restoreObject( smokephp_object* o )
{
    //! - check if the C++ side is on the heap or stack, if stack then set refcount to something like 1,
    //! - example: QVariant
    zval* z = (zval*) emalloc( sizeof(zval) );
    z->type = IS_OBJECT;
    z->refcount__GC = 3;
    z->is_ref__GC = 0;
    z->value.obj.handle = o->zval_ptr()->value.obj.handle;
    Z_OBJ_HT_P( z ) = &php_qt_handler;
    o->setZvalPtr( z );
}

// debugging

void PHPQt::check_qobject(zval* zobject)
{
#ifdef PHP_DEBUG
    if(!PHPQt::SmokePHPObjectExists(zobject)) {

        qDebug() << "PHP Object \n(" << endl;

        qDebug() << "\t       zval => " << zobject << endl;
        if(Z_TYPE_P(zobject) == IS_OBJECT)
            qDebug() << "\tclass entry => " << Z_OBJCE_P(zobject)->name << endl;
        qDebug() << "\t  ref count => " << zobject->refcount__GC << endl;
        qDebug() << "\t     is_ref => " << (int) zobject->is_ref__GC << endl;
        qDebug() << "\t       type => " << printType(Z_TYPE_P(zobject)) << endl;

        if(Z_TYPE_P(zobject) == IS_OBJECT)
        {
            qDebug() <<"\t obj-handle => " << zobject->value.obj.handle << endl;
        }

        qDebug() << ")" << endl;

    } else {

        smokephp_object* o = PHPQt::getSmokePHPObjectFromZval(zobject);

        qDebug() << "PHP-Qt object \n(" << endl;

        qDebug() << "\t       zval => " << zobject << endl;
        // 		qDebug() << "\tclass entry => " << Z_OBJCE_P(zobject)->name << endl;
        qDebug() << "\tclass entry => " << o->ce_ptr()->name << endl;
        qDebug() << "\t  ref count => " << zobject->refcount__GC << endl;
        qDebug() << "\t     is_ref => " << (int) zobject->is_ref__GC      << endl;
        qDebug() << "\t       type => " << printType(Z_TYPE_P(zobject)) << endl;

        if(Z_TYPE_P(zobject) == 5)
        {
            qDebug() <<"\t obj-handle => " << zobject->value.obj.handle << endl;
        }

        qDebug() << endl;

        qDebug() << "\t      smokeobj => " << o << endl;
        qDebug() << "\t         Smoke => " << o->smoke() << endl;
        qDebug() << "\t       classId => " << o->classId() << endl;
        qDebug() << "\t        Qt ptr => " << o->ptr() << endl;
        qDebug() << "\t        ce_ptr => " << o->ce_ptr() << endl;
        qDebug() << "\t      zval_ptr => " << o->zval_ptr() << endl;
        qDebug() << "\t  QMetaObject* => " << o->meta() << endl;

        qDebug() << ")" << endl;
    }
#endif
}

const QString PHPQt::printType(int type)
{
    switch(type){
    case IS_NULL:	return "NULL"; break; // 0
    case IS_LONG:	return "long"; break; // 1
    case IS_DOUBLE: return "double"; break;	//2
    case IS_BOOL: return "bool"; break; //	3
    case IS_ARRAY: return "array"; break; // 4
    case IS_OBJECT: return "object"; break; //	5
    case IS_STRING: return "string"; break; // 6
    case IS_RESOURCE: return "resource"; break; // 7
    case IS_CONSTANT: return "constant"; break; // 8
    case IS_CONSTANT_ARRAY: return "const array"; break; //	9
    }
    return "unknown";
}

#ifdef THOMAS_TEMP_DISABLED
// TODO temp. disabled code, TODO
/*!
 *
 * data types
 * #define IS_NULL      0
 * #define IS_LONG      1
 * #define IS_DOUBLE    2
 * #define IS_BOOL      3
 * #define IS_ARRAY     4
 * #define IS_OBJECT    5
 * #define IS_STRING    6
 * #define IS_RESOURCE  7
 * #define IS_CONSTANT  8
 * #define IS_CONSTANT_ARRAY    9
 *
 *  @param  zval***                 args
 *  @param  int                     argc
 *  @param  Smoke::StackItem*       qargs
 */

static inline int treatArray(zval **val, const int num_args, va_list args, zend_hash_key *hash_key)
{
    const uint type = va_arg(args, uint);
    int e_arrayc = va_arg(args, int);
    void** e_arrayv = va_arg(args, void**);
    smokephp_object *o;
    if(type == IS_OBJECT)
        o = PHPQt::getSmokePHPObjectFromZval(((zval*) *val));

    switch(type){
    case IS_STRING:
        e_arrayv[e_arrayc] = /*new char[Z_STRLEN(**val)+1]; */
            emalloc(Z_STRLEN(**val)+1);
        e_arrayv[e_arrayc++] = reinterpret_cast<void*>( Z_STRVAL(**val) );
        break;
    case IS_LONG:
        e_arrayv[e_arrayc] = emalloc(sizeof(long));
        e_arrayv[e_arrayc++] = reinterpret_cast<void*>( Z_LVAL_PP(val) );
        break;
    case IS_DOUBLE:
        e_arrayv[e_arrayc] = emalloc(sizeof(double));
        e_arrayv[e_arrayc++] = reinterpret_cast<void*> (Z_LVAL_PP(val));
        break;
    case IS_BOOL:
        e_arrayv[e_arrayc] = emalloc(sizeof(bool));
        e_arrayv[e_arrayc++] = reinterpret_cast<void*>( Z_BVAL_PP(val) );
        break;
    case IS_OBJECT:
        e_arrayv[e_arrayc] = emalloc(sizeof(o->ptr()));
        e_arrayv[e_arrayc++] = const_cast<void*>(o->ptr());
        break;
    default:
        php_error(E_ERROR, "PHP-Qt: unsupported array type %d", type);
        break;
    }

    return ZEND_HASH_APPLY_KEEP;
}


void* transformArray(const zval* args)
{
    // array information
    int e_arrayc = zend_hash_num_elements( (*args).value.ht );  // length
    // find the first type
    const zval** first_elem;
    if(zend_hash_get_current_data_ex( (*args).value.ht, reinterpret_cast<void**> (&first_elem), 0) == FAILURE){
        php_error(E_ERROR, "PHP-Qt: could not get first value of hashtable.");
    }

    const uint type = static_cast<int>( (**first_elem).type );
    if(type < 0 || type > 9){
        // should never happen
        php_error(E_ERROR, "Could not get type of array");
    }
    void* e_arrayv;

    switch(type){
    case IS_STRING:
        e_arrayv = new char*[e_arrayc];//safe_emalloc(e_arrayc, sizeof(char*), 0);
        //      e_arrayv = new char[ e_arrayc ];
        break;
    case IS_LONG:
        e_arrayv = safe_emalloc(e_arrayc, sizeof(long), 0);
        break;
    case IS_DOUBLE:
        e_arrayv = safe_emalloc(e_arrayc, sizeof(double), 0);
        break;
    case IS_BOOL:
        e_arrayv = safe_emalloc(e_arrayc, sizeof(bool), 0);
        break;
    case IS_OBJECT:
        e_arrayv = safe_emalloc(e_arrayc, sizeof(QObject*), 0);
        break;
    default:
        php_error(E_ERROR, "PHP-Qt: unsupported array type %d", type);
    }

    zend_hash_apply_with_arguments( (*args).value.ht, (apply_func_args_t) treatArray , 3, type, e_arrayc, e_arrayv );
    return e_arrayv;
}
#endif

