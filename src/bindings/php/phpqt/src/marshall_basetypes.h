/*!
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2006 - 2009
 * Thomas Moenicke <tm at php-qt.org>
 *
 * Derived from the QtRuby and PerlQt sources, see AUTHORS for details
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

#include "marshall_types.h"
#include "pDebug.h"
#include "context.h"
#include "config.h"

template <class T> T* smoke_ptr(Marshall *m) { return (T*) m->item().s_voidp; }

template<> bool* smoke_ptr<bool>(Marshall *m) { return &m->item().s_bool; }
template<> signed char* smoke_ptr<signed char>(Marshall *m) { return &m->item().s_char; }
template<> unsigned char* smoke_ptr<unsigned char>(Marshall *m) { return &m->item().s_uchar; }
template<> short* smoke_ptr<short>(Marshall *m) { return &m->item().s_short; }
template<> unsigned short* smoke_ptr<unsigned short>(Marshall *m) { return &m->item().s_ushort; }
template<> int* smoke_ptr<int>(Marshall *m) { return &m->item().s_int; }
template<> unsigned int* smoke_ptr<unsigned int>(Marshall *m) { return &m->item().s_uint; }
template<> long* smoke_ptr<long>(Marshall *m) { 	return &m->item().s_long; }
template<> unsigned long* smoke_ptr<unsigned long>(Marshall *m) { return &m->item().s_ulong; }
template<> float* smoke_ptr<float>(Marshall *m) { return &m->item().s_float; }
template<> double* smoke_ptr<double>(Marshall *m) { return &m->item().s_double; }
template<> void* smoke_ptr<void>(Marshall *m) { return m->item().s_voidp; }

template <class T> T php_to_primitive(zval*);
template <class T> zval* primitive_to_php(T, zval* return_value);

template <class T>
void marshall_from_php(Marshall *m)
{
	zval* zobj = m->var();
	(*smoke_ptr<T>(m)) = php_to_primitive<T>(zobj);
}

template <class T>
void marshall_to_php(Marshall *m)
{
//	if( m->doAlloc() ) {
//	}
	primitive_to_php<T>( *smoke_ptr<T>(m) , m->var() );
}

#include "marshall_primitives.h"
//#include "marshall_complex.h"

// Special case marshallers

template <>
void marshall_from_php<char *>(Marshall *m)
{
	zval* zobj = m->var();
	m->item().s_voidp = php_to_primitive<char*>(zobj);
}

template <>
void marshall_from_php<SmokeEnumWrapper>(Marshall *m)
{
	zval* v = m->var();

	if (Z_TYPE_P(v) == IS_OBJECT) {
	// A Qt::Enum is a subclass of Qt::Integer, so 'get_qinteger()' can be called ok
	} else {
		m->item().s_enum = Z_LVAL_P(v);
	}
}

// TODO check for more types than int
template <>
void marshall_to_php<SmokeEnumWrapper>(Marshall *m)
{
	zval* z = (zval*) emalloc( sizeof(zval) );
	ZVAL_LONG( z, m->item().s_enum );
	*(m->var()) = *z;
}

// m = MethodCall
template <>
void marshall_from_php<SmokeClassWrapper>(Marshall *m)
{
	zval* zval_ptr = m->var();

	if(zval_ptr == 0) {
	    m->item().s_class = 0;
	    return;
	}

	if(zval_ptr->type == IS_NULL)
	{
	    m->item().s_class = 0;
	    return;
	}
// TODO check if object

	if(zval_ptr->type != IS_OBJECT)
		php_error(E_ERROR, "Invalid type, expecting PHP object for %s\n", m->type().name());

	if(!PHPQt::SmokePHPObjectExists(zval_ptr)) {
		PHPQt::check_qobject(zval_ptr);
// 		php_error(E_ERROR, "Invalid type, expecting %s, %s given (probably PHP-Qt lost the Qt object)\n", m->type().name(), Z_OBJCE_P(zval_ptr)->name);
		php_error(E_ERROR, "Invalid type, expecting %s (probably PHP-Qt lost the Qt object)\n", m->type().name());
		return;
	}

	smokephp_object *o = PHPQt::getSmokePHPObjectFromZval(zval_ptr);

	if(!o || !o->ptr()) {
		if(m->type().isRef()) {
			php_error(E_WARNING, "References can't be nil\n");
			m->unsupported();
		}

		m->item().s_class = 0;
		return;
	}

	void *ptr = o->mPtr();

//	if((!m->cleanup() && m->type().isStack())) {
	if(m->type().isRef()){
		ptr = construct_copy(o);
//#ifdef DEBUG
//			php_error(E_WARNING, "copying %s %p to %p\n", resolve_classname(o->smoke(), o->classId(), o->ptr(), o->ptr(), ptr);
#//endif
	}

	const Smoke::Class &cl = m->smoke()->classes[m->type().classId()];

	ptr = o->smoke()->cast(
		ptr,				// pointer
		o->classId(),			// from
		o->smoke()->idClass(cl.className).index	// to
		);

	m->item().s_class = ptr;

	// remove everything in case it is a stack type
	if( m->type().isStack() )
	{
		pDebug( PHPQt::MapHandle ) << "deleting stack item" << o->ce_ptr()->name;
		PHPQt::unmapSmokePHPObject( m->var() );
		PHPQt::unmapSmokePHPObject( o );
		delete o;
		m->var()->refcount__GC = 0;
	}
	return;
}

/* Happens at method calls: VirtualMethodCall
 *
 */
extern zend_object_handlers php_qt_handler;
extern Smoke::Index cachedQObjectSmokeId;

template <> void marshall_to_php<SmokeClassWrapper>(Marshall *m)
{
    if( m->item().s_class == 0 ) {
        qWarning("Qt Object does not exist!");
        ZVAL_NULL(m->var());
        return;
    }

    void* voidPtr = m->item().s_class;

    // if ptr is already mapped to a php handle, create a new zval using that handle and set it as m->var()
    if( PHPQt::SmokePHPObjectExists( voidPtr ) )
    {
        smokephp_object* o = PHPQt::getSmokePHPObjectFromQt( voidPtr );

        pDebug( PHPQt::MapPtr ) << "found invalid mapped zval" << o->zval_ptr() << o->ce_ptr()->name << " probably freed. Creating new zval, using handle " << o->handle() << " mapped onto " << m->var();

        // remap zval - smokephp_object
        //    	PHPQt::unmapSmokePHPObject( o );

        m->var()->value.obj.handle = o->handle();
        m->var()->value.obj.handlers = &php_qt_handler;
        m->var()->type = IS_OBJECT;
        m->var()->refcount__GC = 2;
        m->var()->is_ref__GC = 0;

        o->setZvalPtr( m->var() );
        //    	PHPQt::setSmokePHPObject( o );

        return;
    }

    // create a new PHP object (return_value):
    QByteArray className( m->smoke()->classes[ m->type().classId() ].className );
    zend_class_entry *_ce;

    if ( m->var() && Z_TYPE_P(m->var()) == IS_OBJECT )
    {
        _ce = Z_OBJCE_P(m->var());
    } /*else if( className == "QObject" ) {

        //! cast from QObject to class type
        voidPtr = m->smoke()->cast( voidPtr, cachedQObjectSmokeId, m->type().classId() );

        //! cast the php one
        QObject* qObject = reinterpret_cast< QObject* > ( voidPtr );
        _ce = zend_fetch_class(
                const_cast< char* > ( qObject->metaObject()->className() ),
                strlen( qObject->metaObject()->className() ),
                ZEND_FETCH_CLASS_AUTO TSRMLS_DC);

    }*/ else //! fallback, already with correct type
        _ce = zend_fetch_class( className.data(), className.size(), ZEND_FETCH_CLASS_AUTO TSRMLS_DC );


    smokephp_object *o = PHPQt::createObject( m->var(), voidPtr, _ce, m->type().classId() );

    if(m->type().isConst() && m->type().isRef() && Context::callType() == Context::ConstructorCall ) // TODO check copy constructor
        //if( m->type().isRef() )
    {
        voidPtr = construct_copy( o );
        if( voidPtr ) {
            pDebug() << "copying " << o->ce_ptr()->name << o->ptr() << "to" << voidPtr;
            o->setPtr( voidPtr );
            o->setAllocated( true );
        } else
            pError() << "copy constructor failed";
    }

    pDebug( PHPQt::MapPtr ) << "allocating" << className << "p" << o->ptr() << "zv" << static_cast<void*> (m->var()) << "h" << m->var()->value.obj.handle;

    if( m->type().isStack() )
        o->setAllocated(true);

    if( Context::callType() == Context::VirtualMethodCall )
        m->var()->refcount__GC = 1;

} // marshall_to_php

template <>
void marshall_to_php<char *>(Marshall *m)
{
	char *sv = (char*)m->item().s_voidp;
	zval* zobj;
	if(sv) {
	    ZVAL_STRING(zobj,sv,/*duplicate*/ 1);
	} else {
	    zobj = Qnil;
	}
	if(m->cleanup())
		delete[] sv;

	*(m->var()) = *zobj;
// 	m->setRetval(zobj);
}

template <>
void marshall_to_php<unsigned char *>(Marshall *m)
{
	m->unsupported();
}

template <>
void marshall_from_php<long long>(Marshall *m)
{
	zval* zobj = m->var();
	m->item().s_voidp = reinterpret_cast< void* >( php_to_primitive< long >( zobj ) );
}

template <>
void marshall_to_php<long long>(Marshall *m)
{
	const long long i = reinterpret_cast< long long > ( m->item().s_voidp );
	zval* zobj = m->var();
	if( i < LONG_MAX ) {
		ZVAL_LONG( zobj, (long) i );
	} else {
		ZVAL_LONG( zobj, LONG_MAX );
	}
}
