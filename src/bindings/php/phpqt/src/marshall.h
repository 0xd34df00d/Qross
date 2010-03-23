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

#ifndef MARSHALL_H
#define MARSHALL_H

#include "smoke.h"
#include <php.h>

class SmokeType;

class Marshall {
public:
    /**
     * FromZVAL is used for virtual function return ce_ptrs and regular
     * method arguments.
     *
     * ToZVAL is used for method return-values and virtual function
     * arguments.
     */
    typedef void (*HandlerFn)(Marshall *);
    enum Action { FromZVAL, ToZVAL };
    virtual SmokeType type() = 0;
    virtual Action action() = 0;
    virtual Smoke::StackItem &item() = 0;
    virtual zval* var() = 0;
    virtual void unsupported() = 0;
    virtual Smoke *smoke() = 0;
    virtual bool doAlloc() = 0;
    /**
     * For return-values, next() does nothing.
     * For FromRV, next() calls the method and returns.
     * For ToRV, next() calls the virtual function and returns.
     *
     * Required to reset Marshall object to the state it was
     * before being called when it returns.
     */
    virtual void next() = 0;
    /**
     * For FromSV, cleanup() returns false when the handler should free
     * any allocated memory after next().
     *
     * For ToSV, cleanup() returns true when the handler should delete
     * the pointer passed to it.
     */
    virtual bool cleanup() = 0;

    virtual ~Marshall() {}
};

class SmokeEnumWrapper {
public:
	Marshall *m;
};

class SmokeClassWrapper {
public:
  Marshall *m;
};

struct TypeHandler {
    const char *name;
    Marshall::HandlerFn fn;
};

class smokephp_object;
void* construct_copy(smokephp_object* o);

#endif
