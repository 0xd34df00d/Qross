/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QPointer>
#include "../core/context.h"

namespace Qross
{
    class PythonFunction;

    /**
     * Runs the code of a \a Script as a module of its own.
     *
     * Every execute() starts from a fresh module whose globals are the
     * script as \c self, the objects of the \a Manager (\c Qross among them)
     * and the objects of the script. The module is registered in
     * \c sys.modules under a name of its own, derived from the name of the
     * script, so that pickle and dataclasses find the classes it defines
     * through their \c __module__. The directory of the script file is
     * appended to \c sys.path, so that scripts can import their neighbours.
     *
     * The signal connections the code of a run makes, through connect() or
     * \a AutoConnectSignals, last until the next run or the destructor.
     *
     * Objects stay owned by C++; a wrapper of a deleted object raises
     * RuntimeError.
     */
    class PythonContext : public Context
    {
        QByteArray m_name;
        PyObject* m_module = nullptr;
        QList<QPointer<PythonFunction>> m_connections;
    public:
        PythonContext(Interpreter* interpreter, Script* script);
        ~PythonContext() override;

        /// The context whose code runs on this thread, or null outside any.
        static PythonContext* current();

        /// Makes \p context current on this thread for the scope.
        class Scope
        {
            PythonContext* const m_previous;
        public:
            explicit Scope(PythonContext* context);
            ~Scope();

            Scope(const Scope&) = delete;
            Scope& operator=(const Scope&) = delete;
        };

        /// Takes \p relay among the connections the next run and the destructor drop.
        void adopt(PythonFunction* relay);

        std::expected<void, Error> execute() override;
        std::expected<QStringList, Error> functionNames() override;
        std::expected<QVariant, Error> callFunction(const QString& name, const QVariantList& args = QVariantList()) override;
        std::expected<QVariant, Error> evaluate(const QByteArray& code) override;
    private:
        PyObject* ensureModule();
        void resetModule();
        void publish(PyObject* dict, const QString& name, QObject* object);
        void connectSignals();
    };
}
