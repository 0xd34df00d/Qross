/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include "../core/metafunction.h"

namespace Qross
{
    /// Relays a signal to a Python callable and lives as a child of the sender.
    class PythonFunction : public MetaFunction
    {
        PyObject* m_callable;
    public:
        PythonFunction(QObject* sender, const QMetaMethod& signal, PyObject* callable);
        ~PythonFunction() override;

        bool matches(PyObject* callable) const;

        /// Deletes every relay, for use before the interpreter shuts down.
        static void deleteAll();
    protected:
        void callback(const QVariantList& args) override;
    };
}
