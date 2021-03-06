/***************************************************************************
 * rubyinterpreter.cpp
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

#include "rubymodule.h"
#include "rubyextension.h"

#include <QPointer>

using namespace Qross;

namespace Qross {

    /// \internal
    class RubyModulePrivate {
        friend class RubyModule;

        /// The name the module has.
        QString modulename;

        /// The \a RubyExtension instance that implements this \a RubyModule .
        RubyExtension* extension;
    };

}

RubyModule::RubyModule(QObject* parent, QObject* object, const QString & modname)
    : QObject(parent)
    , d(new RubyModulePrivate())
{
    Q_ASSERT(object);

    d->modulename = modname.left(1).toUpper() + modname.right(modname.length() - 1 );
    #ifdef QROSS_RUBY_MODULE_CTORDTOR_DEBUG
        qrossdebug(QString("RubyModule Ctor: %1").arg(d->modulename));
    #endif

    d->extension = new RubyExtension(object);
    VALUE rmodule = rb_define_module(d->modulename.toAscii());
    rb_define_module_function(rmodule,"method_missing",  (VALUE (*)(...))RubyModule::method_missing, -1);
    VALUE extension = RubyExtension::toVALUE(d->extension, /*owner*/ false);
    rb_define_const(rmodule, "MODULEOBJ", extension);
}

RubyModule::~RubyModule()
{
    #ifdef QROSS_RUBY_MODULE_CTORDTOR_DEBUG
        qrossdebug(QString("RubyModule Dtor: %1").arg(d->modulename));
    #endif

    delete d->extension;
    delete d;
}

RubyExtension* RubyModule::extension() const
{
    return d->extension;
}

VALUE RubyModule::method_missing(int argc, VALUE *argv, VALUE self)
{
    #ifdef QROSS_RUBY_MODULE_DEBUG
        QString funcname = rb_id2name(SYM2ID(argv[0]));
        qrossdebug(QString("RubyModule::method_missing \"%1\" missing, redirect to RubyExtension").arg(funcname));
    #endif

    //old kde3/qross1 code
    /*
    VALUE rubyObjectModule = rb_funcall( self, rb_intern("const_get"), 1, ID2SYM(rb_intern("MODULEOBJ")) );
    RubyModule* objectModule;
    Data_Get_Struct(rubyObjectModule, RubyModule, objectModule);
    //QObject* object = objectModule->d->object; //dynamic_cast<QObject*>(objectModule->d->object);
    //return RubyExtension::call_method(object, argc, argv);
    RubyExtension* extension = objectModule->d->extension;
    Q_ASSERT(extension);
    return RubyExtension::call_method(extension, argc, argv);
    */

    //the following solution works quit well, but does not take e.g. the connect() call into account
    /*
    VALUE extensionvalue = rb_funcall( self, rb_intern("const_get"), 1, ID2SYM(rb_intern("MODULEOBJ")) );
    RubyExtension* extension;
    Data_Get_Struct(extensionvalue, RubyExtension, extension);
    Q_ASSERT(extension);
    return RubyExtension::call_method_missing(extension, argc, argv, self);
    */

    //fetch the RubyExtension instance this module uses
    VALUE extensionvalue = rb_funcall( self, rb_intern("const_get"), 1, ID2SYM(rb_intern("MODULEOBJ")) );
    //redirect the call to our RubyExtension instance
    return rb_funcall2(extensionvalue, SYM2ID(argv[0]), argc-1, argc > 0 ? &argv[1] : 0);
}
