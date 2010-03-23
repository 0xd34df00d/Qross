/*!
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2006 - 2009
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

#ifndef PHPQT_INTERNALS_H
#define PHPQT_INTERNALS_H

#include "smoke.h"
#include <QtCore/qobjectdefs.h>
#include <php.h>
#include "smokephp.h"

class QString;
class smokephp_object;

namespace PHPQt
{
    /**
     * calls a PHP method
     * @param z_this_ptr    zval*
     * @param methodname
     * @param param_count
     * @param params
     * @return
     */
    zval* callPHPMethod(const zval* z_this_ptr, const char* methodname, const zend_uint param_count, zval** params);

    /**
     * checks if method exists in PHP
     * @param ce_ptr        zend class entry
     * @param methodname
     * @return true if method exists
     * @todo rename
     */
    bool methodExists(const zend_class_entry* ce_ptr, const char* methodname);

    /**
     * creates a QMetaObject
     * @param o
     * @param this_ptr
     */
    void createMetaObject(smokephp_object* o, zval* this_ptr);

    /**
     * Calls signals and slots.
     *
     * We have two types of Signals and Slots: those already defined in Qt and those the user defines
     * in user space. All of them can be combined arbitrarily. The following cases exist:
     * - User space Signals are called via the proxyMethod and the EmitSignal class, using emit()
     * - Qt Signals are called via qt_methodcall
     * - User space Slots are called via qt_metacall after the related signal was emitted, since PHP-Qt puts them into the QMetaObject
     * - Qt Slots are called here via qt_metacall
     * Algorithm:
     * - check if the method is defined in the user space class, if so it is a user space slot and can be called
     * - if it is not defined in the user space class, then it can be either a Qt Slot or a Signal
     *   - if the signature has a slot index in the meta object which is smaller than the offset, it is obviously a Qt slot
     *   - if the signature has a slot index in the meta object that is greater or equal than the offset, it is a user space slot (which
     *     should already be found by the line above)
     *   - if the slot index is -1, it is a Signal
     *     - if signals id is smaller than offset, it is a C++ one
     *     - if it is greater or equal, it is a user space one
     *
     * @param o     mapping object
     * @param args  Smoke stack of arguments
     * @return true if succeeded, false means smoke will call it again on the parent
     */
    bool qt_metacall(smokephp_object* o, Smoke::Stack args);

    /**
     * checks if the class represented by a Smoke::Index is derived from a QObject
     * @param classId
     * @return
     */
    bool isQObject( const Smoke::Index classId );

    /**
     * Prepares the name of the method: it appends certain characters that indicate the argument types.
     * This way the correct call can be found by Smoke.
     * The munging works this way:
     *  $ is a plain scalar
     *  # is an object
     *  ? is a non-scalar (reference to array or hash, undef)
     * @param args
     * @param argc
     */
    void prepareMethodName(zval** args, const int argc);

    /**
     * creates the signature of a method for Signal calls, based on given php information
     * @param argc          number of arguments
     * @param argv          argument stack
     * @param mocStack      moc stack
     * @return              signature
     */
    QByteArray getSignature(int argc, zval **argv, MocArgument* mocStack);

    /**
     * searches for the corresponding Smoke Index by a given class and method name
     * @param c         class name
     * @param m         mangeled method name
     * @param argc      number of arguments
     * @param args      PHP argument stack
     * @return          unambigous method ID
     */
    Smoke::Index findMethod(const char* className, const char* methodName, const int argc, zval** args);

    /**
     * calls a C++ method
     * @param obj
     * @param method
     * @param qargs
     */
    void callCppMethod(void *obj, Smoke::Index method, Smoke::Stack qargs);

    /**
     * initializes Smoke and creates an instance of the binding
     */
    void init();

    /**
     * translates a Qt stack into a Moc stack
     * @param smoke     pointer to smoke
     * @param _a        C++ stack
     * @param qargs     list of C++ argument names
     * @return
     */
    QList<MocArgument*> QtToMoc(Smoke* smoke, void** _a, const QList<QByteArray> qargs);

    Smoke* smoke();
    SmokeBinding* binding();

    typedef short Index;

    /**
     * finds the real methodname since it might be lowercased by the php engine
     * @param methodName
     * @return
     */
    const char* findRealMethodName(const char* methodName);

    /**
     * checks for operator
     * @todo implement operators
     * @param fname
     * @return ?
     */
    const char* checkForOperator(const char* fname);

    // mapping

    /**
     * finds the pointer to the corresponding C++ object of a given PHP value
     * @param this_ptr
     * @return pointer to C++ object
     * @todo rename
     */
    void* getQtObjectFromZval(const zval* this_ptr);

    /**
     * finds the mapping object of a given php value
     * @param this_ptr
     * @return mapping object
     * @todo rename
     */
    smokephp_object* getSmokePHPObjectFromZval(const zval* this_ptr);

    /**
     * finds the mapping object of a given Qt pointer
     * @param QtPtr
     * @return
     * @todo rename
     */
    smokephp_object* getSmokePHPObjectFromQt(const void* QtPtr);

    /**
     * sets mapping of php and C++ objects
     * @param o
     * @todo rename
     */
    void setSmokePHPObject(smokephp_object* o);

    /**
     * checks if mapping object exists
     * @param this_ptr
     * @return true or false
     * @todo rename
     */
    bool SmokePHPObjectExists(const zval* this_ptr);

    /**
     * checks if mapping object exists
     * @param ptr
     * @return true or false
     * @todo rename
     */
    bool SmokePHPObjectExists(const void* ptr);

    /**
     * unmap
     * @param o
     * @return false if failed
     * @todo rename
     */
    bool unmapSmokePHPObject(const zval* zvalue);

    /**
     * unmap
     * @param o
     * @return
     */
    bool unmapSmokePHPObject(smokephp_object* o);

    /**
     * map php and C++ objects
     * @param handle
     * @param
     * @todo rename
     */
    void mapSmokePHPObject( const zend_object_handle handle, smokephp_object* );

    // object creation

    /**
     * does all the setup of a mapping as creating the mapping object etc
     *
     * marshall_basetypes.h marshall_to_php<SmokeClassWrapper>(Marshall *m)
     * @param zval_ptr
     * @param ptr
     * @param ce
     * @param classId
     * @return
     * @todo rename, zend specific
     */
    smokephp_object* createObject(zval* zval_ptr, const void* ptr, const zend_class_entry* ce = 0, const Smoke::Index classId = 0);

    /**
     * clones an object
     * @param zval_ptr
     * @param so
     * @param copyPtr
     * @return
     */
    smokephp_object* cloneObject(zval* zval_ptr, smokephp_object* so, const void* copyPtr);

    /**
     * ?
     * @param zval_ptr
     * @param ptr
     * @return
     * @todo remove?
     * @deprecated
     */
    smokephp_object* createOriginal(zval* zval_ptr, void* ptr);

    /**
     * create a new zval that refers to the object. This is neccessary since zvals can be freed when
     * calling virtual methods or custom slots
     * @param o
     * @todo deprecated?
     * @deprectaed
     */
    void restoreObject( smokephp_object* o );

    // debugging

    /**
     * helper for printing, also mapped to PHP
     * @see functions.h
     * @param zobject
     */
    void check_qobject(zval* zobject);

    /**
     * prints the type of a zval
     * @param type
     * @return
     * @todo rename
     */
    const QString printType(int type);

    Smoke* smoke();
}; // namespace PHPQt

#endif
