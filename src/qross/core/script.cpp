/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "script.h"
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include "context.h"
#include "interpreter.h"
#include "manager.h"
#include "wrapperinterface.h"

using namespace Qross;

namespace
{
    Config resolve(Config config)
    {
        const auto* const file = std::get_if<File>(&config.source);
        if (file && config.interpreter.isEmpty())
            config.interpreter = Manager::self().interpreterNameForFile(file->path);
        return config;
    }
}

Script::Script(Config config, QObject* parent)
    : QObject(parent)
    , m_config(resolve(std::move(config)))
{
    setObjectName(name());
    if (const auto* const code = std::get_if<Code>(&m_config.source))
        m_code = code->text;
    for (const Published& published : m_config.objects)
        addObject(published.object, published.name, published.options);
}

Script::~Script() = default;

const Config& Script::config() const
{
    return m_config;
}

void Script::addObject(QObject* object, const QString& name, ObjectOptions options)
{
    m_objects.add(object, name, options);
}

void Script::removeObject(const QString& name)
{
    m_objects.remove(name);
}

QList<Published> Script::publishedObjects() const
{
    QList<Published> result = Manager::self().publishedObjects();
    for (const Published& own : m_objects.live())
    {
        result.removeIf([&own](const Published& published) { return published.name == own.name; });
        result << own;
    }
    return result;
}

QVariant Script::option(const QString& name, const QVariant& fallback) const
{
    if (const auto it = m_config.options.constFind(name); it != m_config.options.constEnd())
        return *it;
    const InterpreterInfo* const info = Manager::self().interpreterInfo(m_config.interpreter);
    return info ? info->optionValue(name, fallback) : fallback;
}

QByteArray Script::code() const
{
    return m_code;
}

std::unexpected<Error> Script::fail(Error error)
{
    m_error = std::move(error);
    return std::unexpected(*m_error);
}

std::expected<Context*, Error> Script::ensureContext()
{
    if (m_context)
        return m_context.get();

    InterpreterInfo* const info = Manager::self().interpreterInfo(m_config.interpreter);
    if (!info)
        return std::unexpected(Error { QStringLiteral("No such interpreter \"%1\"").arg(m_config.interpreter) });
    for (const QString& name : m_config.options.keys())
        if (!info->hasOption(name))
            return std::unexpected(Error { QStringLiteral("No such option \"%1\" for interpreter \"%2\"").arg(name, m_config.interpreter) });
    Interpreter* const interpreter = info->interpreter();
    if (!interpreter)
        return std::unexpected(Error { QStringLiteral("Failed to load interpreter \"%1\"").arg(m_config.interpreter) });

    auto context = interpreter->createContext(this);
    if (!context)
        return std::unexpected(context.error());
    m_context = std::move(*context);
    return m_context.get();
}

std::expected<void, Error> Script::run()
{
    m_error.reset();
    Q_EMIT started();
    const auto result = execute();
    if (!result)
        m_error = result.error();
    Q_EMIT finished();
    return result;
}

std::expected<void, Error> Script::execute()
{
    if (const auto* const file = std::get_if<File>(&m_config.source))
    {
        QFile source(file->path);
        if (!source.open(QIODevice::ReadOnly))
            return std::unexpected(Error { QStringLiteral("Cannot read \"%1\": %2").arg(file->path, source.errorString()) });
        m_code = source.readAll();
    }
    return ensureContext().and_then([](Context* context) { return context->execute(); });
}

std::expected<QVariant, Error> Script::call(const QString& function, const QVariantList& arguments)
{
    m_error.reset();
    const auto context = ensureContext();
    if (!context)
        return fail(context.error());
    auto result = (*context)->callFunction(function, arguments);
    if (!result)
        m_error = result.error();
    return result;
}

std::expected<QVariant, Error> Script::evaluate(const QByteArray& code)
{
    m_error.reset();
    const auto context = ensureContext();
    if (!context)
        return fail(context.error());
    auto result = (*context)->evaluate(code);
    if (!result)
        m_error = result.error();
    return result;
}

std::optional<Error> Script::error() const
{
    return m_error;
}

void Script::reset()
{
    m_context.reset();
    m_error.reset();
}

Context* Script::context() const
{
    return m_context.get();
}

QString Script::name() const
{
    if (const auto* const file = std::get_if<File>(&m_config.source))
        return file->path;
    return std::get<Code>(m_config.source).name;
}

QString Script::file() const
{
    const auto* const file = std::get_if<File>(&m_config.source);
    return file ? file->path : QString();
}

QString Script::directory() const
{
    const auto* const file = std::get_if<File>(&m_config.source);
    return file ? QFileInfo(file->path).absolutePath() : QString();
}

QString Script::interpreter() const
{
    return m_config.interpreter;
}

QStringList Script::functionNames()
{
    m_error.reset();
    const auto names = ensureContext().and_then([](Context* context) { return context->functionNames(); });
    if (!names)
    {
        m_error = names.error();
        return {};
    }
    return *names;
}

WrapperInterface::~WrapperInterface() = default;
