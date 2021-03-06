/***************************************************************************
 * pythonextension.cpp
 * This file is part of the KDE project
 * copyright (C)2004-2005 by Sebastian Sauer (mail@dipe.org)
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

#include "pythonextension.h"
#include "pythoninterpreter.h"
#include "pythonvariant.h"
#include "pythonfunction.h"

#include <QWidget>
#include <QMetaMethod>
#include <QSignalSpy>
#include <QVarLengthArray>

namespace Qross {

    /// \internal d-pointer class.
    class PythonExtension::Private
    {
        public:
            /// The QObject this PythonExtension wraps.
            QPointer<QObject> object;
            /// Defines if this PythonExtension the owner of the QObject.
            bool owner;

            #ifdef QROSS_PYTHON_EXTENSION_CTORDTOR_DEBUG
                /// \internal string for debugging.
                QString debuginfo;
            #endif

            /// The cached list of methods.
            QHash<QByteArray, Py::Int> methods;
            /// The cached list of properties.
            QHash<QByteArray, QMetaProperty> properties;
            /// The cached list of enumerations.
            QHash<QByteArray, int> enumerations;

            /// The \a PythonFunction instances.
            QHash<QByteArray, PythonFunction*> functions;

            /// The cached list of methodnames.
            Py::List methodnames;
            /// The cached list of membernames.
            Py::List membernames;

            /// The proxymethod which will handle all calls to our \a PythonExtension instance.
            Py::MethodDefExt<PythonExtension>* proxymethod;

    };

}

using namespace Qross;

PythonExtension::PythonExtension(QObject* object, bool owner)
    : Py::PythonExtension<PythonExtension>()
    , d( new Private() )
{
    d->object = object;
    d->owner = owner;

    #ifdef QROSS_PYTHON_EXTENSION_CTORDTOR_DEBUG
        d->debuginfo = object ? QString("%1 (%2)").arg(object->objectName()).arg(object->metaObject()->className()) : "NULL";
        qrossdebug( QString("PythonExtension::Constructor object=%1").arg(d->debuginfo) );
    #endif

    behaviors().name("QrossPythonExtension");
    behaviors().doc("The QrossPythonExtension object wraps a QObject into the world of python.");
    //behaviors().supportPrint();
    behaviors().supportGetattr();
    behaviors().supportSetattr();
    //behaviors().supportGetattro();
    //behaviors().supportSetattro();
    behaviors().supportCompare();
    //behaviors().supportRepr();
    //behaviors().supportStr();
    behaviors().supportHash();
    //behaviors().supportIter();
    //behaviors().supportCall();
    behaviors().supportSequenceType();
    behaviors().supportMappingType();
    behaviors().supportNumberType();
    //behaviors().supportBufferType();

    add_varargs_method("className", &PythonExtension::getClassName, "Return the name of the QObject class.");
    //add_varargs_method("classInfo", &PythonExtension::getClassInfo, "Return a list of key,value-tuples of class information.");
    add_varargs_method("signalNames", &PythonExtension::getSignalNames, "Return list of signal names the QObject provides.");
    add_varargs_method("slotNames", &PythonExtension::getSlotNames, "Return list of slot names the QObject provides.");
    add_varargs_method("propertyNames", &PythonExtension::getPropertyNames, "Return list of property names the QObject provides.");
    //add_varargs_method("dynamicPropertyNames", &PythonExtension::getDynamicPropertyNames, "");
    add_varargs_method("property", &PythonExtension::getProperty, "Return a property value.");
    add_varargs_method("setProperty", &PythonExtension::setProperty, "Set a property value.");
    add_varargs_method("__toPointer__", &PythonExtension::toPointer, "Return the void* pointer of the QObject.");
    //add_varargs_method("__fromPointer__", &PythonExtension::fromPointer, "Set the QObject* to the passed void* pointer.");
    add_varargs_method("connect", &PythonExtension::doConnect, "Connect signal, slots or python functions together.");
    add_varargs_method("disconnect", &PythonExtension::doDisconnect, "Disconnect signal, slots or python functions that are connected together.");

    d->proxymethod = new Py::MethodDefExt<PythonExtension>(
        "", // methodname, not needed cause we use the method only internaly.
        0, // method that should handle the callback, not needed cause proxyhandler will handle it.
        Py::method_varargs_call_handler_t( proxyhandler ), // callback handler
        "" // documentation
    );

    if(d->object) {
        const QMetaObject* metaobject = d->object->metaObject();

        { // initialize methods.
            const int count = metaobject->methodCount();
            for(int i = 0; i < count; ++i) {
                QMetaMethod member = metaobject->method(i);
#if QT_VERSION < 0x050000
                const QString signature = member.signature();
#else
                const QString signature = member.methodSignature();
#endif
                const QByteArray name = signature.left(signature.indexOf('(')).toLatin1();
                if(! d->methods.contains(name)) {
                    d->methods.insert(name, Py::Int(i));
                    d->methodnames.append(Py::String(name));
                }
            }
        }

        { // initialize properties
            const int count = metaobject->propertyCount();
            for(int i = 0; i < count; ++i) {
                QMetaProperty prop = metaobject->property(i);
                d->properties.insert(prop.name(), prop);
                d->membernames.append( Py::String(prop.name()) );
            }
        }

        { // initialize enumerations
            const int count = metaobject->enumeratorCount();
            for(int i = 0; i < count; ++i) {
                QMetaEnum e = metaobject->enumerator(i);
                const int kc = e.keyCount();
                for(int k = 0; k < kc; ++k) {
                    const QByteArray name = /*e.name() +*/ e.key(k);
                    d->enumerations.insert(name, e.value(k));
                    d->membernames.append( Py::String(name) );
                }
            }
        }
    }
}

PythonExtension::~PythonExtension()
{
    #ifdef QROSS_PYTHON_EXTENSION_CTORDTOR_DEBUG
        qrossdebug( QString("PythonExtension::Destructor object=%1").arg(d->debuginfo) );
    #endif
    if( d->owner )
        delete d->object;

    qDeleteAll(d->functions);//FIXME curently it may delete connections (i.e. PythonFunctions) that we want to stay!
    delete d->proxymethod;
    delete d;
}

QObject* PythonExtension::object() const
{
    return d->object;
}

Py::Object PythonExtension::getattr(const char* n)
{
    #ifdef QROSS_PYTHON_EXTENSION_GETATTR_DEBUG
        qrossdebug( QString("PythonExtension::getattr name='%1'").arg(n) );
    #endif

    // handle internal methods
    if(n[0] == '_') {
        if(strcmp(n,"__methods__") == 0)
            return d->methodnames;
        if(strcmp(n,"__members__") == 0)
            return d->membernames;
        //if(strcmp(n,"__dict__") == 0)
        //    return PythonType<QStringList>::toPyObject( QStringList() );
        if(strcmp(n,"__all__") == 0) //this hack is needed to prevent "from-import-* object has no __dict__ and no __all__" exceptions
            return d->methodnames;
    }

    // look if the attribute is a method
    if(d->methods.contains(n)) {
        #ifdef QROSS_PYTHON_EXTENSION_GETATTR_DEBUG
            qrossdebug( QString("PythonExtension::getattr name='%1' is a method.").arg(n) );
        #endif

        // Python is more dynamic then someone thinks of what provides us bigger problems
        // here since we are not able to cache the whole lookup and need to create and return
        // a new function object at each request since 1) they may used internaly by python
        // to redirect this method/attr to somebody else and 2) those returned function object
        // may prevent this object instance from beeing removed by the garbage collector.

        //FIXME use callcache here to improve the performance by some factors!
        Py::Tuple t(3);
        t[0] = Py::Object(this); // reference to this instance, set at getattr()
        t[1] = d->methods[n]; // the first index used for faster access
        t[2] = Py::String(n); // the name of the method
        t.increment_reference_count(); // the PyCFunction_New shoukd take care of removing our ref...
        return Py::Object(PyCFunction_New( &d->proxymethod->ext_meth_def, t.ptr() ), true);
    }

    // look if the attribute is a property
    if(d->properties.contains(n) && d->object) {
        QMetaProperty property = d->properties[n];

        #ifdef QROSS_PYTHON_EXTENSION_GETATTR_DEBUG
            qrossdebug( QString("PythonExtension::getattr name='%1' is a property: type=%2 valid=%3 readable=%4 scriptable=%5 writable=%6 user=%7 usertype=%8")
                        .arg(n).arg(property.typeName()).arg(property.isValid())
                        .arg(property.isReadable()).arg(property.isScriptable(d->object)).arg(property.isWritable())
                        .arg(property.isUser(d->object)).arg(property.userType())
            );
        #endif

        if(! property.isReadable()) {
            Py::AttributeError( ::QString("Attribute \"%1\" is not readable.").arg(n).toLatin1().constData() );
            return Py::None();
        }

        return PythonType<QVariant>::toPyObject( property.read(d->object) );
    }

    // look if the attribute is an enumerator
    if(d->enumerations.contains(n)) {
        return Py::Int(d->enumerations[n]);
    }

    // look if it's a dynamic property
    if(d->object && d->object->dynamicPropertyNames().contains(n)) {
        return PythonType<QVariant>::toPyObject( d->object->property(n) );
    }

    // finally redirect the unhandled attribute-request...
    //return Py::PythonExtension<PythonExtension>::getattr_methods(n);
    return Py::PythonExtension<PythonExtension>::getattr(n);
}

int PythonExtension::setattr(const char* n, const Py::Object& value)
{
    // look if the attribute is a property
    if(d->properties.contains(n) && d->object) {
        QMetaProperty property = d->properties[n];

        #ifdef QROSS_PYTHON_EXTENSION_SETATTR_DEBUG
            qrossdebug( QString("PythonExtension::setattr name='%1' is a property: type=%2 valid=%3 readable=%4 scriptable=%5 writable=%6 usertype=%7")
                .arg(n).arg(property.typeName()).arg(property.isValid())
                .arg(property.isReadable()).arg(property.isScriptable(d->object)).arg(property.isWritable())
                .arg(property.isUser(d->object)).arg(property.userType())
            );
        #endif

        if(! property.isWritable()) {
            Py::AttributeError( ::QString("Attribute \"%1\" is not writable.").arg(n).toLatin1().constData() );
            return -1; // indicate error
        }

        QVariant v = PythonType<QVariant>::toVariant(value);
        if(! property.write(d->object, v)) {
            Py::AttributeError( ::QString("Setting attribute \"%1\" failed.").arg(n).toLatin1().constData() );
            return -1; // indicate error
        }
        #ifdef QROSS_PYTHON_EXTENSION_SETATTR_DEBUG
            qrossdebug( QString("PythonExtension::setattr name='%1' value='%2'").arg(n).arg(v.toString()) );
        #endif
        return 0; // indicate success
    }

    // finally redirect the unhandled attribute-request...
    return Py::PythonExtension<PythonExtension>::setattr(n, value);
}

int PythonExtension::compare(const Py::Object& other)
{
    if(Py::PythonExtension<PythonExtension>::check( other )) {
        Py::ExtensionObject<PythonExtension> extobj( other );
        PythonExtension* extension = extobj.extensionObject();
        QObject* obj = extension->object();
        //qrossdebug( QString("PythonExtension::compare this.name='%1' other.name='%2' other.pyobject='%3'").arg(d->object ? d->object->objectName() : "NULL").arg(obj ? obj->objectName() : "NULL").arg(other.as_string().c_str()) );
        //Q_ASSERT( obj );
        //Q_ASSERT( object() );
        return obj == object() ? 0 : ( obj > object() ? -1 : 1 );
    }
    PyErr_SetObject(PyExc_TypeError, other.ptr());
    return -1;
}

long PythonExtension::hash()
{
    return long( (QObject*) d->object );
}

/* objectName is a property anyway and therefore already accessible
Py::Object PythonExtension::getObjectName(const Py::Tuple&)
{
    return PythonType<QString>::toPyObject( d->object->objectName() );
}
*/

Py::Object PythonExtension::getClassName(const Py::Tuple&)
{
    return PythonType<QString>::toPyObject( d->object->metaObject()->className() );
}

Py::Object PythonExtension::getSignalNames(const Py::Tuple&)
{
    Py::List list;
    const QMetaObject* metaobject = d->object->metaObject();
    const int count = metaobject->methodCount();
    for(int i = 0; i < count; ++i) {
        QMetaMethod m = metaobject->method(i);
        if( m.methodType() == QMetaMethod::Signal)
        {
#if QT_VERSION < 0x050000
            const QByteArray signature = m.signature();
#else
            const QByteArray signature = m.methodSignature();
#endif
            list.append( Py::String(signature) );
        }
    }
    return list;
}

Py::Object PythonExtension::getSlotNames(const Py::Tuple&)
{
    Py::List list;
    const QMetaObject* metaobject = d->object->metaObject();
    const int count = metaobject->methodCount();
    for(int i = 0; i < count; ++i) {
        QMetaMethod m = metaobject->method(i);
        if( m.methodType() == QMetaMethod::Slot)
        {
#if QT_VERSION < 0x050000
            const QByteArray signature = m.signature();
#else
            const QByteArray signature = m.methodSignature();
#endif
            list.append( Py::String(signature) );
        }
    }
    return list;
}

Py::Object PythonExtension::getPropertyNames(const Py::Tuple&)
{
    Py::List list;
    const QMetaObject* metaobject = d->object->metaObject();
    const int count = metaobject->propertyCount();
    for(int i = 0; i < count; ++i)
        list.append( Py::String(metaobject->property(i).name()) );
    return list;
}

Py::Object PythonExtension::getProperty(const Py::Tuple& args)
{
    if( args.size() != 1 ) {
        Py::TypeError("Expected the propertyname as argument.");
        return Py::None();
    }
    return PythonType<QVariant>::toPyObject( d->object->property(
        PythonType<QByteArray>::toVariant(args[0]).constData()
    ) );
}

Py::Object PythonExtension::setProperty(const Py::Tuple& args)
{
    if( args.size() != 2 ) {
        Py::TypeError("Expected the propertyname and the value as arguments.");
        return Py::None();
    }
    return PythonType<bool>::toPyObject( d->object->setProperty(
        PythonType<QByteArray>::toVariant(args[0]).constData(),
        PythonType<QVariant>::toVariant(args[1])
    ) );
}

Py::Object PythonExtension::toPointer(const Py::Tuple&)
{
    QObject* obj = d->object;
    PyObject* qobjectptr = PyLong_FromVoidPtr( (void*) obj );
    //PyObject* o = Py_BuildValue ("N", mw);
    return Py::asObject( qobjectptr );
    //PythonPyQtExtension* pyqtextension = new PythonPyQtExtension(self, args);
    //return pyqtextension;
}

/*
Py::Object PythonExtension::fromPointer(fromPointer(const Py::Tuple&)
{
    QObject* object = dynamic_cast< QObject* >(PyLong_AsVoidPtr( args[0] ));
}
*/

Py::Object PythonExtension::doConnect(const Py::Tuple& args)
{
    #ifdef QROSS_PYTHON_EXTENSION_CONNECT_DEBUG
        qrossdebug( QString("PythonExtension::doConnect" ) );
        for(uint i = 0; i < args.size(); ++i)
            try {
                QVariant v = PythonType<QVariant>::toVariant( args[i] );
                qrossdebug( QString("  Argument index=%1 variant.toString=%2 variant.typeName=%3").arg(i).arg(v.toString()).arg(v.typeName()) );
            }
            catch(Py::Exception& e) { // may happen e.g. on "function" types
                PyTypeObject *type = (PyTypeObject*) args[i].type().ptr();
                qrossdebug( QString("  Argument index=%1 tp_name=%2").arg(i).arg(type->tp_name) );
                e.clear();
            }
    #endif

    if( args.size() < 2 ) {
        Py::TypeError("Expected at least 2 arguments.");
        return PythonType<bool>::toPyObject(false);
    }

    uint idx; // next argument to check
    QObject* sender; // the sender object
    QByteArray sendersignal; // the sender signal
    if( args[0].isString() ) { // connect(signal, ...)
        //qrossdebug( QString("PythonExtension::doConnect connect(signal, ...)" ) );
        sender = d->object;
        sendersignal = PythonType<QByteArray>::toVariant( args[0] );
        idx = 1;
    }
    else { // connect(sender, signal, ...)
        //qrossdebug( QString("PythonExtension::doConnect connect(sender, signal, ...)" ) );
        Py::ExtensionObject<PythonExtension> extobj(args[0]);
        PythonExtension* extension = extobj.extensionObject();
        if(! extension) {
            Py::TypeError( ::QString("First argument needs to be a signalname or a sender-object.").toLatin1().constData() );
            return PythonType<bool>::toPyObject(false);
        }
        sender = extension->object();
        if( ! args[1].isString() ) {
            Py::TypeError( ::QString("Second argument needs to be a signalname.").toLatin1().constData() );
            return PythonType<bool>::toPyObject(false);
        }
        sendersignal = PythonType<QByteArray>::toVariant( args[1] );
        idx = 2;
        if( args.size() <= idx ) {
            Py::TypeError( ::QString("Expected at least %1 arguments.").arg(idx+1).toLatin1().constData() );
            return PythonType<bool>::toPyObject(false);
        }
    }

    QObject* receiver; // the receiver object
    QByteArray receiverslot; // the receiver slot
    if( args[idx].isCallable() ) { // connect with python function
        //qrossdebug( QString("PythonExtension::doConnect connect with python function" ) );
        Py::Callable func(args[idx]); // the callable python function
        PythonFunction* function = new PythonFunction(sender, sendersignal, func);
        d->functions.insertMulti(sendersignal, function);
        receiver = function;
        receiverslot = sendersignal;
    }
    else { // connect with receiver and slot
        //qrossdebug( QString("PythonExtension::doConnect connect with receiver and slot" ) );
        if( args[idx].isString() ) { // connect(..., slot)
            receiver = d->object;
            receiverslot = PythonType<QByteArray>::toVariant( args[idx] );
        }
        else { // connect(..., receiver, slot)
            Py::ExtensionObject<PythonExtension> extobj(args[idx]);
            PythonExtension* extension = extobj.extensionObject();
            if(! extension) {
                Py::TypeError( ::QString("Receiver argument needs to be a slotname or a receiver-object.").toLatin1().constData() );
                return PythonType<bool>::toPyObject(false);
            }
            receiver = extension->object();
            idx++;
            if( args.size() < idx ) {
                Py::TypeError( ::QString("Expected at least %1 arguments.").arg(idx+1).toLatin1().constData() );
                return PythonType<bool>::toPyObject(false);
            }
            if( ! args[idx].isString() ) {
                Py::TypeError( ::QString("Expected receiver slotname as argument %1.").arg(idx+1).toLatin1().constData() );
                return PythonType<bool>::toPyObject(false);
            }
            receiverslot = PythonType<QByteArray>::toVariant( args[idx] );
        }
    }

    // Dirty hack to replace SIGNAL() and SLOT() macros. If the user doesn't
    // defined them explicit, we assume it's wanted to connect from a signal to
    // a slot. This seems to be the most flexible solution so far...
    if( ! sendersignal.startsWith('1') && ! sendersignal.startsWith('2') )
        sendersignal.prepend('2'); // prepending 2 means SIGNAL(...)
    if( ! receiverslot.startsWith('1') && ! receiverslot.startsWith('2') )
        receiverslot.prepend('1'); // prepending 1 means SLOT(...)

    #ifdef QROSS_PYTHON_EXTENSION_CONNECT_DEBUG
        qrossdebug( QString("PythonExtension::doConnect sender=%1 signal=%2 receiver=%3 slot=%4").arg(sender->objectName()).arg(sendersignal.constData()).arg(receiver->objectName()).arg(receiverslot.constData()).toLatin1().constData() );
    #endif

    if(! QObject::connect(sender, sendersignal, receiver, receiverslot) ) {
        qrosswarning( QString("PythonExtension::doConnect Failed to connect").toLatin1().constData() );
        return PythonType<bool>::toPyObject(false);
    }
    return PythonType<bool>::toPyObject(true);
}

Py::Object PythonExtension::doDisconnect(const Py::Tuple&)
{
    //TODO
    return PythonType<bool>::toPyObject(false);
}

PyObject* PythonExtension::proxyhandler(PyObject *_self_and_name_tuple, PyObject *args)
{
    /*
    class GilState {
        public:
            GilState() { m_gilstate = PyGILState_Ensure(); } // Acquire interpreter lock
            ~GilState() { PyGILState_Release( m_gilstate ); } // Free interpreter lock
        private:
            PyGILState_STATE m_gilstate;
    };
    GilState gil;
    */

    try {
        Py::Tuple selftuple(_self_and_name_tuple);

        int methodindex = Py::Int(selftuple[1]);

        QByteArray ba = Py::String(selftuple[2]).as_string().c_str();
        const char* methodname = ba.constData();

        #ifdef QROSS_PYTHON_EXTENSION_CALL_DEBUG
            qrossdebug( QString("PythonExtension::proxyhandler methodname=%1 methodindex=%2").arg(methodname).arg(methodindex) );
        #endif

        PythonExtension *self = static_cast<PythonExtension*>( selftuple[0].ptr() );
        if( ! self->d->object ) {
            Py::RuntimeError( QString("Underlying QObject instance of method '%1' was removed.").arg(methodname).toLatin1().constData() );
            return Py_None;
        }

        Py::Tuple argstuple(args);
        const int argssize = int( argstuple.size() );
        QMetaMethod metamethod = self->d->object->metaObject()->method( methodindex );
        if(metamethod.parameterTypes().size() != argssize) {
            bool found = false;
            const int count = self->d->object->metaObject()->methodCount();
            for(++methodindex; methodindex < count; ++methodindex) {
                metamethod = self->d->object->metaObject()->method( methodindex );
#if QT_VERSION < 0x050000
                const QString signature = metamethod.signature();
#else
                const QString signature = metamethod.methodSignature();
#endif
                const QByteArray name = signature.left(signature.indexOf('(')).toLatin1();
                if(name == methodname) {
                    if(metamethod.parameterTypes().size() == argssize) {
                        found = true;
                        break;
                    }
                }
            }
            if(! found) {
                qrosswarning( QString("PythonExtension::proxyhandler The method '%1' does not expect %2 arguments.").arg(methodname).arg(argssize) );
                throw Py::TypeError( QString("Invalid number of arguments for the method %1").arg(methodname).toLatin1().constData() );
            }
        }

        #ifdef QROSS_PYTHON_EXTENSION_CALL_DEBUG
            qrossdebug( QString("PythonExtension::proxyhandler QMetaMethod idx=%1 sig=%2 tag=%3 type=%4").arg(methodindex).arg(metamethod.signature()).arg(metamethod.tag()).arg(metamethod.typeName()) );
            for(int i = 0; i < argssize; ++i) {
                QVariant v;
                try {
                    v = PythonType<QVariant>::toVariant( argstuple[i] );
                }
                catch(Py::Exception& e) {
                    v = Py::value(e).as_string().c_str();
                    e.clear();
                }
                qrossdebug( QString("  Argument index=%1 variant.toString=%2 variant.typeName=%3").arg(i).arg(v.toString()).arg(v.typeName()) );
            }
        #endif

        Py::Object pyresult;
        {
            QList<QByteArray> typelist = metamethod.parameterTypes();
            const int typelistcount = typelist.count();
            bool hasreturnvalue = strcmp(metamethod.typeName(),"") != 0;

            // exact 1 returnvalue + 0..9 arguments
            Q_ASSERT(typelistcount <= 10);
            QVarLengthArray<MetaType*> variantargs( typelistcount + 1 );
            QVarLengthArray<void*> voidstarargs( typelistcount + 1 );

            // set the return value
            if(hasreturnvalue) {
                MetaType* returntype = PythonMetaTypeFactory::create( metamethod.typeName(), Py::Object(), false /*owner*/ );
                variantargs[0] = returntype;
                voidstarargs[0] = returntype->toVoidStar();
                #ifdef QROSS_PYTHON_EXTENSION_CALL_DEBUG
                    qrossdebug( QString("PythonExtension::proxyhandler typeName=%1").arg(metamethod.typeName()) );
                #endif
            }
            else {
                variantargs[0] = 0;
                voidstarargs[0] = (void*)0;
            }

            // set the arguments
            int idx = 1;
            try {
                for(; idx <= typelistcount; ++idx) {
                    variantargs[idx] = PythonMetaTypeFactory::create( typelist[idx-1].constData(), argstuple[idx - 1], false /*owner*/ );
                    voidstarargs[idx] = variantargs[idx]->toVoidStar();
                }
            }
            catch(Py::Exception& e) {
                // Seems PythonMetaTypeFactory::create raised an exception
                // up. Clean all already allocated MetaType instances.
                for(int i = 0; i < idx; ++i)
                    delete variantargs[i];
                throw e; // re-throw exception
            }

            // call the method now
            int r = self->d->object->qt_metacall(QMetaObject::InvokeMetaMethod, methodindex, &voidstarargs[0]);
            #ifdef QROSS_PYTHON_EXTENSION_CALL_DEBUG
                qrossdebug( QString("RESULT nr=%1").arg(r) );
            #else
                Q_UNUSED(r);
            #endif

            // eval the return-value
            if(hasreturnvalue) {
                QVariant v;
                if( Qross::MetaTypeHandler* handler = Qross::Manager::self().metaTypeHandler(metamethod.typeName()) ) {
                    #ifdef QROSS_PYTHON_EXTENSION_CALL_DEBUG
                        qrossdebug( QString("Returnvalue of type '%2' has a handler").arg(metamethod.typeName()) );
                    #endif
                    void *ptr = (*reinterpret_cast<void*(*)>( variantargs[0]->toVoidStar() ));
                    v = handler->callHandler(ptr);
                }
                else {
                    v = QVariant(variantargs[0]->typeId(), variantargs[0]->toVoidStar());

                    if( ! Qross::Manager::self().strictTypesEnabled() ) {
                        if( v.type() == QVariant::Invalid && QByteArray(metamethod.typeName()).endsWith("*") ) {
                            #ifdef QROSS_PYTHON_EXTENSION_CALL_DEBUG
                                qrossdebug( QString("Returnvalue of type '%2' will be reinterpret_cast<QObject*>").arg(metamethod.typeName()) );
                            #endif
                            QObject* obj = (*reinterpret_cast<QObject*(*)>( variantargs[0]->toVoidStar() ));
                            v.setValue( (QObject*) obj );
                        }
                    }
                }
                pyresult = PythonType<QVariant>::toPyObject(v);
                #ifdef QROSS_PYTHON_EXTENSION_CALL_DEBUG
                    qrossdebug( QString("Returnvalue typeId=%1 metamethod.typename=%2 variant.toString=%3 variant.typeName=%4 pyobject=%5").arg(variantargs[0]->typeId()).arg(metamethod.typeName()).arg(v.toString()).arg(v.typeName()).arg(pyresult.as_string().c_str()) );
                #endif
            }

            // finally free the PythonVariable instances
            for(int i = 0; i <= typelistcount; ++i)
                delete variantargs[i];
        }

        pyresult.increment_reference_count(); // don't destroy PyObject* if pyresult got destroyed.
        return pyresult.ptr();
    }
    catch(Py::Exception& e) {
        QStringList trace;
        int lineno;
        PythonInterpreter::extractException(trace, lineno);
        qrosswarning( QString("PythonExtension::proxyhandler Had exception on line %1:\n%2 \n%3").arg(lineno).arg(Py::value(e).as_string().c_str()).arg(trace.join("\n")) );
        PyErr_Print(); //e.clear();
    }

    return Py_None;
}

int PythonExtension::sequence_length()
{
    return d->object->children().count();
}

Py::Object PythonExtension::sequence_concat(const Py::Object& obj)
{
    throw Py::RuntimeError( QString("Unsupported: PythonExtension::sequence_concat %1").arg(obj.as_string().c_str()).toLatin1().constData() );
}

Py::Object PythonExtension::sequence_repeat(Py_ssize_t index)
{
    // what we do here is rather evil and does not make sense at all. We assume that something
    // like "myobjinstance * 2" means, that the pointer-address should be multiplied by 2. This
    // is the case to keep backward-compatibility with SuperKaramba. In normal cases you wan't
    // use such kind of logic within your python scripts anyway + we can't guarantee that the
    // resulting number may not overflow or something like this.
    return Py::Long( long( (QObject*) d->object ) * index );
}

Py::Object PythonExtension::sequence_item(Py_ssize_t index)
{
    if(index < d->object->children().count())
        return Py::asObject(new PythonExtension( d->object->children().at(index) ));
    return Py::asObject( Py::new_reference_to( NULL ) );
}

Py::Object PythonExtension::sequence_slice(Py_ssize_t from, Py_ssize_t to)
{
    Py::List list;
    if(from >= 0) {
        const int count = d->object->children().count();
        for(int i = from; i <= to && i < count; ++i)
            list.append( Py::asObject(new PythonExtension( d->object->children().at(i) )) );
    }
    return list;
}

int PythonExtension::sequence_ass_item(Py_ssize_t index, const Py::Object& obj)
{
    throw Py::RuntimeError( QString("Unsupported: PythonExtension::sequence_ass_item %1 %2").arg(index).arg(obj.as_string().c_str()).toLatin1().constData() );
}

int PythonExtension::sequence_ass_slice(Py_ssize_t from, Py_ssize_t to, const Py::Object& obj)
{
    throw Py::RuntimeError( QString("Unsupported: PythonExtension::sequence_ass_slice %1 %2 %3").arg(from).arg(to).arg(obj.as_string().c_str()).toLatin1().constData() );
}

int PythonExtension::mapping_length()
{
    return d->object->children().count();
}

Py::Object PythonExtension::mapping_subscript(const Py::Object& obj)
{
    QString name = Py::String(obj).as_string().c_str();
    QObject* object = d->object->findChild< QObject* >( name );
    if(! object) {
        foreach(QObject* o, d->object->children()) {
            if(name == o->metaObject()->className()) {
                object = o;
                break;
            }
        }
    }
    if(object)
        return Py::asObject(new PythonExtension(object));
    return Py::asObject( Py::new_reference_to( NULL ) );
}

int PythonExtension::mapping_ass_subscript(const Py::Object& obj1, const Py::Object& obj2)
{
    throw Py::RuntimeError( QString("Unsupported: PythonExtension::mapping_ass_subscript %1 %2").arg(obj1.as_string().c_str()).arg(obj2.as_string().c_str()).toLatin1().constData() );
}

int PythonExtension::number_nonzero()
{
    #ifdef QROSS_PYTHON_EXTENSION_NUMERIC_DEBUG
        qrossdebug("PythonExtension::number_nonzero");
    #endif
    return d->object ? 1 : 0;
}

Py::Object PythonExtension::number_int()
{
    #ifdef QROSS_PYTHON_EXTENSION_NUMERIC_DEBUG
        qrossdebug("PythonExtension::number_int");
    #endif
    return Py::Int( hash() );
}

Py::Object PythonExtension::number_long()
{
    #ifdef QROSS_PYTHON_EXTENSION_NUMERIC_DEBUG
        qrossdebug("PythonExtension::number_long");
    #endif
    return Py::Long( hash() );
}

Py::Object PythonExtension::number_hex()
{
    #ifdef QROSS_PYTHON_EXTENSION_NUMERIC_DEBUG
        qrossdebug("PythonExtension::number_hex");
    #endif
    void* ptr = (QObject*) d->object;
    return Py::Object(PyString_FromFormat("%p",ptr),true);
}
