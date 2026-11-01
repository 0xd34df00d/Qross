/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "function.h"
#include <QtCore/QMutex>
#include <QtCore/QSet>
#include "gil.h"
#include "interpreter.h"
#include "ref.h"
#include "variant.h"

using namespace Qross;

namespace
{
    QMutex relaysMutex;
    QSet<PythonFunction*> relays;
}

PythonFunction::PythonFunction(QObject* sender, const QMetaMethod& signal, PyObject* callable)
    : MetaFunction(sender, signal)
    , m_callable(callable)
{
    Py_INCREF(m_callable);
    setParent(sender);
    const QMutexLocker locker(&relaysMutex);
    relays.insert(this);
}

PythonFunction::~PythonFunction()
{
    {
        const QMutexLocker locker(&relaysMutex);
        relays.remove(this);
    }
    if (!Py_IsInitialized())
        return;
    const Gil gil;
    Py_DECREF(m_callable);
}

bool PythonFunction::matches(PyObject* callable) const
{
    const int equal = PyObject_RichCompareBool(m_callable, callable, Py_EQ);
    if (equal < 0)
        PyErr_Clear();
    return equal == 1;
}

void PythonFunction::deleteAll()
{
    QList<PythonFunction*> remaining;
    {
        const QMutexLocker locker(&relaysMutex);
        remaining = relays.values();
    }
    qDeleteAll(remaining);
}

void PythonFunction::callback(const QVariantList& args)
{
    const Gil gil;
    Ref arguments(PyTuple_New(args.size()));
    for (qsizetype i = 0; i < args.size(); ++i)
    {
        PyObject* const argument = toPython(args[i]);
        if (!argument)
            break;
        PyTuple_SET_ITEM(arguments.get(), i, argument);
    }
    const Ref result(PyErr_Occurred() ? nullptr : PyObject_CallObject(m_callable, arguments.get()));
    if (!result)
    {
        // Nothing awaits the result, so the error can only be logged.
        ErrorInterface log;
        storeException(log);
    }
}
