/****************************************************************************
 **
 ** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://www.trolltech.com/products/qt/opensource.html
 **
 ** If you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://www.trolltech.com/products/qt/licensing.html or contact the
 ** sales department at sales@trolltech.com.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** Translated to C#/Qyoto by Richard Dale
 **
 ****************************************************************************/

using Qyoto;
using System;
using System.Collections.Generic;

class Pong : QObject {
    static private string SERVICE_NAME = "com.trolltech.QtDBus.PingExample";

    [Q_SLOT]
    public void Terminator() {
        Console.WriteLine("Terminator called");
        Qyoto.Qyoto.SetApplicationTerminated();
    }

    [Q_SLOT]
    public string ping(string arg)
    {
        QMetaObject.InvokeMethod(QCoreApplication.Instance(), "quit");
        return "ping(\"" + arg + "\") got called";
    }

    public static int Main(string[] args) {
        QCoreApplication app = new QCoreApplication(args);
        if (!QDBusConnection.SessionBus().IsConnected()) {
            Console.Write("Cannot connect to the D-BUS session bus.\n" +
                "To start it, run:\n" +
                "\teval `dbus-launch --auto-syntax`\n");
            return 1;
        }

        if (!QDBusConnection.SessionBus().RegisterService(SERVICE_NAME)) {
            Console.WriteLine(QDBusConnection.SessionBus().LastError().Message());        
            return 1;
        }

        Pong pong = new Pong();
        Connect(app, SIGNAL("aboutToQuit()"), pong, SLOT("Terminator()"));
        QDBusConnection.SessionBus().RegisterObject("/", pong, (int) QDBusConnection.RegisterOption.ExportAllSlots);

        return QCoreApplication.Exec();
    }
}

