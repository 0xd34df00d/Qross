/* This file is part of the KDE project
 *
 * Copyright (C) 2000 Simon Hausmann <hausmann@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <dcopclient.h>
#include <dcopobject.h>
#include <kapplication.h>
#include <kstdaction.h>
#include <kaction.h>
#include <kmainwindow.h>
#include <kprocess.h>
#include <kparts/mainwindow.h>
#include <kdebug.h>
#include "xp_notepad_factory.h"

extern "C"
{
  void *init_libxp_notepadpart()
  {
      return new XP_NotepadFactory( true );
  }
};


KParts::Part *XP_NotepadFactory::createPartObject( QWidget *parentWidget, const char *widgetName, QObject *parent, const char *name, const char *className, const QStringList & )
{
    return new XP_NotepadPart( parentWidget, widgetName, parent, name );
}

XP_NotepadPart::XP_NotepadPart(QWidget *parentWidget, const char *widgetName,
	                       QObject *parent, const char *name)
	: XPartHost_KPart(parentWidget, widgetName, parent, name)
{
    m_partProcess = new KProcess;
    *m_partProcess << "xnotepard"
		   << kapp->dcopClient()->appId() << objId();
    m_partProcess->start();

    qDebug("---->>>>>> enter loop");
    kapp->enter_loop();
    qDebug("----<<<<<< left loop");
}

XP_NotepadPart::~XP_NotepadPart()
{
    delete m_partProcess;
}

void XP_NotepadPart::createActions( const QCString &xmlActions )
{
    XPartHost_KPart::createActions( xmlActions );
    qDebug("----<<<<<< exit loop");
    kapp->exit_loop();
}

#include "xp_notepad_factory.moc"
