/** 
 *  This file is part of Mirrors.
 * 
 *  Copyright (C) 2008
 *  Thomas Moenicke <tm at php-qt.org>

    Mirrors is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Mirrors is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Mirrors.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SMOKEINFO_H
#define SMOKEINFO_H

#include <QTextBrowser>
#include <QDebug>

class QCompleter;

class SmokeInfo : public QTextBrowser
{
 public:
    SmokeInfo(QWidget *parent);
    void promoteCompleter(const QCompleter* c){ mCompleter = c; }

 public slots: 
     void reload();

 private:
 const QCompleter* mCompleter;

};

SmokeInfo::SmokeInfo(QWidget *parent)
{
}

void
SmokeInfo::reload()
{
    QTextBrowser::reload();
}

#endif
