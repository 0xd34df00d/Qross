/**
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

#ifndef ZEND_EXTENSION_H_
#define ZEND_EXTENSION_H_

#include <zend.h>
#include <zend_interfaces.h>
#include <php.h>
#include <php_ini.h>

#define PHP_QT_FETCH()  \
	getQtObjectFromZval(getThis()) \

#define PHP_QT_FENTRY(zend_name, name_, arg_info_, flags_)	\
    t->fname = (char*) emalloc(strlen(#zend_name)+1); \
    t->fname = #zend_name; \
    t->handler = name_; \
    t->arg_info = arg_info_; \
    t->num_args = (zend_uint) (sizeof(arg_info_)/sizeof(struct _zend_arg_info)-1); \
    t->flags = flags_; \
    t++;

#define PHP_QT_ME(classname, name, arg_info, flags)	PHP_QT_FENTRY(name, ZEND_MN(classname##_##name), arg_info, flags)

// this is needed for override return_value, see qobject_cast
#if PHP_MAJOR_VERSION >= 5
#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION <= 2)
static
#endif
    ZEND_BEGIN_ARG_INFO_EX(phpqt_cast_arginfo, 0, 1, 0)
    ZEND_END_ARG_INFO();
#endif

extern "C" {

    PHP_MINIT_FUNCTION(php_qt);
    PHP_MSHUTDOWN_FUNCTION(php_qt);
    PHP_RINIT_FUNCTION(php_qt);
    PHP_RSHUTDOWN_FUNCTION(php_qt);
    PHP_MINFO_FUNCTION(php_qt);
    PHP_FUNCTION(confirm_php_qt_compiled);	/* For testing, remove later. */
    PHP_FUNCTION(SIGNAL);
    PHP_FUNCTION(SLOT);
#undef emit
    PHP_FUNCTION(emit);
    PHP_FUNCTION(qDebug);
    PHP_FUNCTION(qWarning);
    PHP_FUNCTION(qCritical);
    PHP_FUNCTION(qAbs);
    PHP_FUNCTION(qRound);
    PHP_FUNCTION(qRound64);
    PHP_FUNCTION(qMin);
    PHP_FUNCTION(qMax);
    PHP_FUNCTION(qBound);
    PHP_FUNCTION(qPrintable);
    PHP_FUNCTION(qFuzzyCompare);
    PHP_FUNCTION(qIsNull);
    PHP_FUNCTION(qIntCast);
    PHP_FUNCTION(qVersion);
    PHP_FUNCTION(PHPQtVersion);
    PHP_FUNCTION(QiDiVersion);
    PHP_FUNCTION(qSharedBuild);
    PHP_FUNCTION(qMalloc);
    PHP_FUNCTION(qFree);
    PHP_FUNCTION(qRealloc);
    PHP_FUNCTION(qMemCopy);
    PHP_FUNCTION(qt_noop);
    PHP_FUNCTION(qt_assert);
    PHP_FUNCTION(qt_assert_x);
    PHP_FUNCTION(Q_ASSERT);
    PHP_FUNCTION(Q_ASSERT_X);
    PHP_FUNCTION(qt_check_pointer);
    PHP_FUNCTION(qobject_cast);
    PHP_FUNCTION(qstatic_cast);
    PHP_FUNCTION(tr);
    PHP_FUNCTION(check_qobject);
    PHP_FUNCTION(Q_UNUSED);
    PHP_FUNCTION(__phpqt_unittest_invoke);

    ZEND_METHOD(php_qt_generic_class, __construct);
    ZEND_METHOD(php_qt_generic_class, __destruct);
    ZEND_METHOD(php_qt_generic_class, __toString);
    ZEND_METHOD(php_qt_generic_class, emit);
    ZEND_METHOD(php_qt_generic_class, proxyMethod);
    ZEND_METHOD(php_qt_generic_class, staticProxyMethod);

} // extern "C"


#endif /*ZEND_EXTENSION_H_*/
