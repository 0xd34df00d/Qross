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

#include <QObject>

#include "EmitSignal.h"
#include "smokephp.h"

extern void smokeStackToQtStack(const Smoke::Stack stack, void ** o, const int items, MocArgument* args);
extern Marshall::HandlerFn getMarshallFn(const SmokeType &type);

EmitSignal::EmitSignal(QObject *obj, const int id, const int items, MocArgument *mocStack, zval **sp, zval * result) :
  _obj(obj), _id(id), _cur(0), _called(false)
{
    _items = items;
    _args = mocStack;
//    _id = id;
    _sp = sp;
    _result = result;
    _stack = new Smoke::StackItem[ items ];
}

EmitSignal::~EmitSignal()
{
    delete[] _stack;

}

Marshall::Action
EmitSignal::action()
{
    return Marshall::FromZVAL;
}

Smoke::StackItem &
EmitSignal::item()
{
    return _stack[_cur];
}

const char *
EmitSignal::mytype()
{
    return "signal";
}

void
EmitSignal::emitSignal()
{
    if (_called) return;
    _called = true;
    void ** o = new void*[_items];
    smokeStackToQtStack(_stack, o + 1, _items, _args + 1);
    _obj->metaObject()->activate(_obj, _id, o);
    delete[] o;
}

void
EmitSignal::mainfunction()
{
    emitSignal();
}

bool
EmitSignal::cleanup()
{
    return true;
}

SmokeType
EmitSignal::type()
{
    return arg().st;
}

zval*
EmitSignal::var()
{
    return _sp[ _cur-1 ];
}

Smoke *
EmitSignal::smoke()
{
    return type().smoke();
}

void
EmitSignal::unsupported()
{
	php_error(E_ERROR, "Cannot handle '%s' as %s argument\n", type().name(), mytype() );
}

const MocArgument &
EmitSignal::arg()
{
	return _args[_cur];
}

void
EmitSignal::next()
{
	const int oldcur = _cur;
	_cur++;

	while(!_called && _cur <= _items) {
	  Marshall::HandlerFn fn = getMarshallFn(type());
	  (*fn)(this);
	  _cur++;
	}
	emitSignal();
	_cur = oldcur;
}

