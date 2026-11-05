/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include "errorinterface.h"
#include "qrossconfig.h"

namespace Qross
{
    class Interpreter;
    class Action;

    /**
     * The state a backend keeps for one \a Action: an engine, a module or
     * a binding.
     *
     * An \a Action creates its context through the \a Interpreter on first
     * use and drops it on finalize(). execute() runs the code of the action
     * afresh; callFunction() and evaluate() work on what the last run left
     * behind.
     */
    class QROSSCORE_EXPORT Context
        : public QObject
        , public ErrorInterface
    {
        Q_OBJECT

        Interpreter* const m_interpreter;
        Action* const m_action;
    public:
        Context(Interpreter* interpreter, Action* action);

        Interpreter* interpreter() const;
        Action* action() const;

        virtual void execute() = 0;
        virtual QStringList functionNames() = 0;
        virtual QVariant callFunction(const QString& name, const QVariantList& args = {}) = 0;
        virtual QVariant evaluate(const QByteArray& code) = 0;
    };
}
