/***************************************************************************
 * main.cpp
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

#include "testobject.h"

// Qross
#include "../core/manager.h"
#include "../core/script.h"
#include "../core/wrapperinterface.h"

// Qt

#include <QArgument>
#include <QMetaEnum>
#include <QApplication>

// for std namespace
#include <string>
#include <iostream>

#define ERROR_OK 0
#define ERROR_HELP 1
#define ERROR_NOSUCHFILE 2
#define ERROR_OPENFAILED 3
#define ERROR_NOINTERPRETER 4
#define ERROR_EXCEPTION 5

QApplication* app = 0;

int runScriptFile(const QString& scriptfile)
{
    Qross::Script script({ .source = Qross::File { scriptfile } });
    if (script.interpreter().isEmpty())
    {
        std::cerr << "No interpreter for scriptfile: " << scriptfile.toLatin1().data() << std::endl;
        std::cerr << "Available interpreters: " << Qross::Manager::self().interpreters().join(", ").toLatin1().data() << std::endl;
        return ERROR_NOINTERPRETER;
    }

    TestObject* testobj3 = new TestObject(&script, "TestObject3");
    TestObject* testobj4 = new TestObject(&script, "TestObject4");
    script.addObject(testobj3, "TestObject3", Qross::AutoConnectSignals);
    script.addObject(testobj4, "TestObject4");

    std::cout << "Execute scriptfile " << scriptfile.toLatin1().data() << " now" << std::endl;
    const auto result = script.run();
    std::cout << "Execution of scriptfile " << scriptfile.toLatin1().data() << " done" << std::endl;

    if (!result)
    {
        std::cerr << qPrintable(result.error().toString()) << std::endl;
        return ERROR_EXCEPTION;
    }
    return ERROR_OK;
}

QVariant OtherObjectHandler(void* ptr)
{
    OtherObject* obj = static_cast<OtherObject*>(ptr);
    qDebug() << "OtherObjectHandler objectName=" << (obj ? obj->objectName() : "NULL");
    OtherObjectWrapper* wrapper = new OtherObjectWrapper(obj);
    QVariant r;
    r.setValue((QObject*)wrapper);
    return r;
}

int main(int argc, char** argv)
{
    int result = 0;

    QStringList scriptfiles;
    for (int i = 1; i < argc; i++)
        scriptfiles.append(argv[i]);

    if (scriptfiles.count() < 1)
    {
        std::cerr << "No scriptfile to execute defined. See --help" << std::endl;
        return ERROR_NOSUCHFILE;
    }

    // init
    app = new QApplication(argc, argv);
    TestObject* testobj1 = new TestObject(0, "TestObject1");
    TestObject* testobj2 = new TestObject(0, "TestObject2");
    Qross::Manager::self().addObject(testobj1);
    Qross::Manager::self().addObject(testobj2);

    Qross::Manager::self().registerMetaTypeHandler("OtherObject*", OtherObjectHandler);

    for (const QString& file : scriptfiles)
    {
        result = runScriptFile(file);
        if (result != ERROR_OK)
            break;
    }

    // finish
    delete testobj1;
    delete testobj2;
    delete app;

    return result;
}
