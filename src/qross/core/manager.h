/***************************************************************************
 * manager.h
 * This file is part of the KDE project
 * copyright (C)2004-2007 by Sebastian Sauer (mail@dipe.org)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 ***************************************************************************/

#pragma once

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include "metatype.h"
#include "published.h"
#include "qrossconfig.h"

namespace Qross
{

    // Forward declarations.
    class Interpreter;
    class InterpreterInfo;

    /**
     * The Manager class is a singleton that provides the main entry
     * point to deal with the Qross Scripting Framework.
     *
     * Use \a Interpreter to just work with some implementated
     * interpreter like python or ruby. While \a Script implements
     * a flexible abstract container to deal with single script files.
     */
    class QROSSCORE_EXPORT Manager : public QObject
    {
        Q_OBJECT
    public:
        /**
         * Return the Manager instance. Always use this
         * function to access the Manager singleton.
         */
        static Manager& self();

        /// The names of the interpreters whose plugins were found, sorted.
        Q_INVOKABLE QStringList interpreters() const;
        /// \return whether \p name, or a former name such as "qtscript", names an interpreter.
        bool hasInterpreter(const QString& name) const;
        /// The description of the interpreter \p name, also under a former name, or nullptr.
        InterpreterInfo* interpreterInfo(const QString& name) const;
        /// The interpreter \p name, loading its plugin on first use, or nullptr.
        Interpreter* interpreter(const QString& name) const;
        /// The name of the interpreter whose file pattern matches \p file, or an empty string.
        QString interpreterNameForFile(const QString& file) const;

        /// Makes \p object visible to every script as \p name, or as its object name.
        void addObject(QObject* object, const QString& name = {}, ObjectOptions options = {});
        void removeObject(const QString& name);
        QList<Published> publishedObjects() const;

        /**
         * \return the \a MetaTypeHandler instance for custom types
         * of type \p typeName .
         *
         * \since 4.2
         */
        MetaTypeHandler* metaTypeHandler(const QByteArray& typeName) const;

        /**
         * Register a handler for custom types.
         *
         * See also the \a WrapperInterface class.
         *
         * \param typeName The custom type the handler should handle.
         * \param handler Function that should be called to handle
         * a custom type.
         *
         * \since 4.2
         */
        void registerMetaTypeHandler(const QByteArray& typeName, MetaTypeHandler::FunctionPtr* handler);

        /**
         * Register a handler for custom types.
         *
         * See also the \a WrapperInterface class.
         *
         * \param typeName The custom type the handler should handle.
         * \param handler Function that should be called to handle
         * a custom type.
         *
         * \since 4.2
         */
        void registerMetaTypeHandler(const QByteArray& typeName, MetaTypeHandler::FunctionPtr2* handler);

        /**
         * Register a handler for custom types.
         *
         * See also the \a WrapperInterface class.
         *
         * \param typeName The custom type the handler should handle.
         * \param handler Function that should be called to handle
         * a custom type.
         *
         * \since 4.2
         */
        void registerMetaTypeHandler(const QByteArray& typeName, MetaTypeHandler* handler);

        /**
         * \return whether \p typeName has a handler assigned or not.
         */
        bool hasHandlerAssigned(const QByteArray& typeName) const;

        /// Deletes the interpreters and the handlers before static destruction does it in an unknown order.
        void finalize();
    private:
        /// \internal d-pointer class.
        class Private;
        /// \internal d-pointer instance.
        Private* const d;
    public:
        /**
         * The constructor. Use \a self() to access the Manager
         * singleton instance and don't call this direct.
         */
        explicit Manager();

        /**
         * Destructor.
         */
        virtual ~Manager();
    };

}
