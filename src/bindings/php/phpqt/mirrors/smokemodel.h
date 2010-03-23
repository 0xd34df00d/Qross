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

#ifndef SMOKEMODEL_H
#define SMOKEMODEL_H

#include <QAbstractItemModel>
#include "smoke.h"

class Smoke;
class MirrorsSmokeBinding;
class QModelIndex;
class SmokeItem;
class QStringList;

class SmokeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SmokeModel(int rows, int columns, QObject *parent = 0);
    SmokeModel(const QString &data, QObject* parent = 0);
    ~SmokeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void setupSmokeData( SmokeItem* rootData );
    
 private:
    Smoke* mSmoke;    
    MirrorsSmokeBinding* mBinding;
    SmokeItem* rootItem;
};

class MirrorsSmokeBinding : public SmokeBinding
{
    
 public:
    MirrorsSmokeBinding(Smoke *s) : SmokeBinding(s)
        {   
        }
    
    virtual void deleted(Smoke::Index classId, void* ptr)
        {   
        }
    
    virtual bool callMethod(Smoke::Index method, void* QtPtr, Smoke::Stack args, bool /*isAbstract*/)
        {
            return false;   
        }
    
    virtual char *className(Smoke::Index classId)
        {
            return "";   
        }
    
    virtual ~MirrorsSmokeBinding()
        {   
        }    
}
;


#endif
