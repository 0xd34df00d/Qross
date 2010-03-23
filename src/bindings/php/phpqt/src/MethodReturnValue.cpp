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

#include "MethodReturnValue.h"
#include "marshall_types.h"

MethodReturnValue::MethodReturnValue(
		Smoke *smoke,
		const Smoke::Index methodIndex,
		const Smoke::Stack stack,
		zval *&retval
) : MethodReturnValueBase( smoke, methodIndex, stack, retval )
{
	Marshall::HandlerFn fn = getMarshallFn(type());
	(*fn)(this);
}

MethodReturnValue::~MethodReturnValue()
{
}

Marshall::Action
MethodReturnValue::action()
{
	return Marshall::ToZVAL;
}
/*
const char *
MethodReturnValue::classname()
{
	return qstrcmp(MethodReturnValueBase::classname(), "QGlobalSpace") == 0 ? "" : MethodReturnValueBase::classname();
}
*/
