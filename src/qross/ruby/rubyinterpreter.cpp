/***************************************************************************
 * rubyinterpreter.cpp
 * This file is part of the KDE project
 * copyright (C)2005,2007 by Cyrille Berger (cberger@cberger.net)
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

#include "rubyinterpreter.h"
#include "rubyextension.h"
#include "rubymodule.h"
#include "rubyscript.h"

#include <qross/core/manager.h>
#include <qross/core/action.h>

#include <map>

#include <QRegExp>

// The in qrossconfig.h defined QROSS_EXPORT_INTERPRETER macro defines an
// exported C function used as factory for Qross::RubyInterpreter instances.
QROSS_EXPORT_INTERPRETER( Qross::RubyInterpreter )

using namespace Qross;

namespace Qross {

    //typedef std::map<QString, VALUE> mStrVALUE;
    //typedef mStrVALUE::iterator mStrVALUE_it;
    //typedef mStrVALUE::const_iterator mStrVALUE_cit;

    /// \internal
    class RubyInterpreterPrivate {
        friend class RubyInterpreter;
        QHash<QString, QPointer<RubyModule> > modules;
        static VALUE s_qrossModule;
    };
}

RubyInterpreterPrivate* RubyInterpreter::d = 0;
VALUE RubyInterpreterPrivate::s_qrossModule = 0;

RubyInterpreter::RubyInterpreter(Qross::InterpreterInfo* info)
    : Qross::Interpreter(info)
{
#ifdef QROSS_RUBY_INTERPRETER_CTORDTOR_DEBUG
    qrossdebug("RubyInterpreter Ctor");
#endif

    if(d == 0)
    {
        initRuby();
    }

    const int defaultsafelevel = 4; // per default use the maximum safelevel
    rb_set_safe_level( info->optionValue("safelevel", defaultsafelevel).toInt() );
}

RubyInterpreter::~RubyInterpreter()
{
#ifdef QROSS_RUBY_INTERPRETER_CTORDTOR_DEBUG
    qrossdebug("RubyInterpreter Dtor");
#endif
    finalizeRuby();
}

QHash<QString, QPointer<RubyModule> > RubyInterpreter::modules() const
{
    return d->modules;
}

Qross::Script* RubyInterpreter::createScript(Qross::Action* action)
{
    return new RubyScript(this, action);
}

void RubyInterpreter::initRuby()
{
    #ifdef QROSS_RUBY_INTERPRETER_DEBUG
        qrossdebug( QString("RubyInterpreter::initRuby()") );
    #endif

    d = new RubyInterpreterPrivate();
#ifdef RUBY_INIT_STACK
    RUBY_INIT_STACK
#endif
    ruby_init();
    ruby_init_loadpath();
    rb_define_global_function("require", (VALUE (*)(...))RubyInterpreter::require, 1);
    if( ! RubyInterpreterPrivate::s_qrossModule )
    {
      RubyInterpreterPrivate::s_qrossModule = rb_define_module("Qross");
      RubyExtension::init();
    }
}

VALUE RubyInterpreter::qrossModule()
{
    Q_ASSERT(RubyInterpreterPrivate::s_qrossModule);
    return RubyInterpreterPrivate::s_qrossModule;
}


void RubyInterpreter::finalizeRuby()
{
    #ifdef QROSS_RUBY_INTERPRETER_DEBUG
        qrossdebug( QString("RubyInterpreter::finalizeRuby()") );
    #endif

    if(d) {
        for(QHash<QString, QPointer<RubyModule> >::Iterator it = d->modules.begin(); it != d->modules.end(); ++it)
            delete it.value();
        d->modules.clear();
    }
    delete d;
    d = 0;

    #ifdef QROSS_RUBY_FINALIZE
        ruby_finalize();
    #endif
}

VALUE RubyInterpreter::require (VALUE self, VALUE name)
{
    #ifdef QROSS_RUBY_INTERPRETER_DEBUG
        qrossdebug( QString("RubyInterpreter::require self=%1 name=%2").arg(STR2CSTR(rb_inspect(self))).arg(STR2CSTR(rb_inspect(name))) );
    #endif

    QString modname = StringValuePtr(name);

    if( RubyScript::isRubyScript(self) ) {
        VALUE rubyscriptvalue = rb_funcall(self, rb_intern("const_get"), 1, ID2SYM(rb_intern("RUBYSCRIPTOBJ")));
        RubyScript* rubyscript;
        Data_Get_Struct(rubyscriptvalue, RubyScript, rubyscript);
        Q_ASSERT(rubyscript);
        Action* action = rubyscript->action();
        Q_ASSERT(action);

        if( action->hasObject(modname) ) {
            #ifdef QROSS_RUBY_INTERPRETER_DEBUG
                qrossdebug( QString("RubyInterpreter::require() module=%1 is internal local child").arg(modname) );
            #endif
            QObject* object = action->object(modname);
            Q_ASSERT(object);
            RubyModule* module = rubyscript->module(object, modname);
            Q_ASSERT(module);
            return Qtrue;
        } else {
            #ifdef QROSS_RUBY_INTERPRETER_DEBUG
                qrossdebug(QString("RubyInterpreter::require() module=%1 is not an internal local child").arg(modname));
            #endif
        }
        if( Qross::Manager::self().hasObject(modname) ) {
            #ifdef QROSS_RUBY_INTERPRETER_DEBUG
                qrossdebug( QString("RubyInterpreter::require() module=%1 is internal global child").arg(modname) );
            #endif
            QObject* object = Qross::Manager::self().object(modname);
            Q_ASSERT(object);
            RubyModule* module = d->modules.contains(modname) ? d->modules[modname] : 0;
            if( ! module ) {
                module = new RubyModule(rubyscript, object, modname);
                //VALUE rmodule = rb_define_module(modname.ascii());
                //rb_define_module_function();
                //VALUE rm = RubyExtension::toVALUE(module);
                //rb_define_variable( ("$" + modname).ascii(), & RubyInterpreter::d->m_modules.insert( mStrVALUE::value_type( modname, rm) ).first->second );
                d->modules.insert(modname, module);
            }
            Q_ASSERT(module);
            return Qtrue;
        } else {
            #ifdef QROSS_RUBY_INTERPRETER_DEBUG
                qrossdebug(QString("RubyInterpreter::require() module=%1 is not an internal global child").arg(modname));
            #endif
        }
    } else {
        #ifdef QROSS_RUBY_INTERPRETER_DEBUG
            qrossdebug("Self is not a ruby script, using ruby's require");
        #endif
    }

    if( modname == "Qt" || modname == "Qt4" || modname == "korundum4" )
    {
        VALUE val = rb_f_require(self, name);
        if( val == Qtrue )
        {
          rb_eval_string("Qt::Internal::set_qtruby_embedded( true )");
        }
        return val;
    }
    
    // We don't know about a module with such a name. So, let Ruby handle it...
    return rb_f_require(self, name);
}
