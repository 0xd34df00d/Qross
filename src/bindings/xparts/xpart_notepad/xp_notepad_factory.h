/* This file is part of the KDE project
 *
 * Copyright (C) 2000 Simon Hausmann <hausmann@kde.org>
 * Copyright (C) 2001 Philippe Fremy <pfremy@chez.com>
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
#ifndef __xp_notepad_factory_h__
#define __xp_notepad_factory_h__

#include <kparts/factory.h>
#include <qptrlist.h>
#include <kurl.h>
#include "xparthost_kpart.h"

class KInstance;
class KAboutData;
class KHTMLSettings;
class KHTMLPart;
class KProcess;

class XP_NotepadFactory : public KParts::Factory
{
  Q_OBJECT
public:
  XP_NotepadFactory( bool clone = false ) {}
  virtual ~XP_NotepadFactory() {}

  virtual KParts::Part *createPartObject( QWidget *parentWidget, const char *widgetName, QObject *parent, const char *name, const char *className, const QStringList &args );

};



class XP_NotepadPart : public XPartHost_KPart
{
    Q_OBJECT

public:
    XP_NotepadPart(QWidget *parentWidget, const char *widgetName,
	           QObject *parent, const char *name);
    virtual ~XP_NotepadPart();

    virtual void createActions( const QCString &xmlActions );
private:
    KProcess *m_partProcess;
};

#endif
