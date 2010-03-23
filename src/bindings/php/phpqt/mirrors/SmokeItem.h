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

#ifndef SMOKEITEM_H_
#define SMOKEITEM_H_

#include <QList>
class QVariant;

class SmokeItem
{
public:
	SmokeItem( QList<QVariant> &data, SmokeItem* parent = 0 );
	virtual ~SmokeItem();
	
	void appendChild( SmokeItem* child );
	SmokeItem* child(int row);
	int childCount();
	int columnCount();
	QVariant data(int column) const;
	int row();
	SmokeItem* parent();

private:	
	class Private;
	Private* d;
};

#endif /*SMOKEITEM_H_*/
