/***************************************************************************
 * kjsinterpreter.cpp
 * This file is part of the KDE project
 * copyright (C)2004-2006 by Sebastian Sauer (mail@dipe.org)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 ***************************************************************************/

#include "kjsinterpreter.h"
#include "kjsscript.h"

//#include <kglobal.h>
//#include <kstandarddirs.h>

// The in qrossconfig.h defined QROSS_EXPORT_INTERPRETER macro defines an
// exported C function used as factory for Qross::KjsInterpreter instances.
QROSS_EXPORT_INTERPRETER( Qross::KjsInterpreter )

using namespace Qross;

namespace Qross {

    /// \internal
    class KjsInterpreterPrivate
    {
        public:
    };

}

KjsInterpreter::KjsInterpreter(Qross::InterpreterInfo* info)
    : Qross::Interpreter(info)
    , d(new KjsInterpreterPrivate())
{
}

KjsInterpreter::~KjsInterpreter()
{
    delete d;
}

Qross::Script* KjsInterpreter::createScript(Qross::Action* action)
{
    return new KjsScript(this, action);
}

