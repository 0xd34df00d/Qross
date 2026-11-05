/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <QtCore/QList>
#include <QtCore/QPointer>
#include "../core/context.h"

namespace Qross
{
    class PythonFunction;

    /**
     * Runs the code of a \a Script as a module of its own.
     *
     * Every execute() starts from a fresh module called \c __main__ whose
     * globals are the script as \c self, the objects of the \a Manager
     * (\c Qross among them) and the objects of the script. The directory of
     * the script file is appended to \c sys.path, so that scripts can import
     * their neighbours.
     *
     * Objects stay owned by C++; a wrapper of a deleted object raises
     * RuntimeError.
     */
    class PythonContext : public Context
    {
        PyObject* m_module = nullptr;
        QList<QPointer<PythonFunction>> m_connections;
    public:
        PythonContext(Interpreter* interpreter, Script* script);
        ~PythonContext() override;

        void execute() override;
        QStringList functionNames() override;
        QVariant callFunction(const QString& name, const QVariantList& args = QVariantList()) override;
        QVariant evaluate(const QByteArray& code) override;
    private:
        PyObject* ensureModule();
        void resetModule();
        void publish(PyObject* dict, const QString& name, QObject* object);
        void connectSignals();
    };
}
