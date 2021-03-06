/***************************************************************************
 * pythonobject.cpp
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

#include "pythonobject.h"
#include "pythonextension.h"
#include "pythonvariant.h"
#include "pythoninterpreter.h"

using namespace Qross;

class PythonObject::Private
{
public:
    Private() {};
    Private(const Py::Object& object) : m_pyobject(object) {};
    const Py::Object m_pyobject;
    QStringList m_calls;
};

PythonObject::PythonObject()
    : Qross::Object()
    , d(new Private)
{
}

PythonObject::PythonObject(const Py::Object& object)
    : Qross::Object()
    , d(new Private(object))
{
    #ifdef QROSS_PYTHON_FUNCTION_DEBUG
        qrossdebug( QString("PythonObject::PythonObject() constructor") );
    #endif

    Py::List x( object.dir() );
    for(Py::Sequence::iterator i= x.begin(); i != x.end(); ++i) {
        std::string s = (*i).str();
        if(s == "__init__")
            continue;

        //if(! m_pyobject.hasAttr( (*i).str() )) continue;
        Py::Object o = d->m_pyobject.getAttr(s);

        #ifdef QROSS_PYTHON_FUNCTION_DEBUG
            QString t;
            if(o.isCallable()) t += "isCallable ";
            if(o.isDict()) t += "isDict ";
            if(o.isList()) t += "isList ";
            if(o.isMapping()) t += "isMapping ";
            if(o.isNumeric()) t += "isNumeric ";
            if(o.isSequence()) t += "isSequence ";
            if(o.isTrue()) t += "isTrue ";
            if(o.isInstance()) t += "isInstance ";
            qrossdebug( QString("PythonObject::PythonObject() method '%1' (%2)").arg( (*i).str().as_string().c_str() ).arg(t) );
        #endif

        if(o.isCallable())
            d->m_calls.append( (*i).str().as_string().c_str() );
    }
}

PythonObject::~PythonObject()
{
    #ifdef QROSS_PYTHON_FUNCTION_DEBUG
        qrossdebug( QString("PythonObject::~PythonObject() destructor") );
    #endif
    delete d;
}

QVariant PythonObject::callMethod(const QString& name, const QVariantList& args)
{
    #ifdef QROSS_PYTHON_FUNCTION_DEBUG
        qrossdebug( QString("PythonObject(%1)::call(%2) isInstance=%3").arg(d->m_pyobject.as_string().c_str()).arg(name).arg(d->m_pyobject.isInstance()) );
    #endif

    //if(d->m_pyobject.isInstance()) { // if it inherits a PyQt4 QObject/QWidget then it's not counted as instance
        try {
            Py::Callable method = d->m_pyobject.getAttr(name.toLatin1().data());
            if (!method.isCallable()) {
                qrossdebug( QString("%1 is not callable (%2).").arg(name).arg(method.str().as_string().c_str()) );
                return QVariant();
            }
            Py::Object pyresult = method.apply( PythonType<QVariantList,Py::Tuple>::toPyObject(args) );
            QVariant result = PythonType<QVariant>::toVariant(pyresult);
            #ifdef QROSS_PYTHON_FUNCTION_DEBUG
                qrossdebug( QString("PythonScript::callFunction() result=%1 variant.toString=%2 variant.typeName=%3").arg(pyresult.as_string().c_str()).arg(result.toString()).arg(result.typeName()) );
            #endif
            return result;
        }
        catch(Py::Exception& e) {
            //#ifdef QROSS_PYTHON_SCRIPT_CALLFUNC_DEBUG
                qrosswarning( QString("PythonScript::callFunction() Exception: %1").arg(Py::value(e).as_string().c_str()) );
            //#endif
            Py::Object err = Py::value(e);
            if(err.ptr() == Py_None) err = Py::type(e); // e.g. string-exceptions have there errormessage in the type-object
            QStringList trace;
            int lineno;
            PythonInterpreter::extractException(trace, lineno);
            setError(err.as_string().c_str(), trace.join("\n"), lineno);
            PyErr_Print();
        }
    //}

    return QVariant();
}

QStringList PythonObject::methodNames()
{
    return d->m_calls;
}

Py::Object PythonObject::pyObject()
{
    return d->m_pyobject;
}
