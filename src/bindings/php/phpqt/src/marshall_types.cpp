/*!
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2006 - 2009
 * Thomas Moenicke <tm at php-qt.org>
 *
 * marshall_types.cpp - Derived from the QtRuby and PerlQt sources, see AUTHORS
 *                       for details
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

#include <Qt/qmetaobject.h>
#include "marshall_types.h"
#include "php_qt.h"
#include "phpqt_internals.h"
#include "smokephp.h"
#include "MethodCallBase.h"

#include <QList>

void
smokeStackToQtStack(const Smoke::Stack stack, void ** o, const int items, MocArgument* args)
{

	for (int i = 0; i < items; i++) {
		Smoke::StackItem *si = stack + i + 1;
		switch(args[i].argType) {
		case xmoc_bool:
			o[i] = &si->s_bool;
			break;
		case xmoc_int:
			o[i] = &si->s_int;
			break;
		case xmoc_double:
			o[i] = &si->s_double;
			break;
		case xmoc_charstar:
			o[i] = &si->s_voidp;
			break;
		case xmoc_QString:
			o[i] = si->s_voidp;
			break;
		default:
		{
			const SmokeType &t = args[i].st;
			void *p;
			switch(t.elem()) {
			case Smoke::t_bool:
				p = &si->s_bool;
				break;
			case Smoke::t_char:
				p = &si->s_char;
				break;
			case Smoke::t_uchar:
				p = &si->s_uchar;
				break;
			case Smoke::t_short:
				p = &si->s_short;
				break;
			case Smoke::t_ushort:
				p = &si->s_ushort;
				break;
			case Smoke::t_int:
				p = &si->s_int;
				break;
			case Smoke::t_uint:
				p = &si->s_uint;
				break;
			case Smoke::t_long:
				p = &si->s_long;
				break;
			case Smoke::t_ulong:
				p = &si->s_ulong;
				break;
			case Smoke::t_float:
				p = &si->s_float;
				break;
			case Smoke::t_double:
				p = &si->s_double;
				break;
			case Smoke::t_enum:
			{
				// allocate a new enum value
				Smoke::EnumFn fn = SmokeClass(t).enumFn();
				if (!fn) {
					php_error(E_WARNING, "Unknown enumeration %s\n", t.name());
					p = new int((int)si->s_enum);
					break;
				}
				const Smoke::Index id = t.typeId();
				(*fn)(Smoke::EnumNew, id, p, si->s_enum);
				(*fn)(Smoke::EnumFromLong, id, p, si->s_enum);
				// FIXME: MEMORY LEAK
				break;
			}
			case Smoke::t_class:
			case Smoke::t_voidp:
				if (strchr(t.name(), '*') != 0) {
					p = &si->s_voidp;
				} else {
					p = si->s_voidp;
				}
				break;
			default:
				p = 0;
				break;
			}
			o[i] = p;
		}
		}
	}
}

void
smokeStackFromQtStack(const Smoke::Stack stack, void ** _o, const int start, const int end, QList<MocArgument*> args)
{
    for (int i = start, j = 0; i < end; i++, j++)
	{
	    void *o = _o[i];
	    switch(args[j]->argType)
	    {
	    case xmoc_bool:
		stack[j].s_bool = *(bool*)o;
		break;
	    case xmoc_int:
		stack[j].s_int = *(int*)o;
		break;
	    case xmoc_double:
		stack[j].s_double = *(double*)o;
		break;
	    case xmoc_charstar:
		stack[j].s_voidp = o;
		break;
	    case xmoc_QString:
		stack[j].s_voidp = o;
		break;
	    default:	// case xmoc_ptr:
	    {
		const SmokeType &t = args[i]->st;
		void *p = o;
		switch(t.elem()) {
		case Smoke::t_bool:
		    stack[j].s_bool = **(bool**)o;
		    break;
		case Smoke::t_char:
		    stack[j].s_char = **(char**)o;
		    break;
		case Smoke::t_uchar:
		    stack[j].s_uchar = **(unsigned char**)o;
		    break;
		case Smoke::t_short:
		    stack[j].s_short = **(short**)p;
		    break;
		case Smoke::t_ushort:
		    stack[j].s_ushort = **(unsigned short**)p;
		    break;
		case Smoke::t_int:
		    stack[j].s_int = **(int**)p;
		    break;
		case Smoke::t_uint:
		    stack[j].s_uint = **(unsigned int**)p;
		    break;
		case Smoke::t_long:
		    stack[j].s_long = **(long**)p;
		    break;
		case Smoke::t_ulong:
		    stack[j].s_ulong = **(unsigned long**)p;
		    break;
		case Smoke::t_float:
		    stack[j].s_float = **(float**)p;
		    break;
		case Smoke::t_double:
		    stack[j].s_double = **(double**)p;
		    break;
		case Smoke::t_enum:
		{
		    Smoke::EnumFn fn = SmokeClass(t).enumFn();
		    if (!fn) {
			php_error(E_WARNING, "Unknown enumeration %s\n", t.name());
			stack[j].s_enum = **(int**)p;
			break;
		    }
		    const Smoke::Index id = t.typeId();
		    (*fn)(Smoke::EnumToLong, id, p, stack[j].s_enum);
		}
		break;
		case Smoke::t_class:
		case Smoke::t_voidp:
		    if (strchr(t.name(), '*') != 0) {
			stack[j].s_voidp = *(void **)p;
		    } else {
			stack[j].s_voidp = p;
		    }
		    break;
		}
	    }
	    }
	}
}

