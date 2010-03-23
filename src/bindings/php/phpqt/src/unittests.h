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

#ifndef   	UNITTESTS_H_
# define   	UNITTESTS_H_

#include <QObject>
#include <zend.h>

class SmokeBinding;
class Smoke;

class Q_DECL_EXPORT TestPHPQt : public QObject
{
  Q_OBJECT;
 public:
  explicit TestPHPQt( SmokeBinding* binding, zval* z );
  virtual ~TestPHPQt();

 private slots:
  void initTestCase(){}
  void InvokeVirtualMethod();
  void InvokeSlot();
 private:
  SmokeBinding* _binding;
  zval* _z;
  Smoke* _smoke;
};

#endif 	    /* !UNITTESTS_H_ */
