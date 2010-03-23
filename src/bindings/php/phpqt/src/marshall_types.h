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

#ifndef MARSHALL_TYPES_H
#define MARSHALL_TYPES_H

#include "marshall.h"

class MocArgument;

Marshall::HandlerFn getMarshallFn(const SmokeType &type);

extern void smokeStackToQtStack(const Smoke::Stack stack, void ** o, const int items, MocArgument* args);
extern void smokeStackFromQtStack(const Smoke::Stack stack, void ** _o, const int start, const int end, QList<MocArgument*> args);

#endif
