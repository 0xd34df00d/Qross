/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>

namespace Qross
{
    /// Holds the interpreter lock for the scope.
    class Gil
    {
        PyGILState_STATE m_state;
    public:
        Gil()
            : m_state(PyGILState_Ensure())
        {
        }
        ~Gil() { PyGILState_Release(m_state); }

        Gil(const Gil&) = delete;
        Gil& operator=(const Gil&) = delete;
    };
}
