/***************************************************************************
 * manager.cpp
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

#include "manager.h"
#include "interpreter.h"

#include <QtCore/QObject>
#include <QtCore/QArgument>
#include <QtCore/QRegularExpression>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QLibrary>
#include <QtCore/QCoreApplication>

using namespace Qross;

namespace Qross
{

    /// @internal
    class Manager::Private
    {
    public:
        /// List of \a InterpreterInfo instances.
        QHash<QString, InterpreterInfo*> interpreterinfos;

        /// List of the interpreter names.
        QStringList interpreters;

        /// Former names of interpreters, still accepted on lookup.
        QHash<QString, QString> aliases;

        /// List with custom handlers for metatypes.
        QHash<QByteArray, MetaTypeHandler*> wrappers;

        /// The objects every script sees.
        PublishedObjects objects;
    };

}

Q_GLOBAL_STATIC(Manager, _self)

Manager& Manager::self()
{
    return *_self();
}

namespace
{
    QStringList librarySearchPaths()
    {
        QStringList paths;
        const QString env = qEnvironmentVariable("QROSS_PLUGIN_PATH");
        if (!env.isEmpty())
            paths += env.split(QDir::listSeparator(), Qt::SkipEmptyParts);
        paths += QStringLiteral(QROSS_INSTALL_LIBDIR);
        paths += QCoreApplication::libraryPaths();
        return paths;
    }

    void* loadLibrary(const char* libname, const char* functionname)
    {
        QLibrary lib;
        lib.setLoadHints(QLibrary::ExportExternalSymbolsHint);

        QStringList candidates;
        for (const QString& dir : librarySearchPaths())
            candidates << QDir(dir).filePath(QString::fromLatin1(libname));
        candidates << QString::fromLatin1(libname);

        for (const QString& candidate : candidates)
        {
            lib.setFileName(candidate);
            if (lib.load())
                break;
        }

        if (!lib.isLoaded())
        {
#ifdef QROSS_INTERPRETER_DEBUG
            qrossdebug(QString("Library '%1' not available: %2").arg(QString::fromLatin1(libname), lib.errorString()));
#endif
            return nullptr;
        }

        auto* const function = lib.resolve(functionname);
        if (!function)
        {
            qrosswarning(QString("Library '%1' does not export '%2'").arg(lib.fileName(), QString::fromLatin1(functionname)));
            return nullptr;
        }
        return reinterpret_cast<void*>(function);
    }
}

Manager::Manager()
    : QObject()
    , d(new Private())
{
    setObjectName("Qross");

#ifdef QROSS_PYTHON_LIBRARY
    if (void* funcPtr = loadLibrary(QROSS_PYTHON_LIBRARY, "qrossinterpreter"))
    {
        d->interpreterinfos.insert("python",
            new InterpreterInfo("python",
                funcPtr, // library
                "*.py", // file filter-wildcard
                QStringList() << "text/x-python" // mimetypes
                ));
    }
#endif

#ifdef QROSS_RUBY_LIBRARY
    if (void* funcPtr = loadLibrary(QROSS_RUBY_LIBRARY, "qrossinterpreter"))
    {
        d->interpreterinfos.insert("ruby",
            new InterpreterInfo("ruby",
                funcPtr, // library
                "*.rb", // file filter-wildcard
                QStringList() << "application/x-ruby" << "text/x-ruby" // mimetypes
                ));
    }
#endif

#ifdef QROSS_JAVASCRIPT_LIBRARY
    if (void* funcPtr = loadLibrary(QROSS_JAVASCRIPT_LIBRARY, "qrossinterpreter"))
    {
        d->interpreterinfos.insert("javascript",
            new InterpreterInfo("javascript",
                funcPtr, // library
                "*.js *.es", // file filter-wildcard
                QStringList() << "text/javascript" << "application/javascript" << "application/ecmascript", // mimetypes
                QVariantMap { { QStringLiteral("qml"), true } } // options
                ));
        d->aliases.insert("qtscript", "javascript");
    }
#endif

    // fill the list of supported interpreternames.
    QHash<QString, InterpreterInfo*>::Iterator it(d->interpreterinfos.begin());
    for (; it != d->interpreterinfos.end(); ++it)
        if (it.value())
            d->interpreters << it.key();
    d->interpreters.sort();

    // publish ourself.
    d->objects.add(this, QStringLiteral("Qross"));
}

Manager::~Manager()
{
    finalize();
    delete d;
}

bool Manager::hasInterpreter(const QString& name) const
{
    return interpreterInfo(name) != nullptr;
}

InterpreterInfo* Manager::interpreterInfo(const QString& name) const
{
    return d->interpreterinfos.value(d->aliases.value(name, name));
}

QString Manager::interpreterNameForFile(const QString& file) const
{
    for (QHash<QString, InterpreterInfo*>::Iterator it = d->interpreterinfos.begin(); it != d->interpreterinfos.end(); ++it)
    {
        if (!it.value())
            continue;
        for (const QString& wildcard : it.value()->wildcard().split(' ', Qt::SkipEmptyParts))
        {
            const QRegularExpression rx = QRegularExpression::fromWildcard(wildcard, Qt::CaseSensitive, QRegularExpression::NonPathWildcardConversion);
            if (rx.match(file).hasMatch())
                return it.value()->interpreterName();
        }
    }
    return QString();
}

Interpreter* Manager::interpreter(const QString& name) const
{
    InterpreterInfo* const info = interpreterInfo(name);
    if (!info)
    {
        qrosswarning(QString("No such interpreter '%1'").arg(name));
        return nullptr;
    }
    return info->interpreter();
}

void Manager::finalize()
{
    qDeleteAll(d->wrappers);
    d->wrappers.clear();

    qDeleteAll(d->interpreterinfos);
    d->interpreterinfos.clear();
}

QStringList Manager::interpreters() const
{
    return d->interpreters;
}

void Manager::addObject(QObject* object, const QString& name, ObjectOptions options)
{
    d->objects.add(object, name, options);
}

void Manager::removeObject(const QString& name)
{
    d->objects.remove(name);
}

QList<Published> Manager::publishedObjects() const
{
    return d->objects.live();
}

MetaTypeHandler* Manager::metaTypeHandler(const QByteArray& typeName) const
{
    return d->wrappers.contains(typeName) ? d->wrappers[typeName] : 0;
}

void Manager::registerMetaTypeHandler(const QByteArray& typeName, MetaTypeHandler::FunctionPtr* handler)
{
    d->wrappers.insert(typeName, new MetaTypeHandler(handler));
}

void Manager::registerMetaTypeHandler(const QByteArray& typeName, MetaTypeHandler::FunctionPtr2* handler)
{
    d->wrappers.insert(typeName, new MetaTypeHandler(handler));
}

void Manager::registerMetaTypeHandler(const QByteArray& typeName, MetaTypeHandler* handler)
{
    d->wrappers.insert(typeName, handler);
}

bool Manager::hasHandlerAssigned(const QByteArray& typeName) const
{
    return d->wrappers.contains(typeName);
}
