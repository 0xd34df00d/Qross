/**
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2008 - 2009
 * Thomas Moenicke <tm at php-qt.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QtTest/QtTest>
#include <QPaintEvent>
#include <QSlider>
#include <iostream>

#include "phpqt_internals.h"
#include "unittests.h"

#include <zend.h>
#include "smokephp.h"


extern Smoke* qt_Smoke;

TestPHPQt::TestPHPQt( SmokeBinding* binding, zval* z )
  : _binding(binding), _z(z), _smoke( qt_Smoke )
{
  std::cout << "setting up unittests" << std::endl;
}

TestPHPQt::~TestPHPQt()
{
}

/*
 * test case for invoking virtual methods
 * QWidget::paintEvent( QPaintEvent* x1 );
 *
 * smoke code:
 * virtual void paintEvent(QPaintEvent* x1)
 * {
 *       Smoke::StackItem x[2];
 *       x[1].s_class = (void*)x1;
 *       if(this->_binding->callMethod(18732, (void*)this, x)) return;
 *       this->QWidget::paintEvent(x1);
 * }
 */

void TestPHPQt::InvokeVirtualMethod()
{
  QPaintEvent x1( QRect( 0,0,10,10 ) );
  void* p = PHPQt::getQtObjectFromZval( _z );

  // QWidget paintEvent
  Smoke::ModuleIndex method = _smoke->findMethod( "QWidget", "paintEvent#" );
  Smoke::Index index = _smoke->methodMaps[ method.index ].method;

  Smoke::StackItem x[2];
  x[1].s_class = (void*) &x1;
  for(int i = 0; i < 80; i++){
    _binding->callMethod( index, p, x );
  }
  std::cout << std::endl;
}

void TestPHPQt::InvokeSlot()
{
  QSlider* slider = static_cast< QSlider* > ( PHPQt::getQtObjectFromZval( _z ) );

  zval* arg;
  MAKE_STD_ZVAL( arg );
  ZVAL_LONG( arg, 7 );
  zval** args = (zval**) safe_emalloc( sizeof( zval* ), 1, 0 );
  args[0] = arg;

  // last argument is just a dummy here
  PHPQt::callPHPMethod( _z, QString("setupConnections").toLatin1().constData(), 0, args );

  for(int i = 0; i < 80; i++ )
    {
      PHPQt::callPHPMethod( _z, QString("invokeSetValue").toLatin1().constData(), 1, args );
    }
  std::cout << std::endl;
  FREE_ZVAL( arg );
  efree( args );
}
