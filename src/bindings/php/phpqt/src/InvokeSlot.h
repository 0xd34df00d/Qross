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

#ifndef INVOKESLOT_H_
#define INVOKESLOT_H_

#include "MethodCallBase.h"
#include <QList>

class QByteArray;
class QMetaObject;
class MocArgument;

class InvokeSlot : public MethodCallBase
{
public:
    InvokeSlot(Smoke *smoke, const Smoke::Stack stack, const zval* obj, zval **sp, const int slotId, const QMetaObject* metaObject, void** a, const QByteArray& slotName);
	virtual ~InvokeSlot();

	Marshall::Action action();
	zval* var();
	virtual const int items();
	void callMethod();
	bool cleanup();
	bool doAlloc() { return true; }
	bool callable(const zend_class_entry* ce);
	SmokeType type();
	Smoke::StackItem& item();

	bool makeObject;

private:
	int _items;
	int _id;
	QByteArray _slotName;
	const QMetaObject* _metaObject;
	void** _a;
	QList<MocArgument*> _mocStack;

	const zval* _obj;
};

#endif /*INVOKESLOT_H_*/
