/***************************************************************************
 * qrossconfig.h
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

#ifndef QROSS_MAIN_QROSSCONFIG_H
#define QROSS_MAIN_QROSSCONFIG_H

#include "qross_export.h"

#include <QtCore/QString>
#include <QtCore/QMetaType>

namespace Qross {

    // Debugging enabled. Comment the line out to disable all kind of debugging.
    #define QROSS_DEBUG_ENABLED

    #ifdef QROSS_DEBUG_ENABLED

        /**
         * Debugging function.
         */
        QROSSCORE_EXPORT void qrossdebug(const QString &s);

        /**
         * Warning function.
         */
        QROSSCORE_EXPORT void qrosswarning(const QString &s);

    #else
        // Define these to an empty statement if debugging is disabled.
        #define qrossdebug(x)
        #define qrosswarning(x)
    #endif

    // Some more debug switches.
    //#define QROSS_OBJECT_METACALL_DEBUG
    //#define QROSS_METATYPE_DEBUG
    //#define QROSS_INTERPRETER_DEBUG
    //#define QROSS_ACTION_DEBUG
    //#define QROSS_ACTIONCOLLECTION_DEBUG

    // The version number of Qross. For example the interpreters use
    // it do be sure there are linked against the correct core version
    // and if the numbers don't match, the interpreter is not loaded.
    #define QROSS_VERSION 12

    // The export macro for interpreter plugins.
    #define QROSS_EXPORT_INTERPRETER( InterpreterImpl ) \
        extern "C" { \
			Q_DECL_EXPORT void* qrossinterpreter(int version, Qross::InterpreterInfo* info) { \
                if(version != QROSS_VERSION) { \
                    Qross::qrosswarning(QString("Interpreter skipped cause provided version %1 does not match expected version %2.").arg(version).arg(QROSS_VERSION)); \
                    return 0; \
                } \
                return new InterpreterImpl(info); \
            } \
        }

    // The name of the interpreter's library. Those library got loaded
    // dynamically during runtime. Comment out to disable compiling of
    // the interpreter-plugin or to hardcode the location of the lib
    // like I did at the following line.
    //#define QROSS_PYTHON_LIBRARY "/home/kde4/koffice/_build/lib/qrosspython.la"

    #define QROSS_PYTHON_LIBRARY "qrosspython" SHLIB_SUFFIX
    #define QROSS_RUBY_LIBRARY "qrossruby" SHLIB_SUFFIX
    //#define QROSS_KJS_LIBRARY "qrosskjs"
    #define QROSS_JAVA_LIBRARY "libqrossjava" SHLIB_SUFFIX
    #define QROSS_FALCON_LIBRARY "qrossfalcon" SHLIB_SUFFIX
    #define QROSS_QTSCRIPT_LIBRARY "qrossqts" SHLIB_SUFFIX
    #define QROSS_LUA_LIBRARY "qloss" SHLIB_SUFFIX

}

#endif

