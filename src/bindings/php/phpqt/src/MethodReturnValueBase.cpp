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

#include "MethodReturnValueBase.h"

MethodReturnValueBase::MethodReturnValueBase(
	Smoke *smoke,
	const Smoke::Index meth,
	const Smoke::Stack stack,
	zval* &retval
) : _smoke(smoke),
	_method(meth),
	_stack(stack),
	_retval(retval)
{
	_st.set(_smoke, method().ret);
}

MethodReturnValueBase::~MethodReturnValueBase()
{
}

const Smoke::Method&
MethodReturnValueBase::method()
{
	return _smoke->methods[_method];
}

Smoke::StackItem&
MethodReturnValueBase::item()
{
	return _stack[0];
}

Smoke *
MethodReturnValueBase::smoke()
{
	return _smoke;
}

SmokeType
MethodReturnValueBase::type()
{
	return _st;
}

void
MethodReturnValueBase::next() {}

bool
MethodReturnValueBase::cleanup()
{
	return false;
}

void
MethodReturnValueBase::unsupported()
{
	php_error(E_ERROR, "Cannot handle '%s' as return-type of %s::%s",
	type().name(),
	_smoke->className(method().classId),
	_smoke->methodNames[method().name]);
}

zval*
MethodReturnValueBase::var()
{
	return _retval;
}

