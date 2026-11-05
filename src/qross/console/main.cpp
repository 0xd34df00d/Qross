/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtCore/QFileInfo>
#include "../core/manager.h"
#include "../core/script.h"

namespace
{
    enum Status
    {
        Ok = 0,
        Usage = 1,
        NoSuchFile = 2,
        NoInterpreter = 4,
        ScriptError = 5,
    };

    int runScript(const QString& path)
    {
        if (!QFileInfo::exists(path))
        {
            std::cerr << "No such script file: " << qPrintable(path) << std::endl;
            return NoSuchFile;
        }

        Qross::Script script({ .source = Qross::File { path } });
        if (script.interpreter().isEmpty())
        {
            std::cerr << "No interpreter for " << qPrintable(path) << "; available: "
                      << qPrintable(Qross::Manager::self().interpreters().join(QStringLiteral(", "))) << std::endl;
            return NoInterpreter;
        }

        if (const auto result = script.run(); !result)
        {
            std::cerr << qPrintable(result.error().toString()) << std::endl;
            return ScriptError;
        }
        return Ok;
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Syntax: " << argv[0] << " scriptfile1 [scriptfile2] ..." << std::endl;
        return Usage;
    }

    QCoreApplication app(argc, argv);
    for (int i = 1; i < argc; ++i)
        if (const int status = runScript(QString::fromLocal8Bit(argv[i])); status != Ok)
            return status;
    return Ok;
}
