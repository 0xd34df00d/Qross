/***************************************************************************
 * action.cpp
 * This file is part of the KDE project
 * copyright (C)2004-2006 by Sebastian Sauer (mail@dipe.org)
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

#include "action.h"
#include "interpreter.h"
#include "script.h"
#include "manager.h"
#include "wrapperinterface.h"

#include <QFile>
#include <QFileInfo>

using namespace Qross;

namespace Qross
{

    /// \internal d-pointer class.
    class Action::Private
    {
    public:
        /**
         * The \a Script instance the \a Action uses if initialized. It will
         * be NULL as long as we didn't initialized it what will be done on
         * demand.
         */
        Script* script;

        /**
         * The scripting code.
         */
        QByteArray code;

        /**
         * The name of the interpreter. This could be something
         * like for example "python" for the python binding.
         */
        QString interpretername;

        /**
         * The name of the scriptfile that should be executed. Those
         * scriptfile will be readed and the content will be used to
         * set the scripting code and, if not defined, the used
         * interpreter.
         */
        QString scriptfile;

        /**
         * Map of options that overwritte the \a InterpreterInfo::Option::Map
         * standard options.
         */
        QMap<QString, QVariant> options;

        Private()
            : script(0)
        {
        }
    };

}

enum InitOptions
{
    Enable = 1
};
void static init(Action* th, const QString& name, int options = 0)
{
    th->setEnabled(options & Enable);
    th->setObjectName(name);
#ifdef QROSS_ACTION_DEBUG
    qrossdebug(QString("Action::Action() Ctor name='%1'").arg(th->objectName()));
#endif
    QObject::connect(th, SIGNAL(triggered(bool)), th, SLOT(slotTriggered()));
}

Action::Action(QObject* parent, const QString& name)
    : QAction(parent)
    , ChildrenInterface()
    , ErrorInterface()
    , d(new Private())
{
    init(this, name);
}

Action::Action(QObject* parent, const QUrl& url)
    : QAction(parent)
    , ChildrenInterface()
    , ErrorInterface()
    , d(new Private())
{
    init(this, url.path(), Enable);
    QFileInfo fi(url.toLocalFile());
    setText(fi.fileName());
    setFile(url.toLocalFile());
}

Action::~Action()
{
#ifdef QROSS_ACTION_DEBUG
    qrossdebug(QString("Action::~Action() Dtor name='%1'").arg(objectName()));
#endif
    finalize();
    delete d;
}

Qross::Script* Action::script() const
{
    return d->script;
}

QString Action::name() const
{
    return objectName();
}

QByteArray Action::code() const
{
    return d->code;
}

void Action::setCode(const QByteArray& code)
{
    if (d->code != code)
    {
        finalize();
        d->code = code;
    }
}

QString Action::interpreter() const
{
    return d->interpretername;
}

void Action::setInterpreter(const QString& interpretername)
{
    if (d->interpretername != interpretername)
    {
        finalize();
        d->interpretername = interpretername;
        setEnabled(Manager::self().hasInterpreterInfo(interpretername));
        if (!isEnabled())
            qrosswarning("Action::setInterpreter: interpreter not found: " + interpretername);
    }
}

QString Action::file() const
{
    return d->scriptfile;
}

bool Action::setFile(const QString& scriptfile)
{
    if (d->scriptfile != scriptfile)
    {
        finalize();
        if (scriptfile.isNull())
        {
            if (!d->scriptfile.isNull())
                d->interpretername.clear();
            d->scriptfile.clear();
        }
        else
        {
            d->scriptfile = scriptfile;
            d->interpretername = Manager::self().interpreternameForFile(scriptfile);
            if (d->interpretername.isNull())
                return false;
        }
    }
    return true;
}

QString Action::currentPath() const
{
    return file().isEmpty() ? QString() : QFileInfo(file()).absolutePath(); // obey Qt docs and don't cheat
}

QVariantMap Action::options() const
{
    return d->options;
}

void Action::addQObject(QObject* obj, const QString& name)
{
    this->addObject(obj, name);
}

QObject* Action::qobject(const QString& name) const
{
    return this->object(name);
}

QStringList Action::qobjectNames() const
{
    return this->objects().keys();
}

QVariant Action::option(const QString& name, const QVariant& defaultvalue)
{
    if (d->options.contains(name))
        return d->options[name];
    InterpreterInfo* info = Manager::self().interpreterInfo(d->interpretername);
    return info ? info->optionValue(name, defaultvalue) : defaultvalue;
}

bool Action::setOption(const QString& name, const QVariant& value)
{
    InterpreterInfo* info = Manager::self().interpreterInfo(d->interpretername);
    if (info)
    {
        if (info->hasOption(name))
        {
            d->options.insert(name, value);
            return true;
        }
        else
            qrosswarning(QString("Qross::Action::setOption(%1, %2): No such option").arg(name).arg(value.toString()));
    }
    else
        qrosswarning(QString("Qross::Action::setOption(%1, %2): No such interpreterinfo").arg(name).arg(value.toString()));
    return false;
}

QStringList Action::functionNames()
{
    if (!d->script)
    {
        if (!initialize())
            return QStringList();
    }
    return d->script->functionNames();
}

QVariant Action::callFunction(const QString& name, const QVariantList& args)
{
    if (!d->script)
    {
        if (!initialize())
            return QVariant();
    }
    return d->script->callFunction(name, args);
}

QVariant Action::evaluate(const QByteArray& code)
{
    if (!d->script)
    {
        if (!initialize())
            return QVariant();
    }
    return d->script->evaluate(code);
}

bool Action::initialize()
{
    finalize();

    if (!d->scriptfile.isNull())
    {
        QFile f(d->scriptfile);
        if (!f.exists())
        {
            setError(tr("Scriptfile \"%1\" does not exist.").arg(d->scriptfile));
            return false;
        }
        if (d->interpretername.isNull())
        {
            setError(tr("Failed to determine interpreter for scriptfile \"%1\"").arg(d->scriptfile));
            return false;
        }
        if (!f.open(QIODevice::ReadOnly))
        {
            setError(tr("Failed to open scriptfile \"%1\"").arg(d->scriptfile));
            return false;
        }
        d->code = f.readAll();
        f.close();
    }

    Interpreter* interpreter = Manager::self().interpreter(d->interpretername);
    if (!interpreter)
    {
        InterpreterInfo* info = Manager::self().interpreterInfo(d->interpretername);
        if (info)
            setError(tr("Failed to load interpreter \"%1\"").arg(d->interpretername));
        else
            setError(tr("No such interpreter \"%1\"").arg(d->interpretername));
        return false;
    }

    d->script = interpreter->createScript(this);
    if (!d->script)
    {
        setError(tr("Failed to create script for interpreter \"%1\"").arg(d->interpretername));
        return false;
    }

    if (d->script->hadError())
    {
        setError(d->script);
        finalize();
        return false;
    }

    clearError(); // clear old exception
    return true;
}

void Action::finalize()
{
    delete d->script;
    d->script = 0;
}

bool Action::isFinalized() const
{
    return d->script == 0;
}

void Action::slotTriggered()
{
#ifdef QROSS_ACTION_DEBUG
    qrossdebug(QString("Action::slotTriggered() name=%1").arg(objectName()));
#endif

    Q_EMIT started(this);

    if (!d->script)
    {
        if (!initialize())
            Q_ASSERT(hadError());
    }

    if (hadError())
    {
#ifdef QROSS_ACTION_DEBUG
        qrossdebug(QString("Action::slotTriggered() on init, errorMessage=%2").arg(errorMessage()));
#endif
    }
    else
    {
        d->script->execute();
        if (d->script->hadError())
        {
#ifdef QROSS_ACTION_DEBUG
            qrossdebug(QString("Action::slotTriggered() after exec, errorMessage=%2").arg(errorMessage()));
#endif
            setError(d->script);
            // emit finished(this);
            finalize();
            // return;
        }
    }

    Q_EMIT finished(this);
}

// --------

// interface files
WrapperInterface::~WrapperInterface()
{
}
