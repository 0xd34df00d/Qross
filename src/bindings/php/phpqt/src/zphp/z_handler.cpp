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

#include <QString>

#include "php_qt.h"
#include "zphp/z_handler.h"
#include "context.h"
#include "phpqt_internals.h"
#include "smokephp.h"

extern "C" {
#include "ext/standard/php_string.h"
}

#include <QByteArray>

zend_object_handlers php_qt_handler;
zend_object_handlers zend_orig_handler;
int (*originalConstantMethodHandler)(ZEND_OPCODE_HANDLER_ARGS);
int (*originalCloneSpecCvHandler)(ZEND_OPCODE_HANDLER_ARGS);
opcode_handler_t *phpqt_original_opcode_handlers;

#if PHP_MAJOR_VERSION > 5 || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION > 2)
user_opcode_handler_t phpqt_opcode_handlers[PHPQT_OPHANDLER_COUNT];
#else
opcode_handler_t phpqt_opcode_handlers[PHPQT_OPHANDLER_COUNT];
#endif

extern "C" {

    union _zend_function* ZProxyHandlers::methodHandler(zval **obj_ptr, char* methodName, int methodName_len TSRMLS_DC)
    {
        //! - check if method is implemented in PHP
        union _zend_function *fbc;
        QByteArray lcMethodName( methodName );
        zend_object *zobj = zend_objects_get_address( *obj_ptr TSRMLS_CC );
        if ( zend_hash_find( &zobj->ce->function_table, lcMethodName.toLower().data(), methodName_len+1, (void **)&fbc ) != FAILURE )
            if( fbc->common.fn_flags & ZEND_ACC_PROTECTED )
                if( PHPQt::smoke()->idMethodName( methodName ).index > 0)
                    fbc->common.fn_flags = ZEND_ACC_PUBLIC;

        //! - try with the original handler
        fbc = zend_orig_handler.get_method( obj_ptr, methodName, methodName_len );
        Context::setActiveScope( *obj_ptr ); // it might go through staticProxy for parent:: calls
        if(!fbc)
        {
            Context::setMethodName( methodName );
            //! - call proxyMethod if it is a Qt object (original handler didn't find a function)
            fbc = zend_orig_handler.get_method(obj_ptr, "proxyMethod", 11);
        }

        return fbc;
    }

    int ZProxyHandlers::constantHandler(ZEND_OPCODE_HANDLER_ARGS)
    {
        zend_op *opline = EX__(opline);
        zend_class_entry *ce = NULL;
        zval **value;

        if (IS_CONST == IS_UNUSED) {
            if (!zend_get_constant(opline->op2.u.constant.value.str.val, opline->op2.u.constant.value.str.len, &EX_T(opline->result.u.var).tmp_var TSRMLS_CC)) {
                zend_error(E_NOTICE, "Use of undefined constant %s - assumed '%s'",
                        opline->op2.u.constant.value.str.val,
                        opline->op2.u.constant.value.str.val);
                EX_T(opline->result.u.var).tmp_var = opline->op2.u.constant;
                zval_copy_ctor(&EX_T(opline->result.u.var).tmp_var);
            }
            execute_data->opline++;
        }

        ce = EX_T(opline->op1.u.var).class_entry;

        if (zend_hash_find(&ce->constants_table, opline->op2.u.constant.value.str.val, opline->op2.u.constant.value.str.len+1, (void **) &value) == SUCCESS) {
            zval_update_constant(value, (void *) 1 TSRMLS_CC);
            EX_T(opline->result.u.var).tmp_var = **value;
            zval_copy_ctor(&EX_T(opline->result.u.var).tmp_var);
        } else {
            //! - enums are methods here
            Smoke::Index method = PHPQt::smoke()->findMethod(ce->name, opline->op2.u.constant.value.str.val).index;
            if(method <= 0) // smoke could not find one
                php_error(E_ERROR, "undefined class constant '%s'", opline->op2.u.constant.value.str.val);

            method = PHPQt::smoke()->methodMaps[method].method;

            //! - get the Qt value
            Smoke::Stack args = new Smoke::StackItem;
            void* dummy; // dummy here
            PHPQt::callCppMethod(dummy, method, args);

            //! - write the zend return value
            zval* return_value;
            MAKE_STD_ZVAL(return_value);
            ZVAL_LONG(return_value, args[0].s_enum);
            EX_T(opline->result.u.var).tmp_var = *return_value;
            zval_copy_ctor(&EX_T(opline->result.u.var).tmp_var);

            efree(return_value);
        }

        execute_data->opline++;
        return 0;
    }

    int ZProxyHandlers::staticMethodHandler(ZEND_OPCODE_HANDLER_ARGS)
    {
        zend_op *opline = EX(opline);
        zend_class_entry *ce = EX_T(opline->op1.u.var).class_entry;

        union _zend_function *fbc;
        zval* function_name;
        char* function_name_strval;
        int function_name_strlen;

        function_name = &opline->op2.u.constant;

        if (Z_TYPE_P(function_name) != IS_STRING)
            php_error(E_ERROR, "Function name must be a string");

        //! - get method name
        function_name_strval = zend_str_tolower_dup(function_name->value.str.val, function_name->value.str.len);
        function_name_strlen = function_name->value.str.len;

        //! - call proxyMethod if method is not defined in userspace
        if(zend_hash_find(&ce->function_table, function_name_strval, function_name_strlen+1, (void**) &fbc) == FAILURE)
        {
            zend_ptr_stack_3_push(&EG(arg_types_stack), EX(fbc), EX(object), NULL);

            if(zend_hash_find(&ce->function_table, "staticproxymethod", 18, (void**) &fbc) != FAILURE)
            {
                Context::setActiveCe( EX_T(opline->op1.u.var).class_entry );
                //! TODO we might have a lowersized string here
                Context::setMethodName( PHPQt::findRealMethodName( function_name->value.str.val ) );
                EX(fbc) = fbc;
                efree(function_name_strval);
                EX(opline)++;
                ZEND_VM_CONTINUE(); // expands to return 0
            }
        }  // end try call proxyMethod
        efree(function_name_strval);
        return originalConstantMethodHandler(execute_data);
    }

    /*!
     *  calls the C++ copy constructor if available, and adds the smokephp_object to the new zval
     */

    int ZProxyHandlers::cloneHandler( ZEND_OPCODE_HANDLER_ARGS )
    {
        zend_op* opline = EX(opline);
        //! - see CV_OF, _get_zval_ptr_ptr_cv
        const zval* source = *EG(current_execute_data)->CVs[ EX(opline) ->op1.u.var];
        int _ret = originalCloneSpecCvHandler(execute_data);

        //! - add Qt stuff
        smokephp_object* o = PHPQt::getSmokePHPObjectFromZval( source );
        const void* copyPtr = construct_copy( o );
        if ( !copyPtr )
            php_error(E_ERROR, "%s can not be cloned", o->ce_ptr()->name);

        smokephp_object* so = PHPQt::cloneObject( EX_T(opline->result.u.var).var.ptr, o, copyPtr );
        if( PHPQt::isQObject( so->classId() ) )
            PHPQt::createMetaObject( so, EX_T(opline->result.u.var).var.ptr );

        return _ret;
    }

    void ZProxyHandlers::installProxyHandlers()
    {
        //! - overwrite method handler
        php_qt_handler = *zend_get_std_object_handlers();
        zend_orig_handler = php_qt_handler;
        php_qt_handler.get_method = methodHandler;

        //! - overwrite :: operator, see zend_vm_execute.h
        memcpy(phpqt_opcode_handlers, zend_opcode_handlers, sizeof(phpqt_opcode_handlers));
        phpqt_original_opcode_handlers = zend_opcode_handlers;
        zend_opcode_handlers = (opcode_handler_t*) phpqt_opcode_handlers;

        //! - overwrite the clone handler
        originalCloneSpecCvHandler = phpqt_opcode_handlers[(ZEND_CLONE*25) + 20];
        //! - ZEND_CLONE = 110 => 2750, line 29325
        for(int i = 20; i <= 25; i++){
            phpqt_opcode_handlers[(ZEND_CLONE*25) + i] = cloneHandler;
        }

        //! - ZEND_FETCH_CONSTANT = 99 => 2475, line 29050 in 5.2.4
        phpqt_opcode_handlers[(ZEND_FETCH_CONSTANT*25) + 0] = constantHandler;
        //! - replace and store ZEND_INIT_STATIC_METHOD_CALL_SPEC_CONST_HANDLER, 29400
        originalConstantMethodHandler = phpqt_opcode_handlers[2825];
        phpqt_opcode_handlers[2825] = staticMethodHandler;
        phpqt_opcode_handlers[2830] = staticMethodHandler;
        phpqt_opcode_handlers[2835] = staticMethodHandler;
        phpqt_opcode_handlers[2840] = staticMethodHandler;
        phpqt_opcode_handlers[2845] = staticMethodHandler;
    }
}
