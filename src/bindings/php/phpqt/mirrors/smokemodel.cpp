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

#include "smokemodel.h"
#include "SmokeItem.h"

#include <QDebug>
#include <QModelIndex>
#include <QStringList>

extern Smoke* qt_Smoke;
extern void init_qt_Smoke();

SmokeModel::SmokeModel(int rows, int columns, QObject *parent)
    : QAbstractItemModel(parent)
{
}

SmokeModel::SmokeModel(const QString &data, QObject *parent)
{
    if (qt_Smoke != 0L)
        qFatal("could not initialize smoke");
    init_qt_Smoke();
    mSmoke = qt_Smoke;
    mBinding = new MirrorsSmokeBinding(qt_Smoke);

    QList<QVariant> rootData;
    rootData << "Qt Root";
    rootItem = new SmokeItem( rootData );
    
    setupSmokeData( rootItem );
}


SmokeModel::~SmokeModel()
{
}

QModelIndex 
SmokeModel::index(int row, int column, const QModelIndex &parent) const
{
    SmokeItem* parentItem;
    
    if (!parent.isValid())
        parentItem = rootItem;
    else
    	parentItem = static_cast<SmokeItem*>( parent.internalPointer() );

    SmokeItem* childItem = parentItem->child( row );

    if( childItem )
    	return createIndex(row, column, childItem);
    else
    	return QModelIndex();
}

QModelIndex 
SmokeModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int 
SmokeModel::rowCount(const QModelIndex &parent) const
{
    return mSmoke->numClasses + mSmoke->numMethods;
}

int 
SmokeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant 
SmokeModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() )
    	return QVariant();

    if( role == Qt::DisplayRole || role == Qt::EditRole )
    {
    	SmokeItem* item = static_cast<SmokeItem*>(index.internalPointer());
    	return item->data( index.column() );
    } else 
    	return QVariant();
}

void SmokeModel::setupSmokeData( SmokeItem* rootItem )
{
    Smoke::Class* sc = mSmoke->classes;
    const Smoke::Class* numClasses = sc + mSmoke->numClasses;
    int classId = 0;
    
    for( sc; sc < numClasses; sc++, classId++ )
    {
    	QList<QVariant> classItemData;
    	classItemData << sc->className;
    	    	
    	SmokeItem* classItem = new SmokeItem(classItemData, rootItem);
    	rootItem->appendChild( classItem );
    	
    	// find related methods
        Smoke::Method* sm = mSmoke->methods;
        const Smoke::Method* numMethods = sm + mSmoke->numMethods;
        for( sm; sm < numMethods; sm++ )
        {
        	if( sm->classId == classId ){
        		QList<QVariant> methodItemData;
        		methodItemData << mSmoke->methodNames[ sm->name ];// << sm->method << sc->className;
        	
        		SmokeItem* methodItem = new SmokeItem( methodItemData, classItem );
        		classItem->appendChild( methodItem );        		
        		rootItem->appendChild( methodItem );
        	}
        }
    }
}

#include "smokemodel.moc"
