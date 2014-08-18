/***************************************************************************
 * pythoninterpreter.h
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

#ifndef QROSS_PYTHONINTERPRETER_H
#define QROSS_PYTHONINTERPRETER_H

#include "pythonconfig.h"
#include <qross/core/qrossconfig.h>
#include <qross/core/interpreter.h>
#include <qross/core/action.h>
#include <qross/core/manager.h>

#include <QString>

namespace Qross {

    // Forward declarations.
    class PythonScript;
    class PythonModule;
    class PythonInterpreterPrivate;

    /**
     * Python interpreter bridge.
     *
     * Implements the \a Qross::Interpreter for the python interpreter
     * backend and provides with the \a Qross::PythonInterpreter::createScript
     * a factory method to create \a Qross::PythonScript instances.
     */
    class PythonInterpreter : public Qross::Interpreter
    {
            friend class PythonScript;
        public:

            /**
             * Constructor.
             *
             * \param info The \a Qross::InterpreterInfo instance
             *        which describes the \a PythonInterpreter for
             *        applications using Qross.
             */
            explicit PythonInterpreter(Qross::InterpreterInfo* info);

            /**
             * Destructor.
             */
            virtual ~PythonInterpreter();

            /**
             * \return a \a PythonScript instance.
             */
            virtual Qross::Script* createScript(Qross::Action* Action);

            /**
             * Extract the current exception and fill the passed \p errorlist with
             * the errortrace and \p lineno with the line-number where the exception
             * got raised (-1 if not known else >= 0).
             */
            static void extractException(QStringList& errorlist, int& lineno);

			static void setImportException(const QString&);
        private:
            /// \internal d-pointer instance.
            PythonInterpreterPrivate * const d;

            /// Initialize the python interpreter.
            inline void initialize();
            /// Finalize the python interpreter.
            inline void finalize();

            /**
             * \return the \a PythonModule instance.
             */
            PythonModule* mainModule() const;
    };

}

#endif
