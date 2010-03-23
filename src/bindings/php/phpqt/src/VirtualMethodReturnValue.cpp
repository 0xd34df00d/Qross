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

#include "VirtualMethodReturnValue.h"
#include "marshall_types.h"

VirtualMethodReturnValue::VirtualMethodReturnValue(
	Smoke *smoke,
	const Smoke::Index methodIndex,
	const Smoke::Stack stack,
	zval* retval
) : MethodReturnValueBase( smoke, methodIndex, stack, retval )
{
	Marshall::HandlerFn fn = getMarshallFn(type());
	(*fn)(this);
}

VirtualMethodReturnValue::~VirtualMethodReturnValue()
{
}

Marshall::Action
VirtualMethodReturnValue::action()
{
	return Marshall::FromZVAL;
}
