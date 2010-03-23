/**
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

#ifndef SMOKEPHP_H
#define SMOKEPHP_H

#undef DEBUG
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_POSIX
#define __USE_POSIX
#endif
#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif

#include "marshall.h"

#define Qnil (zval *) NULL

class QByteArray;
template <class QByteArray> class QList;

/**
 * Type handling by moc is simple.
 *
 * If the type name matches /^(?:const\s+)?\Q$types\E&?$/, use the
 * static_QUType, where $types is join('|', qw(bool int double char* QString);
 *
 * Everything else is passed as a pointer! There are types which aren't
 * Smoke::tf_ptr but will have to be passed as a pointer. Make sure to keep
 * track of what's what.
 *
 * Simply using typeids isn't enough for signals/slots. It will be possible
 * to declare signals and slots which use arguments which can't all be
 * found in a single smoke object. Instead, we need to store smoke => typeid
 * pairs. We also need additional informatation, such as whether we're passing
 * a pointer to the union element.
 */

/**
 * types of moc arguments
 */
enum MocArgumentType {
    xmoc_ptr,
    xmoc_bool,
    xmoc_int,
    xmoc_uint,
    xmoc_long,
    xmoc_ulong,
    xmoc_double,
    xmoc_charstar,
    xmoc_QString,
    xmoc_void
};

/**
 * holds information about a type and provides it in various forms as well as additional information
 */
class SmokeType
{
    Smoke::Type *_t;        // derived from _smoke and _id, but cached

    Smoke *_smoke;
    Smoke::Index _id;

public:
    SmokeType() : _t(0), _smoke(0), _id(0) {}
    SmokeType(Smoke *s, Smoke::Index i) : _smoke(s), _id(i) {
        if(_id < 0 || _id > _smoke->numTypes) _id = 0;
        _t = _smoke->types + _id;
    }
    // default copy constructors are fine, this is a constant structure

    // mutators
    void set(Smoke *s, Smoke::Index i) {
        _smoke = s;
        _id = i;
        _t = _smoke->types + _id;
    }

    // accessors
    Smoke *smoke() const { return _smoke; }
    Smoke::Index typeId() const { return _id; }
    const Smoke::Type &type() const { return *_t; }
    unsigned short flags() const { return _t->flags; }
    unsigned short elem() const { return _t->flags & Smoke::tf_elem; }
    const char *name() const { return _t->name; }
    Smoke::Index classId() const { return _t->classId; }

    // tests
    bool isStack() const { return ((flags() & Smoke::tf_ref) == Smoke::tf_stack); }
    bool isPtr() const { return ((flags() & Smoke::tf_ref) == Smoke::tf_ptr); }
    bool isRef() const { return ((flags() & Smoke::tf_ref) == Smoke::tf_ref); }
    bool isConst() const { return (flags() & Smoke::tf_const); }
    bool isClass() const {
        if(elem() == Smoke::t_class)
            return classId() ? true : false;
        return false;
    }
    bool isQString() const {
        if(elem() == Smoke::t_voidp && !(elem() == Smoke::t_class))
            return true;
        return false;
    }
    bool operator ==(const SmokeType &b) const;
    bool operator !=(const SmokeType &b) const {
        const SmokeType &a = *this;
        return !(a == b);
    }

};

/**
 * provides information about classes
 */
class SmokeClass
{
    Smoke::Class *_c;
    Smoke *_smoke;
    Smoke::Index _id;

public:
    SmokeClass(const SmokeType &t) {
        _smoke = t.smoke();
        _id = t.classId();
        _c = _smoke->classes + _id;
    }
    SmokeClass(Smoke *smoke, Smoke::Index id) : _smoke(smoke), _id(id) {
        _c = _smoke->classes + _id;
    }

    Smoke *smoke() const { return _smoke; }
    const Smoke::Class &c() const { return *_c; }
    Smoke::Index classId() const { return _id; }
    const char *className() const { return _c->className; }
    Smoke::ClassFn classFn() const { return _c->classFn; }
    Smoke::EnumFn enumFn() const { return _c->enumFn; }
    bool operator ==(const SmokeClass &b) const;
    bool operator !=(const SmokeClass &b) const {
        const SmokeClass &a = *this;
        return !(a == b);
    }
    bool isa(const SmokeClass &sc) const {
        // This is a sick function, if I do say so myself
        if(*this == sc) return true;
        Smoke::Index *parents = _smoke->inheritanceList + _c->parents;
        for(int i = 0; parents[i]; i++) {
            if(SmokeClass(_smoke, parents[i]).isa(sc)) return true;
        }
        return false;
    }

    unsigned short flags() const { return _c->flags; }
    bool hasConstructor() const { return flags() & Smoke::cf_constructor; }
    bool hasCopy() const { return flags() & Smoke::cf_deepcopy; }
    bool hasVirtual() const { return flags() & Smoke::cf_virtual; }
    bool hasFire() const { return !(flags() & Smoke::cf_undefined); }
};

#ifdef THOMAS_MAYBE_TO_BE_REMOVED
class SmokeMethod
{
    Smoke::Method *_m;
    Smoke *_smoke;
    Smoke::Index _id;
public:
    SmokeMethod(Smoke *smoke, Smoke::Index id) : _smoke(smoke), _id(id) {
        _m = _smoke->methods + _id;
    }

    Smoke *smoke() const { return _smoke; }
    const Smoke::Method &m() const { return *_m; }
    SmokeClass c() const { return SmokeClass(_smoke, _m->classId); }
    const char *name() const { return _smoke->methodNames[_m->name]; }
    int numArgs() const { return _m->numArgs; }
    unsigned short flags() const { return _m->flags; }
    SmokeType arg(int i) const {
        if(i >= numArgs()) return SmokeType();
        return SmokeType(_smoke, _smoke->argumentList[_m->args + i]);
    }
    SmokeType ret() const { return SmokeType(_smoke, _m->ret); }
    Smoke::Index methodId() const { return _id; }
    Smoke::Index method() const { return _m->method; }

    bool isStatic() const { return flags() & Smoke::mf_static; }
    bool isConst() const { return flags() & Smoke::mf_const; }

    void call(Smoke::Stack args, void *ptr = 0) const {
        Smoke::ClassFn fn = c().classFn();
        (*fn)(method(), ptr, args);
    }
};
#endif

/**
 * maps SmokeType to MocArgumentType
 * @see SmokeType
 * @see MocArgumentType
 */
struct MocArgument
{
    // smoke object and associated typeid
    SmokeType st;
    MocArgumentType argType;
};

#ifdef THOMAS_MAYBE_TO_BE_REMOVED
/**
 * SmokeObject is a thin wrapper around zval* objects. Each SmokeObject instance
 * increments the refcount of its zval* for the duration of its existance.
 *
 * SmokeObject instances are only returned from PHPQt, since the method
 * of binding data to the scalar must be consistent across all modules.
 */
class SmokeObject
{
    zval* rv;
    Smoke_MAGIC *m;

public:
    SmokeObject(zval* obj, Smoke_MAGIC *mag) : rv(obj), m(mag) {
    }

    ~SmokeObject() {
    }

    SmokeObject(const SmokeObject &other) {
        rv = other.rv;
        m = other.m;

    }

    SmokeObject &operator =(const SmokeObject &other) {
        rv = other.rv;
        m = other.m;
        return *this;
    }

    const SmokeClass &c() { return m->c(); }
    Smoke *smoke() { return c().smoke(); }
    zval* var() { return rv; }
    void *ptr() { return m->ptr(); }
    Smoke::Index classId() { return c().classId(); }
    void *cast(const SmokeClass &toc) {
        return smoke()->cast(
                ptr(),
                classId(),
                smoke()->idClass(toc.className()).index
        );
    }
    const char *className() { return c().className(); }

    bool isValid() const { return !(rv == Qnil); }
    bool isAllocated() const { return m->isAllocated(); }
    void setAllocated(bool i) { m->setAllocated(i); }
};
#endif

namespace PHPQt
{

};

#ifdef THOMAS_TEMP_DISABLED
// TODO temp. disabled code, TODO
void*                   transformArray(const zval* args);
#endif

#endif // SMOKEPHP_H
