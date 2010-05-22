/***************************************************************************
 * main.cpp
 * This file is part of the KDE project
 * copyright (C)2006 by Sebastian Sauer (mail@dipe.org)
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

#include <QFile>
#include <QScriptEngine>
#include <QLibraryInfo>
#include <QDebug>
#include <QStringList>
#include <QApplication>
#include <QPluginLoader>

QApplication* app = 0;

bool runScriptFile(QScriptEngine* engine, const QString& scriptfile)
{
    // Read the scriptfile
    QFile f(scriptfile);
    if(! f.exists()) {
        qWarning() << "No such scriptfile:" << scriptfile;
        return false;
    }
    if(! f.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open scriptfile:" << scriptfile;
        return false;
    }
    QByteArray scriptcode = f.readAll();
    f.close();

    // Execute the javascript code.
    qDebug() << "Execute scriptfile:" << scriptfile;
    QScriptValue v = engine->evaluate(scriptcode);
    qDebug() << "Execute done. Result:" << v.toString();

    return true;
}

int main(int argc, char **argv)
{
    QStringList files;
    for(int i = 1; i < argc; ++i)
        files << argv[i];

    // If no options are defined.
    if(files.count() < 1) {
        qWarning() << "Syntax:" << argv[0] << "scriptfile1 [scriptfile2] [scriptfile3] ...";
        return -1;
    }

    app = new QApplication(argc, argv);
    QScriptEngine* engine = new QScriptEngine();
    QScriptValue global = engine->globalObject();

    app->addLibraryPath("/home/d34df00d/Programming/qross/build/qts");
    qDebug()<<"QLibraryInfo::PluginsPath="<<QLibraryInfo::location(QLibraryInfo::PluginsPath);

    qDebug () << engine->availableExtensions();

    engine->importExtension("qross").toString();

    foreach(const QString &file, files)
        runScriptFile(engine, file);

    delete engine;
    delete app;
    return 0;
}
