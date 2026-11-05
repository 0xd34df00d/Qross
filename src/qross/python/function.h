/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <QtCore/QPointer>
#include "../core/metafunction.h"

namespace Qross
{
    class PythonContext;

    /**
     * Relays a signal to a Python callable. It lives as a child of the
     * sender and belongs to the context whose code connected it, which
     * drops it with its next run; the callable runs with that context
     * current.
     */
    class PythonFunction : public MetaFunction
    {
        PyObject* m_callable;
        QPointer<PythonContext> m_owner;
    public:
        /// \p owner may be null for a relay that belongs to no context.
        PythonFunction(QObject* sender, const QMetaMethod& signal, PyObject* callable, PythonContext* owner);
        ~PythonFunction() override;

        bool matches(PyObject* callable) const;

        /// Deletes every relay, for use before the interpreter shuts down.
        static void deleteAll();
    protected:
        void callback(const QVariantList& args) override;
    };
}
