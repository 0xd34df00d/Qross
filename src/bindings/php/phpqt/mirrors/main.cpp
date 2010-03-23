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

#include <QApplication>
#include <QTableView>
#include <QLineEdit>
#include <QCompleter>
#include <QTreeView>

#include "ui_mirrorsMainWindow.h"
#include "smokemodel.h"
#include "qdebug.h"
#include <iostream>

using namespace std;

int
main(int argc, char** argv)
{

    QApplication app(argc, argv);

    QWidget window;
    Ui::mirrorsMainWindow ui;
    ui.setupUi(&window);

    QAbstractItemModel* model = new SmokeModel("");
    QCompleter* completer = new QCompleter(model);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    ui.searchField->setCompleter(completer);

    ui.smokeInfo->promoteCompleter(completer);
    QObject::connect(ui.searchField, SIGNAL(editingFinished()), ui.smokeInfo, SLOT(reload()) );

    QTreeView view;
    view.setModel( model );
    view.show();
    
    window.show();

    return app.exec();
}
