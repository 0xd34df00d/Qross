/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <Python.h>
#include <utility>

namespace Qross
{
    /// Owns one reference to a Python object; releasing it needs the interpreter lock.
    class Ref
    {
        PyObject* m_object = nullptr;
    public:
        Ref() = default;
        /// Takes over a new reference, which is null after a failed call.
        explicit Ref(PyObject* object)
            : m_object(object)
        {
        }
        Ref(const Ref& other)
            : m_object(other.m_object)
        {
            Py_XINCREF(m_object);
        }
        Ref(Ref&& other) noexcept
            : m_object(std::exchange(other.m_object, nullptr))
        {
        }
        ~Ref() { Py_XDECREF(m_object); }

        Ref& operator=(Ref other) noexcept
        {
            std::swap(m_object, other.m_object);
            return *this;
        }

        /// Adds a reference to a borrowed object.
        static Ref borrowed(PyObject* object)
        {
            Py_XINCREF(object);
            return Ref(object);
        }

        PyObject* get() const { return m_object; }
        /// Gives up ownership.
        PyObject* release() { return std::exchange(m_object, nullptr); }
        explicit operator bool() const { return m_object != nullptr; }
    };
}
