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

#ifndef EMITSIGNAL_H_
#define EMITSIGNAL_H_

#include "marshall.h"
#include "zend.h"

class MocArgument;
class QObject;

class EmitSignal : public Marshall
{
public:
	EmitSignal(QObject *obj, const int id, const int items, MocArgument* mocStack, zval **sp, zval * result);
	virtual ~EmitSignal();
    Marshall::Action action();
    Smoke::StackItem &item();
	const char *mytype();
	void emitSignal();
	void mainfunction();
	bool cleanup();
	void next();
	SmokeType type();
	zval* var();
	void unsupported();
	Smoke* smoke();
	const MocArgument &arg();
	bool doAlloc() { return false; }

 protected:
	MocArgument *_args;
	int _cur;
	bool _called;
	Smoke::Stack _stack;
	int _items;
	zval **_sp;
	QObject* _obj;
	int _id;
	zval* _result;
};

#endif /*EMITSIGNAL_H_*/

