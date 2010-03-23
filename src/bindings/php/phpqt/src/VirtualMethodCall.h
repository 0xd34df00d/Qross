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

#ifndef VIRTUALMETHODCALL_H_
#define VIRTUALMETHODCALL_H_

#include "MethodCallBase.h"

/**
 * handles virtual method calls
 */
class VirtualMethodCall : public MethodCallBase
{
public:
    VirtualMethodCall(Smoke *smoke, const Smoke::Index meth, const Smoke::Stack stack, zval* obj, zval **sp);
    virtual ~VirtualMethodCall();

    Marshall::Action action();
    zval* var();
    const int items();
    void callMethod();
    bool cleanup();
    bool doAlloc() { return true; }

    bool makeObject;

private:
    zval* _obj;
};

#endif /*VIRTUALMETHODCALL_H_*/
