/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

#include <variant>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QVariantMap>
#include "published.h"

namespace Qross
{
    /// A script file, read again by every run; its directory joins the module path of the language.
    struct File
    {
        QString path;
    };

    /// Script code given directly, with the name that errors and traces show for it.
    struct Code
    {
        QByteArray text;
        QString name = QStringLiteral("<script>");
    };

    /// Everything a \a Script is made of.
    struct Config
    {
        std::variant<File, Code> source;
        /// Empty means the interpreter that claims the extension of the file.
        QString interpreter = {};
        /// Overrides of the backend's options, such as \c qml for JavaScript.
        QVariantMap options = {};
        QList<Published> objects = {};
    };
}
