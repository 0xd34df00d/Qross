/**
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2006 - 2009
 * Thomas Moenicke <tm at php-qt.org>
 *
 * Derived from the QtRuby and PerlQt sources, see AUTHORS for details
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
// TODO catch more types, see php_to_primitive<long>

template <>
bool php_to_primitive<bool>(zval* v)
{
	if (v->type == IS_OBJECT) {
		// A Qt::Boolean has been passed as a value
		php_error(E_WARNING,"A Qt::Boolean has been passed as a value");
	} else {
		return Z_BVAL_P(v);
	}
}

template <>
zval* primitive_to_php<bool>(bool sv, zval* return_value)
{
	RETVAL_BOOL(sv);
	return return_value;
}

template <>
signed char php_to_primitive<signed char>(zval* v)
{
	return v->value.str.val[0];
}

template <>
zval* primitive_to_php<signed char>(signed char sv, zval* return_value)
{
    php_error(E_ERROR,"signed char not implemented");
}

template <>
unsigned char php_to_primitive<unsigned char>(zval* v)
{
	return v->value.str.val[0];
}

template <>
zval* primitive_to_php<unsigned char>(unsigned char sv, zval* return_value)
{
    php_error(E_ERROR,"unsigned char not implemented");
}

template <>
short php_to_primitive<short>(zval* v)
{
	return Z_LVAL_P(v);
}

template <>
zval* primitive_to_php<short>(short sv, zval* return_value)
{
        RETVAL_LONG(sv);
	return return_value;
}

template <>
unsigned short php_to_primitive<unsigned short>(zval* v)
{
	return Z_LVAL_P(v);
}

template <>
zval* primitive_to_php<unsigned short>(unsigned short sv, zval* return_value)
{
        RETVAL_LONG(sv);
	return return_value;
}

template <>
int php_to_primitive<int>(zval* v)
{
	if (v->type == IS_OBJECT) {
	    php_error(E_WARNING,"An object has been passed, but integer expected.");
	} else {
		if(v->type == IS_LONG) {
	    	return Z_LVAL_P(v);
		// e.g. date() gives a string, so we try to convert it
		} else if (v->type == IS_STRING) {
			return QString(Z_STRVAL_P(v)).toLong();
		} else {
			php_error(E_ERROR,"wrong type, num expected");
		}
	}
}

template <>
zval* primitive_to_php<int>(int sv, zval* return_value)
{
    RETVAL_LONG(sv);
  	return return_value;
}

template <>
unsigned int php_to_primitive<unsigned int>(zval* v)
{
	if (v->type == IS_OBJECT) {
	    php_error(E_WARNING,"An unsigned integer has been passed as an object");
	} else {
	    return Z_LVAL_P(v);
	}
}

template <>
zval* primitive_to_php<unsigned int>(unsigned int sv, zval* return_value)
{
        RETVAL_LONG(sv);
	return return_value;
}

template <>
long php_to_primitive<long>(zval* v)
{
	if (v->type == IS_OBJECT) {
	    php_error(E_WARNING,"A long has been passed as an object");
	} else {
	    return Z_LVAL_P(v);
	}
}

template <>
zval* primitive_to_php<long>(long sv, zval* return_value)
{
        RETVAL_LONG(sv);
	return return_value;
}

template <>
unsigned long php_to_primitive<unsigned long>(zval* v)
{
	if (v->type == IS_OBJECT) {
	    php_error(E_WARNING,"An unsigned long has been passed as an object");
	} else {
	    return Z_LVAL_P(v);
	}
}

template <>
zval* primitive_to_php<unsigned long>(unsigned long sv, zval* return_value)
{
        RETVAL_LONG(sv);
	return return_value;
}

template <>
long long php_to_primitive<long long>(zval* v)
{
	return Z_LVAL_P(v);
}

template <>
zval* primitive_to_php<long long>(long long sv, zval* return_value)
{
        RETVAL_LONG(sv);
	return return_value;
}

template <>
unsigned long long php_to_primitive<unsigned long long>(zval* v)
{
        return Z_LVAL_P(v);
}

template <>
zval* primitive_to_php<unsigned long long>(unsigned long long sv, zval* return_value)
{
        RETVAL_LONG(sv);
	return return_value;
}

template <>
float php_to_primitive<float>(zval* v)
{
        return Z_DVAL_P(v);
}

template <>
zval* primitive_to_php<float>(float sv, zval* return_value)
{
        RETVAL_DOUBLE(sv);
	return return_value;
}

template <>
double php_to_primitive<double>(zval* v)
{
    if (v->type == IS_LONG){
	return Z_LVAL_P(v);
    } else if (v->type == IS_DOUBLE) {
	return Z_DVAL_P(v);
    } else {
	php_error(E_ERROR, "wrong argument type, double expected.");
    }
}

template <>
zval* primitive_to_php<double>(double sv, zval* return_value)
{
        RETVAL_DOUBLE(sv);
	return return_value;
}

template <>
char* php_to_primitive<char *>(zval* rv)
{
	if(rv == Qnil)
		return 0;
	return rv->value.str.val;
}

template <>
unsigned char* php_to_primitive<unsigned char *>(zval* rv)
{
	if(rv == Qnil)
		return 0;

	int len = rv->value.str.len;
	char* mem = (char*) malloc(len+1);
	memcpy(mem, rv->value.str.val, len);
	mem[len] ='\0';
	return (unsigned char*) mem;
}

template <>
zval* primitive_to_php<int*>(int* sv, zval* return_value)
{
	if(!sv) {
		return Qnil;
	}

	return primitive_to_php<int>(*sv, return_value);
}

#if defined(Q_OS_WIN32)
template <>
WId php_to_primitive<WId>(zval* v)
{
	if(v == Qnil)
		return 0;

	return (WId) Z_LVAL_P(v);
}

template <>
zval* primitive_to_php<WId>(WId sv, zval* return_value)
{
        RETVAL_LONG((unsigned long) sv);
	return return_value;
}

template <>
Q_PID php_to_primitive<Q_PID>(zval* v)
{
	if(v == Qnil)
		return 0;

	return (Q_PID) Z_LVAL_P(v);
}

template <>
zval* primitive_to_php<Q_PID>(Q_PID sv, zval* return_value)
{
        RETVAL_LONG((unsigned long) sv);
	return return_value;
}
#endif
