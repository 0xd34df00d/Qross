/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <expected>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include "error.h"
#include "qrossconfig.h"

namespace Qross
{
    class Interpreter;
    class Script;

    /**
     * The state a backend keeps for one \a Script: an engine, a module or
     * a binding.
     *
     * A \a Script creates its context through the \a Interpreter on first
     * use and drops it on finalize(). execute() runs the code of the script
     * afresh; callFunction() and evaluate() work on what the last run left
     * behind. Each returns the error the script raised instead of a value.
     */
    class QROSSCORE_EXPORT Context : public QObject
    {
        Q_OBJECT

        Interpreter* const m_interpreter;
        Script* const m_script;
    public:
        Context(Interpreter* interpreter, Script* script);

        Interpreter* interpreter() const;
        Script* script() const;

        virtual std::expected<void, Error> execute() = 0;
        virtual QStringList functionNames() = 0;
        virtual std::expected<QVariant, Error> callFunction(const QString& name, const QVariantList& args = {}) = 0;
        virtual std::expected<QVariant, Error> evaluate(const QByteArray& code) = 0;
    };
}
