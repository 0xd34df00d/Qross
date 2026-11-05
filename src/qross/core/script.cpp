/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "script.h"
#include "interpreter.h"
#include "context.h"
#include "manager.h"
#include "wrapperinterface.h"

#include <QFile>
#include <QFileInfo>

using namespace Qross;

namespace Qross
{

    /// \internal d-pointer class.
    class Script::Private
    {
    public:
        /**
         * The \a Context instance the \a Script uses if initialized. It will
         * be NULL as long as we didn't initialized it what will be done on
         * demand.
         */
        Context* context;

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
            : context(0)
        {
        }
    };

}

enum InitOptions
{
    Enable = 1
};
void static init(Script* th, const QString& name, int options = 0)
{
    th->setEnabled(options & Enable);
    th->setObjectName(name);
#ifdef QROSS_ACTION_DEBUG
    qrossdebug(QString("Script::Script() Ctor name='%1'").arg(th->objectName()));
#endif
    QObject::connect(th, SIGNAL(triggered(bool)), th, SLOT(slotTriggered()));
}

Script::Script(QObject* parent, const QString& name)
    : QAction(parent)
    , ChildrenInterface()
    , ErrorInterface()
    , d(new Private())
{
    init(this, name);
}

Script::Script(QObject* parent, const QUrl& url)
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

Script::~Script()
{
#ifdef QROSS_ACTION_DEBUG
    qrossdebug(QString("Script::~Script() Dtor name='%1'").arg(objectName()));
#endif
    finalize();
    delete d;
}

Context* Script::context() const
{
    return d->context;
}

QString Script::name() const
{
    return objectName();
}

QByteArray Script::code() const
{
    return d->code;
}

void Script::setCode(const QByteArray& code)
{
    if (d->code != code)
    {
        finalize();
        d->code = code;
    }
}

QString Script::interpreter() const
{
    return d->interpretername;
}

void Script::setInterpreter(const QString& interpretername)
{
    if (d->interpretername != interpretername)
    {
        finalize();
        d->interpretername = interpretername;
        setEnabled(Manager::self().hasInterpreterInfo(interpretername));
        if (!isEnabled())
            qrosswarning("Script::setInterpreter: interpreter not found: " + interpretername);
    }
}

QString Script::file() const
{
    return d->scriptfile;
}

bool Script::setFile(const QString& scriptfile)
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

QString Script::currentPath() const
{
    return file().isEmpty() ? QString() : QFileInfo(file()).absolutePath(); // obey Qt docs and don't cheat
}

QVariantMap Script::options() const
{
    return d->options;
}

void Script::addQObject(QObject* obj, const QString& name)
{
    this->addObject(obj, name);
}

QObject* Script::qobject(const QString& name) const
{
    return this->object(name);
}

QStringList Script::qobjectNames() const
{
    return this->objects().keys();
}

QVariant Script::option(const QString& name, const QVariant& defaultvalue)
{
    if (d->options.contains(name))
        return d->options[name];
    InterpreterInfo* info = Manager::self().interpreterInfo(d->interpretername);
    return info ? info->optionValue(name, defaultvalue) : defaultvalue;
}

bool Script::setOption(const QString& name, const QVariant& value)
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
            qrosswarning(QString("Qross::Script::setOption(%1, %2): No such option").arg(name).arg(value.toString()));
    }
    else
        qrosswarning(QString("Qross::Script::setOption(%1, %2): No such interpreterinfo").arg(name).arg(value.toString()));
    return false;
}

QStringList Script::functionNames()
{
    if (!d->context)
    {
        if (!initialize())
            return QStringList();
    }
    return d->context->functionNames();
}

QVariant Script::callFunction(const QString& name, const QVariantList& args)
{
    if (!d->context)
    {
        if (!initialize())
            return QVariant();
    }
    return d->context->callFunction(name, args);
}

QVariant Script::evaluate(const QByteArray& code)
{
    if (!d->context)
    {
        if (!initialize())
            return QVariant();
    }
    return d->context->evaluate(code);
}

bool Script::initialize()
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

    d->context = interpreter->createContext(this);
    if (!d->context)
    {
        setError(tr("Failed to create script for interpreter \"%1\"").arg(d->interpretername));
        return false;
    }

    if (d->context->hadError())
    {
        setError(d->context);
        finalize();
        return false;
    }

    clearError(); // clear old exception
    return true;
}

void Script::finalize()
{
    delete d->context;
    d->context = 0;
}

bool Script::isFinalized() const
{
    return d->context == 0;
}

void Script::slotTriggered()
{
#ifdef QROSS_ACTION_DEBUG
    qrossdebug(QString("Script::slotTriggered() name=%1").arg(objectName()));
#endif

    Q_EMIT started(this);

    if (!d->context)
    {
        if (!initialize())
            Q_ASSERT(hadError());
    }

    if (hadError())
    {
#ifdef QROSS_ACTION_DEBUG
        qrossdebug(QString("Script::slotTriggered() on init, errorMessage=%2").arg(errorMessage()));
#endif
    }
    else
    {
        d->context->execute();
        if (d->context->hadError())
        {
#ifdef QROSS_ACTION_DEBUG
            qrossdebug(QString("Script::slotTriggered() after exec, errorMessage=%2").arg(errorMessage()));
#endif
            setError(d->context);
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
