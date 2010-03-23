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

#include "context.h"

#include <zend.h>
#include <QByteArray>

Context* Context::m_Context = 0;

class Context::Private
{
public:
    Private( Context* q )
        : q( q ),
        callType( Context::MethodCall )
    {
    }

    QStack< QByteArray* > m_methodNameStack;
    QStack< zend_class_entry* > classEntryStack;
    zval* m_scope;
    zend_class_entry* m_activeCe;
    zval* m_activeScope;
    bool m_parentCall;
    Context::CallType callType;

private:
    Context* const q;
};

Context::Context() :
	d( new Private( this ) )
{}

void Context::createContext()
{
    m_Context = new Context;
}

void Context::destroyContext()
{
    delete m_Context;
}

void
Context::setActiveCe(zend_class_entry* ce)
{
    m_Context->d->classEntryStack.push( ce );
}

zend_class_entry*
Context::activeCe()
{
	return m_Context->d->classEntryStack.top();
}

void
Context::removeActiveCe()
{
	m_Context->d->classEntryStack.pop();
}

zval*
Context::activeScope()
{
    return m_Context->d->m_scope;
}

void
Context::setActiveScope(zval* zval_ptr)
{
    m_Context->d->m_scope = zval_ptr;
}

void
Context::removeActiveScope()
{
    m_Context->d->m_scope = 0;
}

void
Context::setParentCall(bool pc)
{
    m_Context->d->m_parentCall = pc;
}

bool
Context::parentCall()
{
    return m_Context->d->m_parentCall;
}

void
Context::setMethodName(const char* name)
{
    m_Context->d->m_methodNameStack.push( new QByteArray(name) );
}

void
Context::removeMethodName()
{
    m_Context->d->m_methodNameStack.pop();
}

QByteArray*
Context::methodName()
{
    return m_Context->d->m_methodNameStack.top();
}

const char*
Context::methodNameC()
{
    return m_Context->d->m_methodNameStack.top()->constData();
}

void Context::setCallType( const Context::CallType callType )
{
    m_Context->d->callType = callType;
}

const Context::CallType Context::callType()
{
    return m_Context->d->callType;
}

