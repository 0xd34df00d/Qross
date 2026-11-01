/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2007-2008 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <memory>
#include "../core/script.h"

class QJSValue;
class QQmlEngine;

namespace Qross
{
    /**
     * Runs the code of an \a Action in a QQmlEngine.
     *
     * Every execute() starts from a fresh engine, so a rerun sees neither the
     * globals nor the signal connections of the previous run. The engine
     * publishes the action as \c self, the objects of the \a Manager (\c Qross
     * among them) and the objects of the action, each with the keys of its
     * enums as properties.
     *
     * Published objects stay owned by C++. For everything else Qt's rule
     * applies: an object without a parent that a slot returns is owned by the
     * engine unless the host sets QJSEngine::CppOwnership on it.
     *
     * The \c qml option, on by default, imports the QtQml module first, which
     * gives QModelIndex and its relatives members such as \c row, \c column
     * and \c data(). The import registers those types for the whole process,
     * so switching the option off only spares the import once any script has
     * done it.
     */
    class JsScript : public Script
    {
        Q_OBJECT

        std::unique_ptr<QQmlEngine> m_engine;
    public:
        JsScript(Interpreter* interpreter, Action* action);
        ~JsScript() override;

        /**
         * \return the engine, created on first use and replaced by every
         * execute(). Hosts reach it through the metaobject, hence the plain
         * QObject return type.
         */
        Q_INVOKABLE QObject* engine();

        void execute() override;
        QStringList functionNames() override;
        QVariant callFunction(const QString& name, const QVariantList& args = QVariantList()) override;
        QVariant evaluate(const QByteArray& code) override;
    private:
        QQmlEngine& ensureEngine();
        QQmlEngine& createEngine();
        void publish(QJSValue& global, const QString& name, QObject* object);
        void connectSignals(QQmlEngine& engine);
    };
}
