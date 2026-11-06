/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2007 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <expected>
#include <memory>
#include <optional>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include "config.h"
#include "error.h"
#include "qrossconfig.h"

namespace Qross
{
    class Context;

    /**
     * One script: its source, its interpreter, the objects it sees and the
     * state its runs leave behind.
     *
     * A script is configured once, by its \a Config. run() executes the
     * source afresh each time, reading a \a File again, and keeps the
     * resulting state, so that call() reaches the functions the script
     * defined and evaluate() runs code among them. Objects added with
     * addObject() are seen by the next run. The objects of the \a Manager
     * are visible to every script; an object of the script with the same
     * name wins.
     *
     * Scripts see the script as \c self with the invokable methods below.
     *
     * The context is created on the thread of the first run(), call(),
     * evaluate() or functionNames(); the backends say what they allow from
     * other threads.
     */
    class QROSSCORE_EXPORT Script : public QObject
    {
        Q_OBJECT

        const Config m_config;
        PublishedObjects m_objects;
        QByteArray m_code;
        std::unique_ptr<Context> m_context;
        std::optional<Error> m_error;
    public:
        explicit Script(Config config, QObject* parent = nullptr);
        ~Script() override;

        const Config& config() const;

        /// Makes \p object visible to the next run as \p name, or as its object name.
        void addObject(QObject* object, const QString& name = {}, ObjectOptions options = {});
        void removeObject(const QString& name);
        /// The live objects of the \a Manager and of this script, the script's own replacing namesakes.
        QList<Published> publishedObjects() const;

        /// The option \p name as configured, else the backend's default, else \p fallback.
        QVariant option(const QString& name, const QVariant& fallback = {}) const;
        /// The source the last run() read, or the \a Code text.
        QByteArray code() const;

        std::expected<void, Error> run();
        std::expected<QVariant, Error> call(const QString& function, const QVariantList& arguments = {});
        std::expected<QVariant, Error> evaluate(const QByteArray& code);
        /// The error of the latest run(), call(), evaluate() or functionNames(), if it failed.
        std::optional<Error> error() const;

        /// Drops the state of the runs so far; the next use starts afresh. Must not be called from within the running script.
        void reset();
        /// The backend's state, or nullptr before the first use and after reset().
        Context* context() const;

        /// The path of a \a File source, or the name of the \a Code.
        Q_INVOKABLE QString name() const;
        /// The path of a \a File source, otherwise empty.
        Q_INVOKABLE QString file() const;
        /// The directory of a \a File source, otherwise empty.
        Q_INVOKABLE QString directory() const;
        Q_INVOKABLE QString interpreter() const;
        /// The functions the script has defined so far.
        Q_INVOKABLE QStringList functionNames();
    Q_SIGNALS:
        /// Emitted at the start of every run(); a slot may still reset() the script or add objects for it.
        void started();
        /// Emitted at the end of every run(), after error() is set.
        void finished();
    private:
        std::expected<void, Error> execute();
        std::expected<Context*, Error> ensureContext();
        std::unexpected<Error> fail(Error error);
    };
}
