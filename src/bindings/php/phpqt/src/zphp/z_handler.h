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

#ifndef ZEND_HANDLERS_H
#define ZEND_HANDLERS_H

#include <zend_interfaces.h>

// for opcode handler
#define PHPQT_OPHANDLER_COUNT				((25 * 151) + 1)
#define EX__(element) execute_data->element
#define EX_T(offset) (*(temp_variable *)((char *) EX__(Ts) + offset))
#define ZEND_VM_CONTINUE() return 0

namespace ZProxyHandlers {
extern "C" {

    /**
     *  proxy handler for regular method calls, called by the zend engine
     * @param obj_ptr
     * @param methodName
     * @param methodName_len
     */

    union _zend_function* methodHandler(zval **obj_ptr, char* methodName, int methodName_len TSRMLS_DC);

    /*!
     *   handler for constants
     */

    int constantHandler(ZEND_OPCODE_HANDLER_ARGS);

#undef EX
#define EX(element) execute_data->element


    /*!
     *	handler for static method calls
     *  and for the parent:: statement
     *
     *  try to find a static method defined in Qt and
     *  call the staticProxyMethod handler
     *  @see ZEND_INIT_STATIC_METHOD_CALL_SPEC_CONST_HANDLER in zend_vm_execute.h
     */

    int staticMethodHandler(ZEND_OPCODE_HANDLER_ARGS);

    /*!
     *  handler for cloning objects
     */

    int cloneHandler(ZEND_OPCODE_HANDLER_ARGS);

    /*!
     *  install proxy handlers (opcode handlers)
     */

    void installProxyHandlers();

} // namespace ZProxyHandlers
}
#endif
