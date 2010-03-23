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
#include <QString>
#include "phpqt_internals.h"

#include "VirtualMethodReturnValue.h"
#include "InvokeSlot.h"

#include <QMetaObject>
#include <QMetaMethod>
#include <QByteArray>
#include "smokephp.h"

#include "marshall_types.h"

// TODO check the second and the 6th argument, its both _id in PHPQt::metacall
InvokeSlot::InvokeSlot(
		Smoke *smoke,
		const Smoke::Stack stack,
		const zval* obj,
		zval **sp,
		const int slotId,
		const QMetaObject* metaObject,
		void** a,
		const QByteArray& slotName
) : MethodCallBase( smoke, stack, sp ),
    _obj(obj),
    _id(slotId),
    _metaObject(metaObject),
    _a(a),
    _slotName( slotName )
{
    _args = _smoke->argumentList + method().args;

    QList<QByteArray> qargs = _metaObject->method(_id).parameterTypes();
    _items = qargs.count();
    _mocStack = PHPQt::QtToMoc(smoke, _a + 1, qargs);
    smokeStackFromQtStack(_stack, _a + 1, 0, _items, _mocStack);
}

InvokeSlot::~InvokeSlot()
{
#ifdef TEMP_DISABLED
  delete[] _stack;
#endif
}

Marshall::Action
InvokeSlot::action()
{
	return Marshall::ToZVAL;
}

zval*
InvokeSlot::var()
{
	MethodCallBase::_sp[_cur] = (zval*) emalloc(sizeof(zval));
    return MethodCallBase::_sp[_cur];
}

const int
InvokeSlot::items()
{
    return _items;
}

void
InvokeSlot::callMethod()
{
    if (_called) return;
    _called = true;
    zval* retval = PHPQt::callPHPMethod(_obj, _slotName.constData(), items(), MethodCallBase::_sp);
//    if(_args[0].argType != xmoc_void)
	VirtualMethodReturnValue r(_smoke, _method, _stack, retval);
}

bool
InvokeSlot::cleanup()
{
	return false;
}

bool
InvokeSlot::callable(const zend_class_entry* ce)
{
    return PHPQt::methodExists(ce, _slotName.constData());
}

SmokeType
InvokeSlot::type()
{
    return _mocStack[_cur]->st;
}

Smoke::StackItem &
InvokeSlot::item()
{
    return _stack[_cur];
}
