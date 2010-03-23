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

#ifndef CONTEXT_H
#define CONTEXT_H

#include <QStack>
class QByteArray;
#include "zend.h"

/*!
 * API to access to some context settings
 */

class Context
{
    static Context* m_Context;

    Context();
    ~Context(){};

public:
    enum CallType
    {
        ConstructorCall = 1,
        MethodCall,
	StaticMethodCall,
        VirtualMethodCall,
        SignalCall,
        SlotCall
    };

    static void createContext();
    static void destroyContext();

    static zend_class_entry* activeCe();
    static zval* activeScope();
    static bool parentCall();
    static void removeMethodName();
    static QByteArray* methodName();
    static const char* methodNameC();

    static void setActiveCe(zend_class_entry* activeCePtr);
    static void setActiveScope(zval* zval_ptr);
    static void removeActiveScope();
    static void setParentCall(bool pc);
    static void setMethodName(const char* name);

    static void removeActiveCe();

    static void setCallType( const CallType callType );
    static const CallType callType();

private:
    class Private;
    Context::Private *d;
};

#endif

