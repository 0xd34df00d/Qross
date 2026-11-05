/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "published.h"

using namespace Qross;

void PublishedObjects::add(QObject* object, const QString& name, ObjectOptions options)
{
    if (!object)
        return;
    const QString key = name.isEmpty() ? object->objectName() : name;
    remove(key);
    m_entries << Entry { object, key, options };
}

void PublishedObjects::remove(const QString& name)
{
    m_entries.removeIf([&name](const Entry& entry) { return entry.name == name; });
}

QList<Published> PublishedObjects::live() const
{
    QList<Published> result;
    for (const Entry& entry : m_entries)
        if (entry.object)
            result << Published { entry.object, entry.name, entry.options };
    return result;
}
