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

#ifndef METHODRETURNVALUEBASE_H_
#define METHODRETURNVALUEBASE_H_


#include "smoke.h"
#include "smokephp.h"
#include "marshall.h"

class MethodReturnValueBase : public Marshall
{
public:
	MethodReturnValueBase(Smoke *smoke, const Smoke::Index meth, const Smoke::Stack stack, zval* &retval);
	virtual ~MethodReturnValueBase();
	const Smoke::Method &method();
	Smoke::StackItem &item();
	Smoke *smoke();
	SmokeType type();
	void next();
	bool cleanup();
	void unsupported();
	zval* var();
	bool doAlloc() { return true; }

protected:
	Smoke *_smoke;
	Smoke::Index _method;
	Smoke::Stack _stack;
	SmokeType _st;
	zval* &_retval;
};

#endif /*METHODRETURNVALUEBASE_H_*/
