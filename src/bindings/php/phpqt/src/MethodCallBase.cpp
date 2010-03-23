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

#include "MethodCallBase.h"

#include "smoke.h"
#include "smokephp.h"

Marshall::HandlerFn getMarshallFn(const SmokeType &type);

MethodCallBase::MethodCallBase(Smoke *smoke, const Smoke::Index meth, zval **sp) :
	_smoke(smoke), _method(meth), _cur(-1), _called(false), _sp(sp)
{
}

MethodCallBase::MethodCallBase(Smoke *smoke, const Smoke::Index meth, const Smoke::Stack stack, zval** sp) :
	_smoke(smoke), _method(meth), _stack(stack), _cur(-1), _called(false), _sp(sp)
{
}

MethodCallBase::MethodCallBase(Smoke *smoke, const Smoke::Stack stack, zval** sp) :
	_smoke(smoke), _method(0), _stack(stack), _cur(-1), _called(false), _sp(sp)
{
}
/*
MethodCallBase::~MethodCallBase()
{
}
*/
Smoke *
MethodCallBase::smoke()
{
	return _smoke;
}

SmokeType
MethodCallBase::type()
{
	return SmokeType(_smoke, _args[_cur]);
}

Smoke::StackItem &
MethodCallBase::item()
{
	return _stack[_cur + 1];
}

const Smoke::Method &
MethodCallBase::method()
{
	return _smoke->methods[_method];
}

void
MethodCallBase::next()
{
	const int oldcur = _cur;
	_cur++;
	while(!_called && _cur < items() ) {
		Marshall::HandlerFn fn = getMarshallFn(type());
		(*fn)(this);
		_cur++;
	}
	callMethod();
	_cur = oldcur;
}

void
MethodCallBase::unsupported()
{
	php_error(E_ERROR, "Cannot handle '%s' as argument of %s::%s",
		type().name(),
		_smoke->className(method().classId),
		_smoke->methodNames[method().name]);
}
