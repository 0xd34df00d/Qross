/*!
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2006 - 2009
 * Thomas Moenicke <tm at php-qt.org>
 * Katrina Niolet <katrina at niolet.name>
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

  #ifndef QTPHP_H
  #define QTPHP_H

  #include "smoke.h"
  #include <QString>

  #define PHPQT_VERSION "0.9"
  #define QIDI_VERSION "0.1"
  #define QSTRING_CLASSID -1 // QString is not in smoke
  #define COMPILE_DL_PHP_QT

  #include <php.h>

  class QMetaObject;

  #define Qnil (zval *) NULL

  void init_codec();
  zval* zstringFromQString(QString * s);

/**
  * an intermediary between php objects and related C++ objects
  */
class smokephp_object
{
public:
    smokephp_object(Smoke* smoke, const int classId, const void* ptr, const zend_class_entry* ce, zval* zval_ptr)
    :   m_allocated( false ),
        m_smoke(smoke),
        m_classId(classId),
        m_ptr(ptr),
        m_ce_ptr(ce),
        m_parent_ce_ptr(ce),
        m_zval_ptr(zval_ptr),
        m_meta(0),
        m_handle(zval_ptr->value.obj.handle)
        {
        }

    const bool allocated() { return m_allocated; }
    Smoke* smoke() { return m_smoke; }
    const int classId() { return m_classId; }
    const void* ptr() { return m_ptr; }

    void* mPtr() { return const_cast<void*>(m_ptr); } // can be modified
    const zend_class_entry* ce_ptr() { return m_ce_ptr; }
    const zend_class_entry* parent_ce_ptr() { return m_parent_ce_ptr; } //! @todo remove
    const zval* zval_ptr() { return m_zval_ptr; } //! @todo rename

    //! cached for faster qt_metacalls, signal calls
    const QMetaObject* meta() { return m_meta; }

    //! @todo maybe remove
    const zend_object_handle handle(){ return m_handle; }

    void setAllocated( bool allocated ) { m_allocated = allocated; }
    void setParentCePtr(zend_class_entry* parent_ce_ptr) { m_parent_ce_ptr = parent_ce_ptr; }
    void setMetaObject(const QMetaObject* meta) { m_meta = meta; }
    void setPtr(void* ptr) { m_ptr = ptr; }
    void setZvalPtr(zval* z){ m_zval_ptr=z; }

private:
    bool m_allocated; // true means ownership by bindings, Qt else
    Smoke *m_smoke;
    int m_classId;
    const void *m_ptr;

    const zend_class_entry *m_ce_ptr;
    const zend_class_entry *m_parent_ce_ptr;
    zval *m_zval_ptr;
    const QMetaObject* m_meta;
    const zend_object_handle m_handle;
};

  #endif
