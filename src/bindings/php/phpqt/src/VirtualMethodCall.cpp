/**
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2008 - 2009
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

#include "phpqt_internals.h"
#include "VirtualMethodCall.h"
#include "VirtualMethodReturnValue.h"

#include "marshall_types.h"

VirtualMethodCall::VirtualMethodCall(Smoke *smoke, const Smoke::Index meth, const Smoke::Stack stack, zval* obj, zval **sp) :
 	MethodCallBase( smoke, meth, stack, sp), _obj(obj)
{
  	_args = _smoke->argumentList + method().args;
}

VirtualMethodCall::~VirtualMethodCall()
{
}

Marshall::Action
VirtualMethodCall::action()
{
	return Marshall::ToZVAL;
}

zval*
VirtualMethodCall::var()
{
    return _sp[_cur];
}

const int
VirtualMethodCall::items()
{
	return method().numArgs;
}

void
VirtualMethodCall::callMethod()
{
	if (_called) return;
	_called = true;

	zval* retval = PHPQt::callPHPMethod(_obj, _smoke->methodNames[method().name], items(), _sp);
	VirtualMethodReturnValue r(_smoke, _method, _stack, retval);
//	efree( retval );
}

bool
VirtualMethodCall::cleanup()
{
	return false;
}
