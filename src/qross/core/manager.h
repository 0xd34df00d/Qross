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

#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QObject>

#include "qrossconfig.h"
#include "childreninterface.h"
#include "metatype.h"

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
     * interpreter like python or ruby. While \a Action implements
     * a flexible abstract container to deal with single script files.
     */
    class QROSSCORE_EXPORT Manager
        : public QObject
        , public ChildrenInterface
    {
        Q_OBJECT
    public:
        /**
         * Return the Manager instance. Always use this
         * function to access the Manager singleton.
         */
        static Manager& self();

        /**
         * \return a map with \a InterpreterInfo* instances
         * used to describe interpreters.
         */
        QHash<QString, InterpreterInfo*> interpreterInfos() const;

        /**
         * \return true if there exists an interpreter with the
         * name \p interpretername else false. A former name of an
         * interpreter, such as "qtscript" for "javascript", counts too.
         */
        bool hasInterpreterInfo(const QString& interpretername) const;

        /**
         * \return the \a InterpreterInfo* matching to the defined
         * \p interpretername or NULL if there does not exists such
         * a interpreter.
         */
        InterpreterInfo* interpreterInfo(const QString& interpretername) const;

        /**
         * Return the name of the \a Interpreter that feels responsible
         * for the defined \p file .
         *
         * \param file The filename we should try to determinate the
         * interpretername for.
         * \return The name of the \a Interpreter which will be used
         * to execute the file or QString() if we failed to determinate
         * a matching interpreter for the file.
         */
        const QString interpreternameForFile(const QString& file);

        /**
         * Return the \a Interpreter instance defined by
         * the interpretername.
         *
         * \param interpretername The name of the interpreter.
         * e.g. "python" or "javascript".
         * \return The Interpreter instance or NULL if there does not exists
         * an interpreter with such an interpretername.
         */
        Interpreter* interpreter(const QString& interpretername) const;

        /**
         * Allows to free and finalize the interpreters before
         * static cleanup of singleton instances takes place.
         */
        void finalize();

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
    public Q_SLOTS:

        /**
         * \return a list of names of all supported scripting interpreters.
         * The list may contain for example "python", "ruby" and "javascript" depending
         * on what interpreter-plugins are installed.
         */
        QStringList interpreters() const;

        void addQObject(QObject* obj, const QString& name = QString());
        QObject* qobject(const QString& name) const;
        QStringList qobjectNames() const;
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

Q_DECLARE_METATYPE(Qross::Manager*)
