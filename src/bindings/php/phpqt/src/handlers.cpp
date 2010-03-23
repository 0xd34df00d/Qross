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

#include <QtCore/QHash>
#include <QtGui/QWidget>
#include <QtCore/qprocess.h>
#include <QtCore/qtextcodec.h>

//#include "smoke.h"
#include "marshall.h"
#include "php_qt.h"
#include <php_ini.h>
#include "phpqt_internals.h"
#include "smokephp.h"

extern zend_class_entry* qstring_ce;

bool
matches_arg(Smoke *smoke, Smoke::Index meth, Smoke::Index argidx, const char *argtype)
{
	const Smoke::Index *arg = smoke->argumentList + smoke->methods[meth].args + argidx;
	SmokeType type = SmokeType(smoke, *arg);
	if (type.name() && qstrcmp(type.name(), argtype) == 0) {
		return true;
	}
	return false;
}

void*
construct_copy(smokephp_object *o)
{
    const char *className;
    if(o->classId() > 0)
    {
        className = o->smoke()->className( o->classId() );
    } else {
        // must be a qstring
        return o->mPtr();
    }

    int classNameLen = strlen(className);

    char *ccSig = new char[classNameLen + 2];       // copy constructor signature
    strcpy(ccSig, className);
    strcat(ccSig, "#");
    const Smoke::ModuleIndex ccId = o->smoke()->idMethodName( ccSig );
    delete[] ccSig;
    char *ccArg = new char[classNameLen + 8];
    sprintf(ccArg, "const %s&", className);

    const Smoke::ModuleIndex classIdx(o->smoke(), o->classId());

    Smoke::ModuleIndex ccMeth = o->smoke()->findMethod( classIdx, ccId );

    if( !ccMeth.index ) {
        delete[] ccArg;
        return 0;
    }

    Smoke::Index method = o->smoke()->methodMaps[ ccMeth.index ].method;
    if(method > 0)
    {
        // Make sure it's a copy constructor
        if(!matches_arg(o->smoke(), method, 0, ccArg)) {
            delete[] ccArg;
            return 0;
        }
        delete[] ccArg;
        ccMeth.index = method;
    } else {
        // ambiguous method, pick the copy constructor
        Smoke::Index i = -method;
        while(o->smoke()->ambiguousMethodList[i]) {
            if(matches_arg(o->smoke(), o->smoke()->ambiguousMethodList[i], 0, ccArg))
                break;
            i++;
        }
        delete[] ccArg;
        ccMeth.index = o->smoke()->ambiguousMethodList[i];
        if( !ccMeth.index )
        {
            return 0;
        }
    }

    // Okay, ccMeth is the copy constructor. Time to call it.
    Smoke::StackItem args[2];
    args[0].s_class = 0;
    args[1].s_class = o->mPtr();
    Smoke::ClassFn fn = o->smoke()->classes[o->classId()].classFn;
    (*fn)( o->smoke()->methods[ ccMeth.index ].method, 0, args );
    return args[0].s_class;
}


#include "marshall_basetypes.h"
template <class T>
static void marshall_it(Marshall *m)
{
	switch(m->action()) {
		case Marshall::FromZVAL:
			marshall_from_php<T>(m);
		break;

		case Marshall::ToZVAL:
			marshall_to_php<T>( m );
		break;

		default:
			m->unsupported();
		break;
	}
}

void
marshall_basetype(Marshall *m)
{
	switch(m->type().elem()) {

		case Smoke::t_bool:
			marshall_it<bool>(m);
		break;
		case Smoke::t_char:
			marshall_it<signed char>(m);
		break;
		case Smoke::t_uchar:
			marshall_it<unsigned char>(m);
		break;
		case Smoke::t_short:
			marshall_it<short>(m);
		break;

		case Smoke::t_ushort:
			marshall_it<unsigned short>(m);
		break;

		case Smoke::t_int:
			marshall_it<int>(m);
		break;

		case Smoke::t_uint:
			marshall_it<unsigned int>(m);
		break;

		case Smoke::t_long:
			marshall_it<long>(m);
		break;

		case Smoke::t_ulong:
			marshall_it<unsigned long>(m);
		break;

		case Smoke::t_float:
			marshall_it<float>(m);
		break;

		case Smoke::t_double:
			marshall_it<double>(m);
		break;

		case Smoke::t_enum:
			marshall_it<SmokeEnumWrapper>(m);
		break;

		case Smoke::t_class:
			marshall_it<SmokeClassWrapper>(m);
		break;

		default:
			m->unsupported();
		break;
	}

}

static void marshall_void(Marshall * /*m*/) {}
static void marshall_unknown(Marshall *m) {
    m->unsupported();
}

static void marshall_charPP(Marshall *m)
{
    switch( m->action() )
    {
        case Marshall::FromZVAL:
        {
            zval* arglist = m->var();
            if( arglist == NULL || arglist->type != IS_ARRAY || zend_hash_num_elements( arglist->value.ht ) == 0 )
            {
                m->item().s_voidp = 0;
                break;
            }
            const int argc = zend_hash_num_elements( arglist->value.ht );
            char** argv = new char* [ argc + 1 ];
            HashTable *ht = arglist->value.ht;
            long i = 0;
            for( zend_hash_internal_pointer_reset( ht ); zend_hash_has_more_elements( ht ) == SUCCESS; zend_hash_move_forward( ht ) )
            {
                zval** value, tmpcopy;
                if( zend_hash_get_current_data( ht, (void**) &value ) == FAILURE )
                {
                    qDebug() << "invalid list element in argv/char**";
                    continue;
                }
                tmpcopy = **value;
                zval_copy_ctor( &tmpcopy );
                convert_to_string( &tmpcopy );
                argv[ i ] = new char[ Z_STRLEN(tmpcopy) + 1 ];
                strcpy( argv[ i ], Z_STRVAL(tmpcopy) );
                zval_dtor( &tmpcopy );
                i++;
            }
            argv[ i ] = 0;
            m->item().s_voidp = argv;
            m->next();
            break;
        }
    }
}

static void marshall_charP(Marshall *m) {
  marshall_it<char *>(m);
}

void marshall_ucharP(Marshall *m) {
  marshall_it<unsigned char *>(m);
}

static const char * KCODE = 0;
static QTextCodec *codec = 0;

void
init_codec() {

	KCODE = INI_ORIG_STR("qt.codec");

	if (qstrcmp(KCODE, "EUC") == 0) {
		codec = QTextCodec::codecForName("eucJP");
	} else if (qstrcmp(KCODE, "SJIS") == 0) {
		codec = QTextCodec::codecForName("Shift-JIS");
	} else if ((qstrcmp(KCODE, "UTF8") != 0) && (qstrcmp(KCODE,"Latin1") != 0)) {
	    php_error(E_WARNING, "unknown text codec, set to local8Bit");
	    KCODE="";
	}
}


QString*
qstringFromZString(zval* zstring) {
	if (KCODE == 0) {
		init_codec();
	}
	if (qstrcmp(KCODE, "UTF8") == 0)
		return new QString(QString::fromUtf8(zstring->value.str.val, zstring->value.str.len));
	else if (qstrcmp(KCODE, "EUC") == 0)
		return new QString(codec->toUnicode(zstring->value.str.val));
	else if (qstrcmp(KCODE, "SJIS") == 0)
		return new QString(codec->toUnicode(zstring->value.str.val));
	else if(qstrcmp(KCODE, "Latin1") == 0)
		return new QString(QString::fromLatin1(zstring->value.str.val));

	return new QString(QString::fromLocal8Bit(zstring->value.str.val, zstring->value.str.len));
}

zval*
zstringFromQString(QString * s) {

	if (KCODE == 0) {
		init_codec();
	}
	zval* return_value = (zval*) emalloc(sizeof(zval));
	if (qstrcmp(KCODE, "UTF8") == 0) {
		ZVAL_STRING(return_value, (char*) s->toUtf8().constData(), /* duplicate */ 1);
	} else if (qstrcmp(KCODE, "EUC") == 0) {
		ZVAL_STRING(return_value, (char*) codec->fromUnicode(*s).constData(), /* duplicate */ 1);
	} else if (qstrcmp(KCODE, "SJIS") == 0) {
		ZVAL_STRING(return_value, (char*) codec->fromUnicode(*s).constData(), /* duplicate */ 1);
	} else if (qstrcmp(KCODE, "Latin1") == 0) {
		ZVAL_STRING(return_value, (char*) s->toLatin1().constData(), /* duplicate */ 1);
	} else {
		ZVAL_STRING(return_value, (char*) s->toUtf8().constData(), /* duplicate */ 1);
	}
	return return_value;
}


static void marshall_QString(Marshall *m) {

	switch(m->action()) {
		case Marshall::FromZVAL:
		{
			if(Z_TYPE_P(m->var()) != IS_STRING){ // is object
			    m->item().s_voidp = PHPQt::getQtObjectFromZval(m->var());
			    m->next();
			    break;
			}

			QString* s = 0;
			if( m->var() != Qnil) {
				s = qstringFromZString(m->var());
			} else {
				s = new QString();
			}

			m->item().s_voidp = s;
			m->next();

			if (!m->type().isConst() && m->var() != Qnil && s != 0 && !s->isNull()) {
				m->var()->value.str.len = 0;
				zval* temp = zstringFromQString(s);
				ZVAL_STRING(m->var(), temp->value.str.val, 1);
			}

			if (s != 0 && m->cleanup()) {
				delete s;
			}
		}
		break;

		case Marshall::ToZVAL:
		{
			QString* s = static_cast<QString*>(m->item().s_voidp);
			PHPQt::createObject(m->var(), (void*) s, qstring_ce, -1);
		}
		break;

		default:
			m->unsupported();
		break;

   }
}

static void marshall_IntR(Marshall *m)
{

    switch( m->action() )
    {
    case Marshall::FromZVAL:
    {
        m->item().s_voidp = &( Z_LVAL_P( m->var() ) );
	m->var()->refcount__GC = 100;
        break;
    }
    case Marshall::ToZVAL:
    {
        // TODO test me
        int *ip = (int*) m->item().s_voidp;
        m->var()->value.lval = *ip;
    }
    }
}

static void marshall_QStringList(Marshall* m)
{
    switch( m->action() )
    {
    case Marshall::FromZVAL:
    {
        QStringList* stringList = new QStringList;
        zval* list = m->var();
        char* assocKey;
        ulong numKey;
        if ( list->type != IS_ARRAY ) {
            m->item().s_voidp = 0;
            break;
        }
        HashTable* list_hash = HASH_OF( list );
        zval **list_iterator;
        zend_hash_internal_pointer_reset( list_hash );
        while( zend_hash_has_more_elements( list_hash ) == SUCCESS )
        {
            zend_hash_get_current_key( list_hash, &assocKey, &numKey, 0 );
            zend_hash_get_current_data( list_hash, (void**) &list_iterator );
            if( (*list_iterator)->type == IS_STRING )
                stringList->append( Z_STRVAL_PP( list_iterator ) );
            else if ( (*list_iterator)->type == IS_OBJECT ) {
                smokephp_object* o = PHPQt::getSmokePHPObjectFromZval( (*list_iterator) );
                if( o && o->classId() == QSTRING_CLASSID )
                {
                    QString* s = reinterpret_cast< QString*> ( o->mPtr() );
                    stringList->append( *s );
                } else {
                    pNotice() << "unsupported class " << o->ce_ptr()->name << "in QStringList";
                }
            }
            zend_hash_move_forward( list_hash );
        }

        m->item().s_voidp = stringList;
        m->next();

        // it might be changed if not const
        if ( stringList != 0 && !m->type().isConst() ) {
            array_init( list );
            for(QStringList::Iterator it = stringList->begin(); it != stringList->end(); ++it)
                add_next_index_string( list , (*it).toLatin1().data(), 0 );
        }
        if (m->cleanup()) {
            delete stringList;
        }
        break;
    }
    case Marshall::ToZVAL:
    {
        QStringList *stringlist = static_cast<QStringList *>( m->item().s_voidp );
        if ( !stringlist ) {
            *(m->var()) = *Qnil;
            break;
        }
        // TODO linking QStringList
        zval* av;
        MAKE_STD_ZVAL( av );
        array_init( av );
        for (QStringList::Iterator it = stringlist->begin(); it != stringlist->end(); ++it) {
            add_next_index_string( av, estrdup( (*it).toAscii().data() ), 0 );
        }

        *(m->var()) = *av;
        if (m->cleanup()) {
            delete stringlist;
        }
    }
    break;
    default:
        m->unsupported();
        break;
    }
}

TypeHandler Qt_handlers[] = {
    { "WId", marshall_it<WId> },
    { "Q_PID", marshall_it<Q_PID> },
    { "QString", marshall_QString },
    { "QString&", marshall_QString },
    { "QString*", marshall_QString },
    { "int&", marshall_IntR },
    { "char**", marshall_charPP },
    { "char*", marshall_charP },
    { "qint64", marshall_it<long long> },
    { "qint64&", marshall_it<long long> },
    { "QStringList", marshall_QStringList },
    { "QStringList*", marshall_QStringList },
    { "QStringList&", marshall_QStringList },
    { 0, 0 }
};

QHash<QByteArray, TypeHandler*> type_handlers;

void install_handlers(TypeHandler *h) {
	while(h->name) {
		type_handlers.insert(h->name, h);
		h++;
	}
}

Marshall::HandlerFn getMarshallFn(const SmokeType &type) {
	if(type.elem())
		return marshall_basetype;
	if(!type.name())
		return marshall_void;

	TypeHandler *h = type_handlers[type.name()];

	if(h == 0 && type.isConst() && strlen(type.name()) > strlen("const ")) {
			h = type_handlers[type.name() + strlen("const ")];
	}

	if(h != 0) {
		return h->fn;
	}

	return marshall_unknown;
}
