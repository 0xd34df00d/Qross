/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2005-2008 Cyrille Berger <cberger@cberger.net>
 * Copyright (C) 2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "variant.h"
#include <climits>
#include <limits>
#include <QtCore/QDateTime>
#include <QtCore/QRect>
#include <QtCore/QTimeZone>
#include <QtCore/QUrl>
#include <QtGui/QColor>
#include "../core/manager.h"
#include "../core/object.h"
#include "object.h"
#include "wrapper.h"

using namespace Qross;

namespace
{
    VALUE classNamed(const char* name)
    {
        const ID id = rb_intern(name);
        return rb_const_defined(rb_cObject, id) ? rb_const_get(rb_cObject, id) : Qnil;
    }

    Result fromList(const QVariantList& list)
    {
        VALUE array = rb_ary_new_capa(list.size());
        for (const QVariant& item : list)
        {
            const Result value = toRuby(item);
            if (!value)
                return value;
            rb_ary_push(array, *value);
        }
        return array;
    }

    Result fromMap(const QVariantMap& map)
    {
        VALUE hash = rb_hash_new();
        for (auto it = map.cbegin(); it != map.cend(); ++it)
        {
            const Result value = toRuby(it.value());
            if (!value)
                return value;
            rb_hash_aset(hash, fromString(it.key()), *value);
        }
        return hash;
    }

    VALUE fromDateTime(const QDateTime& dateTime)
    {
        if (!dateTime.isValid())
            return Qnil;
        const qint64 msecs = dateTime.toMSecsSinceEpoch();
        qint64 seconds = msecs / 1000;
        qint64 remainder = msecs % 1000;
        if (remainder < 0)
        {
            remainder += 1000;
            --seconds;
        }
        const timespec spec { time_t(seconds), long(remainder) * 1000000 };

        // INT_MAX asks for local time, INT_MAX - 1 for UTC.
        int offset = INT_MAX;
        switch (dateTime.timeSpec())
        {
        case Qt::UTC:
            offset = INT_MAX - 1;
            break;
        case Qt::OffsetFromUTC:
        case Qt::TimeZone:
            offset = dateTime.offsetFromUtc();
            break;
        case Qt::LocalTime:
            break;
        }
        return rb_time_timespec_new(&spec, offset);
    }

    Result fromDate(const QDate& date)
    {
        if (!date.isValid())
            return Qnil;
        const VALUE klass = classNamed("Date");
        if (NIL_P(klass))
            return fromString(date.toString(Qt::ISODate));
        return callProtected(klass, rb_intern("new"), { INT2NUM(date.year()), INT2NUM(date.month()), INT2NUM(date.day()) });
    }

    VALUE fromColor(const QColor& color)
    {
        if (!color.isValid())
            return Qnil;
        return fromString(color.name(color.alpha() == 255 ? QColor::HexRgb : QColor::HexArgb));
    }

    QVariant fromInteger(VALUE value)
    {
        if (FIXNUM_P(value))
        {
            const long number = FIX2LONG(value);
            if (number >= std::numeric_limits<int>::min() && number <= std::numeric_limits<int>::max())
                return int(number);
            return qlonglong(number);
        }

        // The sign comes back as the result, with 2 for a magnitude beyond 64 bits.
        quint64 magnitude = 0;
        const int sign = rb_integer_pack(value, &magnitude, 1, sizeof magnitude, 0, INTEGER_PACK_NATIVE_BYTE_ORDER);
        if (sign >= 0 && sign < 2)
            return magnitude <= quint64(std::numeric_limits<qint64>::max()) ? QVariant(qlonglong(magnitude)) : QVariant(qulonglong(magnitude));
        if (sign == -1 && magnitude <= quint64(1) << 63)
            return qlonglong(-qint64(magnitude - 1) - 1);
        return rb_big2dbl(value);
    }

    QVariant fromRubyString(VALUE string)
    {
        if (rb_enc_get_index(string) == rb_ascii8bit_encindex())
            return QByteArray(RSTRING_PTR(string), RSTRING_LEN(string));
        return toString(string);
    }

    QVariant fromTime(VALUE time)
    {
        const timespec spec = rb_time_timespec(time);
        const qint64 msecs = qint64(spec.tv_sec) * 1000 + spec.tv_nsec / 1000000;
        const Result utc = callProtected(time, rb_intern("utc?"), {});
        if (utc && RTEST(*utc))
            return QDateTime::fromMSecsSinceEpoch(msecs, QTimeZone::UTC);
        const Result offset = callProtected(time, rb_intern("utc_offset"), {});
        const QDateTime local = QDateTime::fromMSecsSinceEpoch(msecs, QTimeZone::LocalTime);
        if (!offset || !FIXNUM_P(*offset) || FIX2LONG(*offset) == local.offsetFromUtc())
            return local;
        return QDateTime::fromMSecsSinceEpoch(msecs, QTimeZone::fromSecondsAheadOfUtc(int(FIX2LONG(*offset))));
    }

    QVariant fromDate(VALUE date)
    {
        const VALUE dateTimeClass = classNamed("DateTime");
        if (!NIL_P(dateTimeClass) && RTEST(rb_obj_is_kind_of(date, dateTimeClass)))
        {
            const Result time = callProtected(date, rb_intern("to_time"), {});
            return time && RTEST(rb_obj_is_kind_of(*time, rb_cTime)) ? fromTime(*time) : QVariant();
        }
        const Result year = callProtected(date, rb_intern("year"), {});
        const Result month = callProtected(date, rb_intern("month"), {});
        const Result day = callProtected(date, rb_intern("day"), {});
        if (!year || !month || !day)
            return {};
        return QDate(int(NUM2LONG(*year)), int(NUM2LONG(*month)), int(NUM2LONG(*day)));
    }

    int insertPair(VALUE key, VALUE value, VALUE argument)
    {
        auto* const map = reinterpret_cast<QVariantMap*>(argument);
        QString name = toString(key);
        if (!RB_TYPE_P(key, T_STRING) && !RB_SYMBOL_P(key))
        {
            const Result text = callProtected(key, rb_intern("to_s"), {});
            name = text ? toString(*text) : QString();
        }
        map->insert(name, toVariant(value));
        return ST_CONTINUE;
    }
}

VALUE Qross::fromString(const QString& string)
{
    const QByteArray utf8 = string.toUtf8();
    return rb_utf8_str_new(utf8.constData(), utf8.size());
}

QString Qross::toString(VALUE value)
{
    if (RB_SYMBOL_P(value))
        value = rb_sym2str(value);
    if (!RB_TYPE_P(value, T_STRING))
        return {};
    const int encoding = rb_enc_get_index(value);
    if (encoding != rb_utf8_encindex() && encoding != rb_usascii_encindex() && encoding != rb_ascii8bit_encindex())
        value = rb_str_conv_enc(value, rb_enc_get(value), rb_utf8_encoding());
    return QString::fromUtf8(RSTRING_PTR(value), RSTRING_LEN(value));
}

Result Qross::toRuby(const QVariant& value)
{
    const QMetaType type = value.metaType();
    switch (type.id())
    {
    case QMetaType::UnknownType:
    case QMetaType::Nullptr:
        return Qnil;
    case QMetaType::Bool:
        return value.toBool() ? Qtrue : Qfalse;
    case QMetaType::Int:
    case QMetaType::Short:
    case QMetaType::Char:
    case QMetaType::SChar:
    case QMetaType::Long:
    case QMetaType::LongLong:
        return LL2NUM(value.toLongLong());
    case QMetaType::UInt:
    case QMetaType::UShort:
    case QMetaType::UChar:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
        return ULL2NUM(value.toULongLong());
    case QMetaType::Float:
    case QMetaType::Double:
        return rb_float_new(value.toDouble());
    case QMetaType::QString:
        return fromString(value.toString());
    case QMetaType::QChar:
        return fromString(QString(value.toChar()));
    case QMetaType::QByteArray: {
        const QByteArray bytes = value.toByteArray();
        return rb_str_new(bytes.constData(), bytes.size());
    }
    case QMetaType::QStringList:
    case QMetaType::QVariantList:
        return fromList(value.toList());
    case QMetaType::QVariantMap:
    case QMetaType::QVariantHash:
        return fromMap(value.toMap());
    case QMetaType::QUrl:
        return fromString(value.toUrl().toString());
    case QMetaType::QColor:
        return fromColor(value.value<QColor>());
    case QMetaType::QSize: {
        const QSize size = value.toSize();
        return rb_ary_new_from_args(2, INT2NUM(size.width()), INT2NUM(size.height()));
    }
    case QMetaType::QSizeF: {
        const QSizeF size = value.toSizeF();
        return rb_ary_new_from_args(2, rb_float_new(size.width()), rb_float_new(size.height()));
    }
    case QMetaType::QPoint: {
        const QPoint point = value.toPoint();
        return rb_ary_new_from_args(2, INT2NUM(point.x()), INT2NUM(point.y()));
    }
    case QMetaType::QPointF: {
        const QPointF point = value.toPointF();
        return rb_ary_new_from_args(2, rb_float_new(point.x()), rb_float_new(point.y()));
    }
    case QMetaType::QRect: {
        const QRect rect = value.toRect();
        return rb_ary_new_from_args(4, INT2NUM(rect.x()), INT2NUM(rect.y()), INT2NUM(rect.width()), INT2NUM(rect.height()));
    }
    case QMetaType::QRectF: {
        const QRectF rect = value.toRectF();
        return rb_ary_new_from_args(4, rb_float_new(rect.x()), rb_float_new(rect.y()), rb_float_new(rect.width()), rb_float_new(rect.height()));
    }
    case QMetaType::QDateTime:
        return fromDateTime(value.toDateTime());
    case QMetaType::QDate:
        return fromDate(value.toDate());
    case QMetaType::QTime: {
        const QTime time = value.toTime();
        return time.isValid() ? fromString(time.toString(Qt::ISODateWithMs)) : Qnil;
    }
    default:
        break;
    }

    if (type == QMetaType::fromType<Object::Ptr>())
    {
        const Object::Ptr object = value.value<Object::Ptr>();
        if (const auto* const ruby = dynamic_cast<RubyObject*>(object.data()))
            return ruby->value();
        return Qnil;
    }

    if (MetaTypeHandler* const handler = Manager::self().metaTypeHandler(type.name()))
    {
        void* const pointer = (type.flags() & QMetaType::IsPointer) ? *static_cast<void* const*>(value.constData()) : const_cast<void*>(value.constData());
        const QVariant handled = handler->callHandler(pointer);
        if (handled.metaType() != type)
            return toRuby(handled);
    }

    if (type.flags() & QMetaType::PointerToQObject)
        return wrapObject(*static_cast<QObject* const*>(value.constData()));
    if (type.flags() & QMetaType::IsEnumeration)
        return LL2NUM(value.toLongLong());
    if (value.canConvert<QVariantList>())
        return fromList(value.toList());
    if (value.canConvert<QVariantMap>())
        return fromMap(value.toMap());

    return fail(rb_eTypeError, QStringLiteral("cannot convert a value of type %1 to Ruby").arg(QString::fromLatin1(type.name())));
}

QVariant Qross::toVariant(VALUE value)
{
    switch (rb_type(value))
    {
    case T_NIL:
        return {};
    case T_TRUE:
        return true;
    case T_FALSE:
        return false;
    case T_FIXNUM:
    case T_BIGNUM:
        return fromInteger(value);
    case T_FLOAT:
        return RFLOAT_VALUE(value);
    case T_STRING:
        return fromRubyString(value);
    case T_SYMBOL:
        return toString(value);
    case T_ARRAY: {
        QVariantList list;
        const long count = RARRAY_LEN(value);
        list.reserve(count);
        for (long i = 0; i < count; ++i)
            list << toVariant(rb_ary_entry(value, i));
        return list;
    }
    case T_HASH: {
        QVariantMap map;
        rb_hash_foreach(value, insertPair, reinterpret_cast<VALUE>(&map));
        return map;
    }
    default:
        break;
    }

    if (isWrapper(value))
        return QVariant::fromValue(unwrapObject(value));
    if (RTEST(rb_obj_is_kind_of(value, rb_cTime)))
        return fromTime(value);
    const VALUE dateClass = classNamed("Date");
    if (!NIL_P(dateClass) && RTEST(rb_obj_is_kind_of(value, dateClass)))
        return fromDate(value);

    return QVariant::fromValue(Object::Ptr(new RubyObject(value)));
}
