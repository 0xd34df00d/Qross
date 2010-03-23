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

#include "SmokeItem.h"

#include <QList>
#include <QVariant>

class SmokeItem::Private
{
public:
	Private( SmokeItem* qq )
	:q(qq)
	{	
		
	}
	~Private() {
		childItems.~QList<SmokeItem*>();
		itemData.~QList<QVariant>();
		delete parentItem;
	}

	QList<SmokeItem*> childItems;
	QList<QVariant> itemData;
	SmokeItem* parentItem;
	
private:
	SmokeItem* q;	
};

SmokeItem::SmokeItem( QList<QVariant> &data, SmokeItem* parent )
	: d( new Private( this ) )
{
	d->itemData = data;
	d->parentItem = parent;
}

SmokeItem::~SmokeItem()
{
	delete d;
}

void
SmokeItem::appendChild( SmokeItem* child )
{
	d->childItems.append( child );
}

SmokeItem* 
SmokeItem::child(int row)
{
	return d->childItems.value(row);
}

int 
SmokeItem::childCount()
{
	return d->childItems.count();
}

int 
SmokeItem::columnCount()
{
	return d->itemData.count();
}

QVariant 
SmokeItem::data(int column) const
{
	return d->itemData.value( column );
}

int 
SmokeItem::row()
{
	if(d->parentItem)
		return d->parentItem->d->childItems.indexOf( const_cast<SmokeItem*>(this) );
	return 0;
}

SmokeItem* 
SmokeItem::parent()
{
	return d->parentItem;
}

