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
#ifndef METHODCALLBASE_H_
#define METHODCALLBASE_H_

#include "marshall.h"

class Smoke;

class MethodCallBase : public Marshall
{
public:
	MethodCallBase(Smoke *smoke, const Smoke::Index meth, zval** sp);
	MethodCallBase(Smoke *smoke, const Smoke::Index meth, const Smoke::Stack stack, zval** sp);
	MethodCallBase(Smoke *smoke, const Smoke::Stack stack, zval** sp);
	//	virtual ~MethodCallBase();

	Smoke *smoke();
	SmokeType type();
       	Smoke::StackItem &item();
	const Smoke::Method &method();
	virtual const int items() = 0;
	virtual void callMethod() = 0;
	void next();
	void unsupported();

protected:
	Smoke *_smoke;
	Smoke::Index _method;
	Smoke::Stack _stack;
	int _cur;
	Smoke::Index *_args;
	bool _called;
	zval **_sp;
};

#endif /*METHODCALLBASE_H_*/
