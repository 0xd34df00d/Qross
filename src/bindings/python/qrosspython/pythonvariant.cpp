/***************************************************************************
 * pythonvariant.cpp
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

#include "pythonvariant.h"
#include "pythonextension.h"

#include <cstring>
#include <string>
#include <stdexcept>

#include <qross/core/manager.h>
#include <qross/core/wrapperinterface.h>
#include <sip.h>

#include <QWidget>
#include <QtDebug>

using namespace Qross;

namespace Qross {

    /// \internal helper class to deal with generic QList-types.
    class VoidList : public QList<void*> {
        public:
            VoidList() : QList<void*>() {}
            VoidList(QList<void*> list, const QByteArray& typeName) : QList<void*>(list), typeName(typeName) {}
            QByteArray typeName;

            static void* extractVoidStar(const Py::Object& object)
            {
                QVariant v = PythonType<QVariant>::toVariant(object);
                if( QObject* obj = qVariantCanConvert< QWidget* >(v) ? qvariant_cast< QWidget* >(v) : qVariantCanConvert< QObject* >(v) ? qvariant_cast< QObject* >(v) : 0 ) {
                    if( WrapperInterface* wrapper = dynamic_cast<WrapperInterface*>(obj) )
                        return wrapper->wrappedObject();
                    return obj;
                }
                if( void* ptr = v.value< void* >() ) {
                    return ptr;
                }
                return 0; //TODO handle other cases?!
            }

    };

}

Q_DECLARE_METATYPE(Qross::VoidList)

Py::Object PythonType<QVariant>::toPyObject(const QVariant& v)
{
    #ifdef QROSS_PYTHON_VARIANT_DEBUG
        qrossdebug( QString("PythonType<QVariant>::toPyObject variant.toString=%1 variant.typeid=%2 variant.typeName=%3").arg(v.toString()).arg(v.type()).arg(v.typeName()) );
    #endif

    switch( v.type() ) {
        case QVariant::Int:
            return PythonType<int>::toPyObject(v.toInt());
        case QVariant::UInt:
            return PythonType<uint>::toPyObject(v.toUInt());
        case QVariant::Double:
            return PythonType<double>::toPyObject(v.toDouble());
        case QVariant::Bool:
            return PythonType<bool>::toPyObject(v.toBool());
        case QVariant::LongLong:
            return PythonType<qlonglong>::toPyObject(v.toLongLong());
        case QVariant::ULongLong:
            return PythonType<qlonglong>::toPyObject(v.toULongLong());
        case QVariant::String:
            return PythonType<QString>::toPyObject(v.toString());

        case QVariant::Invalid: {
            #ifdef QROSS_PYTHON_VARIANT_DEBUG
                qrossdebug( QString("PythonType<QVariant>::toPyObject variant=%1 is QVariant::Invalid. Returning Py:None.").arg(v.toString()) );
            #endif
            //return Py::Object();
            return Py::None(); //FIXME should we fall through here?
        } break;
        case QVariant::UserType: {
            #ifdef QROSS_PYTHON_VARIANT_DEBUG
                qrossdebug( QString("PythonType<QVariant>::toPyObject variant=%1 is QVariant::UserType. Trying to cast now.").arg(v.toString()) );
            #endif
        } // fall through

        default: {
            if( strcmp(v.typeName(),"float") == 0 ) {
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonType<QVariant>::toPyObject Casting '%1' to double").arg(v.typeName()) );
                #endif
                return PythonType<double>::toPyObject(v.toDouble());
            }

            if( strcmp(v.typeName(),"Qross::VoidList") == 0 ) {
                VoidList list = v.value<VoidList>();
                Qross::MetaTypeHandler* handler = Qross::Manager::self().metaTypeHandler(list.typeName);
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonType<QVariant>::toPyObject Casting '%1' to QList<%2> with %3 items, hasHandler=%4").arg(v.typeName()).arg(list.typeName.constData()).arg(list.count()).arg(handler ? "true" : "false") );
                #endif
                QVariantList l;
                foreach(void* ptr, list) {
                    if( handler ) {
                        l << handler->callHandler(ptr);
                    }
                    else {
                        QVariant v;
                        v.setValue(ptr);
                        l << v;
                    }
                }
                return PythonType<QVariantList>::toPyObject(l);
            }

            if( qVariantCanConvert< Qross::Object::Ptr >(v) ) {
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonType<QVariant>::toPyObject Casting '%1' to Qross::Object::Ptr").arg(v.typeName()) );
                #endif
                Qross::Object::Ptr obj = v.value< Qross::Object::Ptr >();
                Qross::PythonObject* pyobj = dynamic_cast< Qross::PythonObject* >(obj.data());
                if(! obj) {
                    #ifdef QROSS_PYTHON_VARIANT_DEBUG
                        qrossdebug( QString("PythonType<QVariant>::toPyObject To Qross::PythonObject* casted '%1' is NULL").arg(v.typeName()) );
                    #endif
                    return Py::None();
                }
                return pyobj->pyObject();
            }

            if( qVariantCanConvert< QWidget* >(v) ) {
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonType<QVariant>::toPyObject Casting '%1' to QWidget").arg(v.typeName()) );
                #endif
                QWidget* widget = qvariant_cast< QWidget* >(v);
                if(! widget) {
                    #ifdef QROSS_PYTHON_VARIANT_DEBUG
                        qrossdebug( QString("PythonType<QVariant>::toPyObject To QWidget casted '%1' is NULL").arg(v.typeName()) );
                    #endif
                    return Py::None();
                }
                return Py::asObject(new PythonExtension(widget));
            }

            if( qVariantCanConvert< QObject* >(v) ) {
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonType<QVariant>::toPyObject Casting '%1' to QObject").arg(v.typeName()) );
                #endif
                QObject* obj = qvariant_cast< QObject* >(v);
                if(! obj) {
                    #ifdef QROSS_PYTHON_VARIANT_DEBUG
                        qrossdebug( QString("PythonType<QVariant>::toPyObject To QObject casted '%1' is NULL").arg(v.typeName()) );
                    #endif
                    return Py::None();
                }
                return Py::asObject(new PythonExtension(obj));
            }

            try {
#if defined(SIP_USE_PYCAPSULE)
                const sipAPIDef *sipApi = (const sipAPIDef *)PyCapsule_Import("sip._C_API", 0);
#else
                PyObject *sip_module;
                PyObject *sip_module_dict;
                PyObject *c_api;
                sip_module = PyImport_ImportModule("sip");
                if (sip_module == NULL)
                    throw std::runtime_error ("Could not import sip module.");
                sip_module_dict = PyModule_GetDict(sip_module);
                c_api = PyDict_GetItemString(sip_module_dict, "_C_API");
                if (c_api == NULL)
                    throw std::runtime_error ("Could not get C API.");
                if (!PyCObject_Check(c_api))
                    throw std::runtime_error ("Sanity checks for C API failed.");
                const sipAPIDef *sipApi = (const sipAPIDef *)PyCObject_AsVoidPtr(c_api);
#endif

                if (!sipApi)
                	qrosswarning ("PythonType<QVariant>::toPyObject() could not get C API");
                else
                {
                	QByteArray typeName (v.typeName ());
                	void *data = const_cast<void*>( v.data () );
                	if (typeName.endsWith ('*'))
                	{
                		data = *reinterpret_cast<void**> (data);
                		typeName.chop (1);
                	}
                	const sipTypeDef *type = sipApi->api_find_type( typeName.constData() );
                	if (type)
                	{
						Py::Object result( sipApi->api_convert_from_type( data, type, NULL ) );
						if (result != Py::None())
							return result;
                	}
                }
            }
            catch(Py::Exception& e) {
            	qrosswarning (QString ("PythonType<QVariant>::toPyObject() EXCEPTION: %1").arg (Py::value(e).as_string().c_str()));
            }
            catch(const std::exception& e) {
            	qrosswarning (QString ("PythonType<QVariant>::toPyObject() STD EXCEPTION: %1").arg (e.what ()));
            }

            if( qVariantCanConvert< void* >(v) ) {
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonType<QVariant>::toPyObject Casting '%1' to VoidStar").arg(v.typeName()) );
                #endif
                PyObject* voidptr = PyLong_FromVoidPtr( (void*) qvariant_cast<void*>(v) );
                return Py::asObject( voidptr );
            }

            //if(v.type() == QVariant::Invalid) return Py::None();

            #ifdef QROSS_PYTHON_VARIANT_DEBUG
                qrosswarning( QString("PythonType<QVariant>::toPyObject Not possible to convert the QVariant '%1' with type '%2' (%3) to a Py::Object.").arg(v.toString()).arg(v.typeName()).arg(v.type()) );
            #endif
            throw Py::TypeError( QString("Variant of type %1 can not be casted to a python object.").arg(v.typeName()).toLatin1().constData() );
        }
    }
}

QVariant PythonType<QVariant>::toVariant(const Py::Object& obj)
{
    #ifdef QROSS_PYTHON_VARIANT_DEBUG
        qrossdebug( QString("PythonType<QVariant>::toVariant str=%1").arg(obj.as_string().c_str()) );
    #endif

    // check for None
    if(obj == Py::None())
        return QVariant();

    PyObject* pyobj = obj.ptr();
    Q_ASSERT(pyobj);

    // check for some basic buildin types
    if( PyObject_TypeCheck(pyobj, &PyInt_Type) )
        return PythonType<int>::toVariant(obj);
    if( PyObject_TypeCheck(pyobj, &PyLong_Type) )
        return PythonType<qlonglong>::toVariant(obj);
    if( PyObject_TypeCheck(pyobj, &PyFloat_Type) )
        return PythonType<double>::toVariant(obj);
    if( PyObject_TypeCheck(pyobj, &PyBool_Type) )
        return PythonType<bool>::toVariant(obj);
    if( obj.isString() )
        return PythonType<QString>::toVariant(obj);
    if( PyObject_TypeCheck(pyobj, &PyTuple_Type) )
        return PythonType<QVariantList,Py::Tuple>::toVariant(Py::Tuple(obj));
    if( PyObject_TypeCheck(pyobj, &PyList_Type) )
        return PythonType<QVariantList,Py::List>::toVariant(Py::List(obj));
    if( PyObject_TypeCheck(pyobj, &PyDict_Type) )
        return PythonType<QVariantMap,Py::Dict>::toVariant(Py::Dict(obj.ptr()));

    // check if it's an extension
    if(PythonExtension::check(obj.ptr())) {
        Py::ExtensionObject<PythonExtension> extobj(obj);
        PythonExtension* extension = extobj.extensionObject();
        if(! extension) {
            #ifdef QROSS_PYTHON_VARIANT_DEBUG
                qrosswarning( QString("PythonType<QVariant>::toVariant Failed to determinate PythonExtension for object=%1").arg(obj.as_string().c_str()) );
            #endif
            throw Py::RuntimeError( QString("Failed to determinate PythonExtension object.").toLatin1().constData() );
        }

        const QVariant variant = qVariantFromValue( extension->object() );
        #ifdef QROSS_PYTHON_VARIANT_DEBUG
            if(extension->object())
                qrossdebug( QString("PythonType<QVariant>::toVariant QrossObject.objectName=%1 QrossObject.className=%2 QVariant.toString=%3 QVariant.typeName=%4").arg(extension->object()->objectName()).arg(extension->object()->metaObject()->className()).arg(variant.toString()).arg(variant.typeName()) );
            else
                qrossdebug( QString("PythonType<QVariant>::toVariant The PythonExtension object does not have a valid QObject") );
        #endif
        return variant;
    }

    try {
    	// get the void* pointer
        Py::Module mainmod( PyImport_AddModule( (char*)"sip" ) );
        Py::Callable func = mainmod.getDict().getItem("unwrapinstance");
        Py::Tuple arguments(1);
        arguments[0] = obj; //pyqtobject pointer
        Py::Object result = func.apply(arguments); // call the sip.unwrapinstance function
        void* ptr = PyLong_AsVoidPtr( result.ptr() );

        // get the metatype id
        QString typeString = QString::fromUtf8( Py::Object(PyObject_Type(obj.ptr()),true).repr().as_string().c_str() );
        int pos = typeString.indexOf('.', std::strlen("<class 'PyQt4.") );
        QString type = typeString.mid( pos + 1, typeString.size() - pos - 3 );
        int metaid = QMetaType::type( type.toLatin1() );

        if (metaid > 0)
        	return QVariant (metaid, ptr);
    }
    catch(Py::Exception& e) {
    	qrosswarning (QString ("PythonType<QVariant>::toVariant() EXCEPTION: %1").arg (Py::value(e).as_string().c_str()));
    }

    // This is a bit messy. We are only interested in instances here but newer Python versions don't care
    // any longer and don't really make any difference between buildin types and class-instances. To have
    // at least some kind of safety we check for the Py_TPFLAGS_HEAPTYPE flag and if defined, just put
    // the PyObject into a Qross::Object then.

    //PyTypeObject *type = (PyTypeObject*) obj.type().ptr(); // can throw a Py::TypeError
    //if( obj.isInstance() || PyClass_Check(pytype) || PyObject_TypeCheck(pyobj, &PyBaseObject_Type) ) {
    //if( PyObject_TypeCheck(pyobj, &PyBaseObject_Type) ) {
    //if(obj.ptr()->ob_type->tp_flags & Py_TPFLAGS_HEAPTYPE) {
    #ifdef QROSS_PYTHON_VARIANT_DEBUG
    qrossdebug( QString("PythonType<QVariant>::toVariant convert to Qross::PythonObject") );
    #endif
    //return new PythonType(object);
    QVariant result;
    Qross::Object::Ptr p(new Qross::PythonObject(obj));
    result.setValue(p);
    return result;
}

#if 0
Py::Object PythonType<QColor>::toPyObject(const QColor& color)
{
    #ifdef QROSS_PYTHON_VARIANT_DEBUG
        qrossdebug( QString("PythonType<QColor>::toPyObject color.name=%1").arg(color.name()) );
    #endif
qrossdebug( QString("....1") );
    Color* c = new Color(0 /*no parent*/, color);
qrossdebug( QString("....2") );
    Py::Object o = Py::asObject( new PythonExtension(c, false /*owner*/) );
qrossdebug( QString("....3") );
    return o;
}

QColor PythonType<QColor>::toVariant(const Py::Object& obj)
{
    if( PythonExtension::check(obj.ptr()) ) {
        Py::ExtensionObject<PythonExtension> extobj(obj);
        Q_ASSERT( extobj.extensionObject() );
        Color* color = dynamic_cast< Color* >( extobj.extensionObject()->object() );
        #ifdef QROSS_PYTHON_VARIANT_DEBUG
            qrossdebug( QString("PythonType<QColor>::toVariant Color.name=%1").arg(color ? color->name() : "NULL") );
        #endif
        if( color ) return color->color();
    }
    PyTypeObject *type = (PyTypeObject*) obj.type().ptr();
    if( PyType_IsSubtype(type,&PyString_Type) ) {
        QString cname = PythonType<QString>::toVariant(obj);
        QColor c(cname);
        #ifdef QROSS_PYTHON_VARIANT_DEBUG
            qrossdebug( QString("PythonType<QColor>::toVariant string=%1 color.name=%2").arg(cname).arg(c.name()) );
        #endif
        return c;
    }
    if( type == &PyTuple_Type || type == &PyList_Type ) {
        Py::Tuple t(obj);
        if( t.size() >= 3 ) {
            bool f = ( ((PyTypeObject*)(t[0].type().ptr())) == &PyFloat_Type );
            int r = f ? int(PythonType<double>::toVariant(t[0]) * 255.0) : PythonType<int>::toVariant(t[0]);
            int g = f ? int(PythonType<double>::toVariant(t[1]) * 255.0) : PythonType<int>::toVariant(t[1]);
            int b = f ? int(PythonType<double>::toVariant(t[2]) * 255.0) : PythonType<int>::toVariant(t[2]);
            int a = (t.size() >= 4) ? ( f ? int(PythonType<double>::toVariant(t[3]) * 255.0) : PythonType<int>::toVariant(t[3]) ) : 255;
            QColor c(r,g,b,a);
            #ifdef QROSS_PYTHON_VARIANT_DEBUG
                qrossdebug( QString("PythonType<QColor>::toVariant Tuple QColor.name=%1").arg(c.name()) );
            #endif
            return c;
        }
    }
    #ifdef QROSS_PYTHON_VARIANT_DEBUG
        qrossdebug( QString("PythonType<QColor>::toVariant empty QColor()") );
    #endif
    return QColor();
}
#endif

class MetaTypeNoDoubleVoidStar : public MetaTypeVoidStar
{
	public:
		MetaTypeNoDoubleVoidStar(int typeId, void* ptr, bool owner) : MetaTypeVoidStar(typeId, ptr, owner) {
		}
		virtual void* toVoidStar() { return m_ptr; }
};

MetaType* PythonMetaTypeFactory::create(const char* typeName, const Py::Object& object, bool owner)
{
    int typeId = QVariant::nameToType(typeName);

    #ifdef QROSS_PYTHON_VARIANT_DEBUG
        qrossdebug( QString("PythonMetaTypeFactory::create typeName=%1 metatype.id=%2 variant.id=%3 object=%4").arg(typeName).arg(QMetaType::type(typeName)).arg(typeId).arg(object.as_string().c_str()) );
    #endif

    switch(typeId) {
        case QVariant::Int:
            return new PythonMetaTypeVariant<int>(object);
        case QVariant::UInt:
            return new PythonMetaTypeVariant<uint>(object);
        case QVariant::Double:
            return new PythonMetaTypeVariant<double>(object);
        case QVariant::Bool:
            return new PythonMetaTypeVariant<bool>(object);

        case QVariant::ByteArray:
            return new PythonMetaTypeVariant<QByteArray>(object);
        case QVariant::String:
            return new PythonMetaTypeVariant<QString>(object);

        case QVariant::StringList:
            return new PythonMetaTypeVariant<QStringList>(object);
        case QVariant::Map:
            return new PythonMetaTypeVariant<QVariantMap>(object);
        case QVariant::List:
            return new PythonMetaTypeVariant<QVariantList>(object);

        case QVariant::LongLong:
            return new PythonMetaTypeVariant<qlonglong>(object);
        case QVariant::ULongLong:
            return new PythonMetaTypeVariant<qulonglong>(object);

        case QVariant::Size:
            return new PythonMetaTypeVariant<QSize>(object);
        case QVariant::SizeF:
            return new PythonMetaTypeVariant<QSizeF>(object);
        case QVariant::Point:
            return new PythonMetaTypeVariant<QPoint>(object);
        case QVariant::PointF:
            return new PythonMetaTypeVariant<QPointF>(object);
        case QVariant::Rect:
            return new PythonMetaTypeVariant<QRect>(object);
        case QVariant::RectF:
            return new PythonMetaTypeVariant<QRectF>(object);

        case QVariant::Color:
            return new PythonMetaTypeVariant<QColor>(object);
        case QVariant::Url:
            return new PythonMetaTypeVariant<QUrl>(object);

        case QVariant::Date:
            return new PythonMetaTypeVariant<QDate>(object);
        case QVariant::Time:
            return new PythonMetaTypeVariant<QTime>(object);
        case QVariant::DateTime:
            return new PythonMetaTypeVariant<QDateTime>(object);

        case QVariant::Invalid: // fall through
        case QVariant::UserType: // fall through
        default: {
            if(Py::PythonExtension<PythonExtension>::check( object )) {
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonMetaTypeFactory::create Py::Object '%1' with typename '%2' is a PythonExtension object").arg(object.as_string().c_str()).arg(typeName) );
                #endif

                Py::ExtensionObject<PythonExtension> extobj(object);
                PythonExtension* extension = extobj.extensionObject();
                QObject* obj = extension->object();
                if( ! obj )
                    throw Py::RuntimeError( QString("Underlying QObject instance of the PythonExtension was removed.").toLatin1().constData() );
                if( WrapperInterface* wrapper = dynamic_cast<WrapperInterface*>(obj) )
                    return new MetaTypeNoDoubleVoidStar( typeId, wrapper->wrappedObject(), owner );
                return new MetaTypeVoidStar( typeId, obj, owner );
            }

            /*
            //if( metaid == QMetaType::QObjectStar )
            if( metaid == QMetaType::QWidgetStar ) {
                if( qVariantCanConvert< QWidget* >(v) ) {
                    QWidget* widget = qvariant_cast< QWidget* >(v);
                    return new MetaTypeVoidStar( metaid, widget, false );
                }
            }
            */

            // handle custom types within a QList by converting the list of pointers into a QList<void*>
            QByteArray tn(typeName);
            if( tn.startsWith("QList<") && tn.endsWith("*>") ) {
                QByteArray itemTypeName = tn.mid(6, tn.length()-7);
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrosswarning( QString("PythonMetaTypeFactory::create Convert Py::Object '%1' to QList<void*> with typeName='%2' and itemTypeName='%3'").arg(object.as_string().c_str()).arg(typeName).arg(itemTypeName.constData()) );
                #endif
                QList<void*> list;
                if( object.isTuple() ) {
                    Py::Tuple t(object);
                    for(uint i = 0; i < t.size(); ++i)
                        if( void *ptr = VoidList::extractVoidStar(t[i]) )
                            list << ptr;
                }
                else if( object.isList() ) {
                    Py::List l(object);
                    for(uint i = 0; i < l.length(); ++i)
                        if( void *ptr = VoidList::extractVoidStar(l[i]) )
                            list << ptr;
                }
                return new Qross::MetaTypeImpl< VoidList >(VoidList(list, itemTypeName));
            }

            int metaid = QMetaType::type(typeName);
            if( metaid > 0 ) {
                switch(metaid) {
                    case QMetaType::QObjectStar: // fall through
                    case QMetaType::QWidgetStar: {
                        #ifdef QROSS_PYTHON_VARIANT_DEBUG
                            Py::Object pyobjtype( PyObject_Type(object.ptr()), true /* owner */ );
                            const QString pyobjtypename( pyobjtype.repr().as_string().c_str() );
                            qrossdebug( QString("PythonMetaTypeFactory::create Py::Object is %1").arg(pyobjtypename) );
                        #endif
                        if( object.hasAttr("metaObject") ) {
                            // It seems the best way to determinate a PyQt4/PyKDE4 QObject/QWidget is by
                            // just looking if the passed in PyObject has a metaObject-attribute. That
                            // way we are sure to also catch classes that inheritate from such PyQt
                            // widgets. So, if the PyObject has such an attribute we try to use the
                            // with PyQt together delivered sip.unwrapinstance() function to fetch
                            // the QObject/QWidget-pointer.
                            try {
                                Py::Module mainmod( PyImport_AddModule( (char*)"sip" ) );
                                Py::Callable func = mainmod.getDict().getItem("unwrapinstance");
                                Py::Tuple arguments(1);
                                arguments[0] = object; //pyqtobject pointer
                                Py::Object result = func.apply(arguments); // call the sip.unwrapinstance function
                                void* ptr = PyLong_AsVoidPtr( result.ptr() ); // the result is a void* pointer to our QObject/QWidget instance
                                QObject* obj = 0;
                                switch(metaid) {
                                    case QMetaType::QObjectStar: {
                                        obj = static_cast<QObject*>(ptr);
                                    } break;
                                    case QMetaType::QWidgetStar: {
                                        obj = static_cast<QWidget*>(ptr);
                                    } break;
                                    default:
                                        break;
                                }
                                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                                    qrossdebug(QString("PythonMetaTypeFactory::create class=%1 ptr=%2").arg(obj ? obj->metaObject()->className() : "NULL").arg(long(ptr)));
                                #endif
                                return new MetaTypeVoidStar( metaid, obj, false /*owner*/ );
                            }
                            catch(Py::Exception& e) {
                                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                                    qrossdebug(QString("PythonMetaTypeFactory::create EXCEPTION %1").arg(Py::value(e).as_string().c_str()));
                                #endif
                            }
                        }
                        #ifdef QROSS_PYTHON_VARIANT_DEBUG
                            qrossdebug( QString("PythonMetaTypeFactory::create Py::Object isNone. Create empty type '%1'").arg(metaid) );
                        #endif
                        void* ptr = 0; //QMetaType::construct(metaid, 0);
                        return new MetaTypeVoidStar( metaid, ptr, false /*owner*/ );
                    } break;
                    default:
                    	return new MetaTypeVoidStar( metaid, QMetaType::construct( metaid ), false );
                        break;
                }

                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonMetaTypeFactory::create Py::Object is typeName=%1 metaid=%2").arg(typeName).arg(metaid) );
                #endif

                // this is a dirty hack to downcast KUrl's to QUrl's
                // without the need to link against kdelibs.
                if( strcmp(typeName,"KUrl") == 0 ) {
                    return new PythonMetaTypeVariant<QUrl>(object);
                }
            }

            // still no success. So, let's try to guess the content...
            QVariant v = PythonType<QVariant>::toVariant(object);
            if( qVariantCanConvert< Qross::Object::Ptr >(v) ) {
                #ifdef QROSS_PYTHON_VARIANT_DEBUG
                    qrossdebug( QString("PythonType<QVariant>::toPyObject Casting '%1' to Qross::Object::Ptr").arg(v.typeName()) );
                #endif
                if( Qross::Object::Ptr ptr = v.value< Qross::Object::Ptr >() )
                    return new MetaTypeVariant<Qross::Object::Ptr>(ptr);
            }

            #ifdef QROSS_PYTHON_VARIANT_DEBUG
                qrosswarning( QString("PythonMetaTypeFactory::create Convert Py::Object '%1' to QVariant v.toString='%2' v.typeName='%3' typeName='%4' typeId='%5'").arg(object.as_string().c_str()).arg(v.toString()).arg(v.typeName()).arg(typeName).arg(typeId) );
            #endif
            return new Qross::MetaTypeVariant< QVariant >( v );
        } break;
    }
}

