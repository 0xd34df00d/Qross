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

#ifndef METHODCALL_H_
#define METHODCALL_H_

#include "MethodCallBase.h"
#include "smoke.h"
#include "php.h"

class MethodCall : public MethodCallBase
{
public:
	MethodCall(Smoke *smoke, const Smoke::Index method, zval* target, zval **sp, zval *&retval);
	virtual ~MethodCall();
	Marshall::Action action();
	zval* var();
	void callMethod();
	virtual const int items();
	bool cleanup();
	bool doAlloc() { return false; }

private:
	zval* _target;
	int _items;
	zval *&_retval;
	smokephp_object * _o;
	bool _staticCall;
};

#endif /*METHODCALL_H_*/
