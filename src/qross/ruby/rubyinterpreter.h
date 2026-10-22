/***************************************************************************
 * rubyinterpreter.h
 * This file is part of the KDE project
 * copyright (C)2005 by Cyrille Berger (cberger@cberger.net)
 * copyright (C)2006 by Sebastian Sauer (mail@dipe.org)
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

#ifndef QROSS_RUBYRUBYINTERPRETER_H
#define QROSS_RUBYRUBYINTERPRETER_H

#include "rubyconfig.h"

#include <qross/core/qrossconfig.h>
#include <qross/core/interpreter.h>

#include <QPointer>

namespace Qross {

    class RubyModule;
    class RubyInterpreterPrivate;

    /**
    * This class is the bridget between Qross and Ruby.
    * @author Cyrille Berger
    */
    class RubyInterpreter : public Qross::Interpreter
    {
        public:

            /**
            * Constructor
            *
            * @param info The \a Qross::InterpreterInfo instance
            *        that describes this \a RubyInterpreter .
            */
            explicit RubyInterpreter(Qross::InterpreterInfo* info);

            /**
            * Destructor.
            */
            virtual ~RubyInterpreter();

            /**
            * Factory method to create and return a new \a RubyScript instance.
            */
            virtual Qross::Script* createScript(Qross::Action* action);

            /**
            * @return the hash of \a RubyModule instances we know about.
            */
            QHash<QString, QPointer<RubyModule> > modules() const;
        public:
            /**
             * @return the ruby object with the module Qross, this module holds class
             * definition used by qross, and scripts object. All qross specific objects
             * should be member of that module.
             */
            static VALUE qrossModule();

        private:
            /// Initialize the ruby interpreter.
            void initRuby();
            /// Finalize the ruby interpreter.
            void finalizeRuby();
            /// Load an external plugin / module.
            static VALUE require (VALUE, VALUE);
        private:
            /// Private d-pointer.
            static RubyInterpreterPrivate * d;
    };

}

#endif
