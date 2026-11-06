/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * Copyright (C) 2004-2006 Sebastian Sauer <mail@dipe.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "variant.h"
#include <datetime.h>
#include <limits>
#include <QtCore/QDateTime>
#include <QtCore/QRect>
#include <QtCore/QTimeZone>
#include <QtCore/QUrl>
#include <QtGui/QColor>
#include "../core/manager.h"
#include "../core/object.h"
#include "object.h"
#include "ref.h"
#include "wrapper.h"

using namespace Qross;

namespace
{
    void importDateTime()
    {
        if (!PyDateTimeAPI)
            PyDateTime_IMPORT;
    }

    PyObject* fromString(const QString& string)
    {
        // Decoded as UTF-16 rather than UTF-8 so that a lone surrogate, which both sides can hold, survives.
        int byteOrder = Q_BYTE_ORDER == Q_LITTLE_ENDIAN ? -1 : 1;
        return PyUnicode_DecodeUTF16(reinterpret_cast<const char*>(string.constData()), string.size() * 2, "surrogatepass", &byteOrder);
    }

    PyObject* fromList(const QVariantList& list)
    {
        Ref result(PyList_New(list.size()));
        if (!result)
            return nullptr;
        for (qsizetype i = 0; i < list.size(); ++i)
        {
            PyObject* const item = toPython(list[i]);
            if (!item)
                return nullptr;
            PyList_SET_ITEM(result.get(), i, item);
        }
        return result.release();
    }

    PyObject* fromMap(const QVariantMap& map)
    {
        Ref result(PyDict_New());
        if (!result)
            return nullptr;
        for (auto it = map.cbegin(); it != map.cend(); ++it)
        {
            const Ref key(fromString(it.key()));
            const Ref value(toPython(it.value()));
            if (!key || !value || PyDict_SetItem(result.get(), key.get(), value.get()) < 0)
                return nullptr;
        }
        return result.release();
    }

    PyObject* fromDateTime(const QDateTime& dateTime)
    {
        if (!dateTime.isValid())
            Py_RETURN_NONE;
        const QDate date = dateTime.date();
        const QTime time = dateTime.time();
        // Local time stays naive, which Python reads as local time too; anything else carries its offset.
        Ref zone = Ref::borrowed(Py_None);
        if (dateTime.timeSpec() != Qt::LocalTime)
        {
            const Ref offset(PyDelta_FromDSU(0, dateTime.offsetFromUtc(), 0));
            zone = Ref(offset ? PyTimeZone_FromOffset(offset.get()) : nullptr);
            if (!zone)
                return nullptr;
        }
        return PyDateTimeAPI->DateTime_FromDateAndTime(date.year(), date.month(), date.day(), time.hour(), time.minute(), time.second(), time.msec() * 1000, zone.get(), PyDateTimeAPI->DateTimeType);
    }

    PyObject* fromColor(const QColor& color)
    {
        if (!color.isValid())
            Py_RETURN_NONE;
        return fromString(color.name(color.alpha() == 255 ? QColor::HexRgb : QColor::HexArgb));
    }

    QString toString(PyObject* object)
    {
        const Py_ssize_t length = PyUnicode_GET_LENGTH(object);
        switch (PyUnicode_KIND(object))
        {
        case PyUnicode_1BYTE_KIND:
            return QString::fromLatin1(reinterpret_cast<const char*>(PyUnicode_1BYTE_DATA(object)), length);
        case PyUnicode_2BYTE_KIND:
            return QString(reinterpret_cast<const QChar*>(PyUnicode_2BYTE_DATA(object)), length);
        default:
            break;
        }
        // A code point beyond the BMP takes a surrogate pair; a surrogate code point, which Python allows, stays a lone one.
        QString result;
        result.reserve(length);
        const Py_UCS4* const data = PyUnicode_4BYTE_DATA(object);
        for (Py_ssize_t i = 0; i < length; ++i)
            result += QChar::fromUcs4(data[i]);
        return result;
    }

    QVariant fromLong(PyObject* object)
    {
        int overflow = 0;
        const long long value = PyLong_AsLongLongAndOverflow(object, &overflow);
        if (overflow > 0)
        {
            const unsigned long long large = PyLong_AsUnsignedLongLong(object);
            if (!PyErr_Occurred())
                return qulonglong(large);
            PyErr_Clear();
        }
        if (overflow != 0)
        {
            const double approximate = PyLong_AsDouble(object);
            PyErr_Clear();
            return approximate;
        }
        if (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max())
            return int(value);
        return qlonglong(value);
    }
}

PyObject* Qross::toPython(const QVariant& value)
{
    const QMetaType type = value.metaType();
    switch (type.id())
    {
    case QMetaType::UnknownType:
    case QMetaType::Nullptr:
        Py_RETURN_NONE;
    case QMetaType::Bool:
        return PyBool_FromLong(value.toBool());
    case QMetaType::Int:
    case QMetaType::Short:
    case QMetaType::Char:
    case QMetaType::SChar:
    case QMetaType::Long:
    case QMetaType::LongLong:
        return PyLong_FromLongLong(value.toLongLong());
    case QMetaType::UInt:
    case QMetaType::UShort:
    case QMetaType::UChar:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
        return PyLong_FromUnsignedLongLong(value.toULongLong());
    case QMetaType::Float:
    case QMetaType::Double:
        return PyFloat_FromDouble(value.toDouble());
    case QMetaType::QString:
        return fromString(value.toString());
    case QMetaType::QChar:
        return fromString(QString(value.toChar()));
    case QMetaType::QByteArray: {
        const QByteArray bytes = value.toByteArray();
        return PyBytes_FromStringAndSize(bytes.constData(), bytes.size());
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
        return Py_BuildValue("(ii)", size.width(), size.height());
    }
    case QMetaType::QSizeF: {
        const QSizeF size = value.toSizeF();
        return Py_BuildValue("(dd)", size.width(), size.height());
    }
    case QMetaType::QPoint: {
        const QPoint point = value.toPoint();
        return Py_BuildValue("(ii)", point.x(), point.y());
    }
    case QMetaType::QPointF: {
        const QPointF point = value.toPointF();
        return Py_BuildValue("(dd)", point.x(), point.y());
    }
    case QMetaType::QRect: {
        const QRect rect = value.toRect();
        return Py_BuildValue("(iiii)", rect.x(), rect.y(), rect.width(), rect.height());
    }
    case QMetaType::QRectF: {
        const QRectF rect = value.toRectF();
        return Py_BuildValue("(dddd)", rect.x(), rect.y(), rect.width(), rect.height());
    }
    case QMetaType::QDateTime:
        importDateTime();
        return fromDateTime(value.toDateTime());
    case QMetaType::QDate: {
        importDateTime();
        const QDate date = value.toDate();
        if (!date.isValid())
            Py_RETURN_NONE;
        return PyDate_FromDate(date.year(), date.month(), date.day());
    }
    case QMetaType::QTime: {
        importDateTime();
        const QTime time = value.toTime();
        if (!time.isValid())
            Py_RETURN_NONE;
        return PyTime_FromTime(time.hour(), time.minute(), time.second(), time.msec() * 1000);
    }
    default:
        break;
    }

    if (type == QMetaType::fromType<Object::Ptr>())
    {
        const Object::Ptr object = value.value<Object::Ptr>();
        if (auto* const python = dynamic_cast<PythonObject*>(object.data()))
            return python->object();
        Py_RETURN_NONE;
    }

    if (MetaTypeHandler* const handler = Manager::self().metaTypeHandler(type.name()))
    {
        void* const pointer = (type.flags() & QMetaType::IsPointer) ? *static_cast<void* const*>(value.constData()) : const_cast<void*>(value.constData());
        const QVariant handled = handler->callHandler(pointer);
        if (handled.metaType() != type)
            return toPython(handled);
    }

    if (type.flags() & QMetaType::PointerToQObject)
        return wrapObject(*static_cast<QObject* const*>(value.constData()));
    if (type.flags() & QMetaType::IsEnumeration)
        return PyLong_FromLongLong(value.toLongLong());
    if (value.canConvert<QVariantList>())
        return fromList(value.toList());
    if (value.canConvert<QVariantMap>())
        return fromMap(value.toMap());

    PyErr_Format(PyExc_TypeError, "cannot convert a value of type %s to Python", type.name());
    return nullptr;
}

QVariant Qross::toVariant(PyObject* object)
{
    if (!object || object == Py_None)
        return QVariant();
    if (PyBool_Check(object))
        return object == Py_True;
    if (PyLong_Check(object))
        return fromLong(object);
    if (PyFloat_Check(object))
        return PyFloat_AsDouble(object);
    if (PyUnicode_Check(object))
        return toString(object);
    if (PyBytes_Check(object))
        return QByteArray(PyBytes_AS_STRING(object), PyBytes_GET_SIZE(object));
    if (PyByteArray_Check(object))
        return QByteArray(PyByteArray_AS_STRING(object), PyByteArray_GET_SIZE(object));
    if (PyList_Check(object) || PyTuple_Check(object))
    {
        QVariantList list;
        const Py_ssize_t count = PySequence_Size(object);
        for (Py_ssize_t i = 0; i < count; ++i)
        {
            const Ref item(PySequence_GetItem(object, i));
            list << toVariant(item.get());
        }
        return list;
    }
    if (PyDict_Check(object))
    {
        QVariantMap map;
        PyObject* key = nullptr;
        PyObject* value = nullptr;
        Py_ssize_t position = 0;
        while (PyDict_Next(object, &position, &key, &value))
        {
            const Ref keyString(PyObject_Str(key));
            map.insert(keyString ? toString(keyString.get()) : QString(), toVariant(value));
        }
        return map;
    }
    if (isWrapper(object))
        return QVariant::fromValue(unwrapObject(object));

    importDateTime();
    if (PyDateTime_Check(object))
    {
        const QDate date(PyDateTime_GET_YEAR(object), PyDateTime_GET_MONTH(object), PyDateTime_GET_DAY(object));
        const QTime time(PyDateTime_DATE_GET_HOUR(object), PyDateTime_DATE_GET_MINUTE(object), PyDateTime_DATE_GET_SECOND(object), PyDateTime_DATE_GET_MICROSECOND(object) / 1000);
        if (PyDateTime_DATE_GET_TZINFO(object) == Py_None)
            return QDateTime(date, time);
        const Ref offset(PyObject_CallMethod(object, "utcoffset", nullptr));
        if (!offset || !PyDelta_Check(offset.get()))
        {
            PyErr_Clear();
            return QDateTime(date, time);
        }
        const int seconds = PyDateTime_DELTA_GET_DAYS(offset.get()) * 86400 + PyDateTime_DELTA_GET_SECONDS(offset.get());
        const int microseconds = PyDateTime_DELTA_GET_MICROSECONDS(offset.get());
        // Qt holds whole-second offsets within sixteen hours of UTC; any other datetime becomes UTC at the same instant.
        if (const QTimeZone zone = QTimeZone::fromSecondsAheadOfUtc(seconds); zone.isValid() && !microseconds)
            return QDateTime(date, time, zone);
        return QDateTime(date, time, QTimeZone::UTC).addMSecs(-(qint64(seconds) * 1000 + microseconds / 1000));
    }
    if (PyDate_Check(object))
        return QDate(PyDateTime_GET_YEAR(object), PyDateTime_GET_MONTH(object), PyDateTime_GET_DAY(object));
    if (PyTime_Check(object))
        return QTime(PyDateTime_TIME_GET_HOUR(object), PyDateTime_TIME_GET_MINUTE(object), PyDateTime_TIME_GET_SECOND(object), PyDateTime_TIME_GET_MICROSECOND(object) / 1000);

    return QVariant::fromValue(Object::Ptr(new PythonObject(object)));
}
