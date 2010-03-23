/**
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

#include <QString>
#include <QHash>
#include "php_qt.h"
#include "MethodCall.h"
#include "MethodReturnValue.h"
#include "phpqt_internals.h"
#include "marshall_types.h"
#include "context.h"
#include "pDebug.h"

MethodCall::MethodCall(Smoke *smoke, const Smoke::Index method, zval* target, zval **sp, zval *&retval) :
    MethodCallBase(smoke,method,sp),
    _target(target),
    _o(0),
    _retval(retval),
    _staticCall( false )
{
    if (PHPQt::SmokePHPObjectExists(_target))
    {
        smokephp_object *o = PHPQt::getSmokePHPObjectFromZval(_target);
        if (o && o->ptr())
        {
            _o = o;
        }
    }

    if( !(MethodCallBase::method().flags & Smoke::mf_static) && !(MethodCallBase::method().flags & Smoke::mf_ctor) && _o == 0 ){
	_target = Context::activeScope();
        _o = PHPQt::getSmokePHPObjectFromZval(_target);
    }

    _args = _smoke->argumentList + _smoke->methods[_method].args;
    _items = _smoke->methods[_method].numArgs;
    // TODO memory test
    _stack = new Smoke::StackItem[_items + 1];
}

MethodCall::~MethodCall()
{
    // nested frees, it should actually be deleted here
    // delete[] _stack;
    _stack = 0;
    if( _staticCall )
      efree( _target );
}

Marshall::Action
MethodCall::action()
{
	return Marshall::FromZVAL;
}

zval*
MethodCall::var()
{
	if (_cur < 0) return _retval;
	return MethodCallBase::_sp[_cur];
}

void
MethodCall::callMethod() {
	if(_called) return;
	_called = true;

	const QByteArray className(_smoke->className(method().classId));

	if (! className.endsWith(_smoke->methodNames[method().name])
		&& Z_TYPE_P(_target) == IS_NULL
		&& !(method().flags & Smoke::mf_static) )
	{
		php_error(E_ERROR, "Instance is not initialized, cannot call %s",
					_smoke->methodNames[method().name]);
	}

	if (Z_TYPE_P(_target) == IS_NULL && !(method().flags & Smoke::mf_static)) {
		php_error(E_ERROR, "%s is not a class method\n", _smoke->methodNames[method().name]);
	}

	const Smoke::ClassFn fn = _smoke->classes[method().classId].classFn;

	void *ptr = 0;

	if (_o != 0) {
		const Smoke::Class &cl = _smoke->classes[method().classId];

		ptr = _o->smoke()->cast(	(void *) _o->ptr(),
									_o->classId(),
									_o->smoke()->idClass(cl.className, true).index );
	} else {
	    if( !(method().flags & Smoke::mf_static) && !(method().flags & Smoke::mf_ctor) )
		pError( PHPQt::Method ) << "cannot call non-static " << className << "::" << Context::methodName()->constData() << " without an object.";
	}

	_items = -1;

	(*fn)(method().method, ptr, _stack);
	if (method().flags & Smoke::mf_ctor) {
		Smoke::StackItem s[2];
		s[1].s_voidp = PHPQt::binding();
		(*fn)(0, _stack[0].s_voidp, s);
	}
	// TODO return_value_used
	MethodReturnValue r(_smoke, _method, _stack, _retval);
}


const int
MethodCall::items()
{
	return _items;
}

bool
MethodCall::cleanup()
{
	return true;
}
/*
const char *
MethodCall::classname()
{
	return qstrcmp(MethodCallBase::classname(), "QGlobalSpace") == 0 ? "" : MethodCallBase::classname();
}
*/
