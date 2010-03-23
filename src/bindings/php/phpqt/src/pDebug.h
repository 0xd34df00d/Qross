/**
 * PHP-Qt - The PHP language bindings for Qt
 *
 * Copyright (C) 2008 - 2009
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

#ifndef PDEBUG_H_
#define PDEBUG_H_

/**
 * If debug is compiled in, you can define debug levels using php.ini directives. Thus, you're able to
 * fine-tune the output depending on the issues you want to debug.
 */

// NOTICE make a switch that handles either Qt or PHP messages
// TODO add throwPHPError(), throwPHPWarning(), throwPHPNotice()
// NOTICE maybe rename pError() to pFatal()

//ZEND_DEBUG_OBJECTS

#include "config.h"
#include <QDebug>

namespace PHPQt
{
	enum Area {
		NoLevel,
		Method, StaticMethod,
		VirtualMethod, Signal, Slot,
		Moc,
		MapPtr, UnmapPtr,
		MapHandle, UnmapHandle,
		Construct, Destruct
	};
}

#ifdef PHPQT_DEBUG

#ifndef PHPQT_MOC_DEBUG
#define PHPQT_MOC_DEBUG 0
#endif
#ifndef PHPQT_CONSTRUCT_DEBUG
#define PHPQT_CONSTRUCT_DEBUG 0
#endif
#ifndef PHPQT_DESTRUCT_DEBUG
#define PHPQT_DESTRUCT_DEBUG 0
#endif
#ifndef PHPQT_METHOD_DEBUG
#define PHPQT_METHOD_DEBUG 0
#endif
#ifndef PHPQT_STATICMETHOD_DEBUG
#define PHPQT_STATICMETHOD_DEBUG 0
#endif
#ifndef PHPQT_VIRTUALMETHOD_DEBUG
#define PHPQT_VIRTUALMETHOD_DEBUG 0
#endif
#ifndef PHPQT_SIGNAL_DEBUG
#define PHPQT_SIGNAL_DEBUG 0
#endif
#ifndef PHPQT_SLOT_DEBUG
#define PHPQT_SLOT_DEBUG 0
#endif
#ifndef PHPQT_MAPPTR_DEBUG
#define PHPQT_MAPPTR_DEBUG 0
#endif
#ifndef PHPQT_UNMAPPTR_DEBUG
#define PHPQT_UNMAPPTR_DEBUG 0
#endif
#ifndef PHPQT_MAPHANDLE_DEBUG
#define PHPQT_MAPHANDLE_DEBUG 0
#endif
#ifndef PHPQT_UNMAPHANDLE_DEBUG
#define PHPQT_UNMAPHANDLE_DEBUG 0
#endif

static bool MethodDebug = PHPQT_METHOD_DEBUG;
static bool StaticMethodDebug = PHPQT_STATICMETHOD_DEBUG;
static bool VirtualMethodDebug = PHPQT_VIRTUALMETHOD_DEBUG;
static bool SignalDebug = PHPQT_SIGNAL_DEBUG;
static bool SlotDebug = PHPQT_SLOT_DEBUG;
static bool MocDebug = PHPQT_MOC_DEBUG;
static bool MapPtrDebug = PHPQT_MAPPTR_DEBUG;
static bool UnmapPtrDebug = PHPQT_UNMAPPTR_DEBUG;
static bool MapHandleDebug = PHPQT_MAPHANDLE_DEBUG;
static bool UnmapHandleDebug = PHPQT_UNMAPHANDLE_DEBUG;
static bool ConstructDebug = PHPQT_CONSTRUCT_DEBUG;
static bool DestructDebug = PHPQT_DESTRUCT_DEBUG;

static inline QDebug mapToArea( int area, QtMsgType msgType )
{
	switch (area) {
	case PHPQt::Moc:
		if( MocDebug )
			return QDebug( msgType ) << "moc: ";
		else
			return new QString;
		break;
	case PHPQt::MapPtr:
		if( MapPtrDebug )
			return QDebug( msgType ) << "mapPtr: ";
		else
			return new QString;
		break;
	case PHPQt::Signal:
		if( SignalDebug )
			return QDebug( msgType ) << "signal";
		else
			return new QString;
	case PHPQt::Slot:
		if( SlotDebug )
			return QDebug( msgType ) << "slot";
		else
			return new QString;
	case PHPQt::VirtualMethod:
		if( VirtualMethodDebug )
			return QDebug( msgType ) << "virtual";
		else
			return new QString;
	case PHPQt::StaticMethod:
		if( StaticMethodDebug )
			return QDebug( msgType ) << "static method";
		else
			return new QString;
	case PHPQt::Method:
		if( MethodDebug )
			return QDebug( msgType ) << "method";
		else
			return new QString;
	case PHPQt::MapHandle:
		if( MapHandleDebug )
			return QDebug( msgType ) << "mapHandle";
		else
			return new QString;
	case PHPQt::Construct:
		if( ConstructDebug )
			return QDebug( msgType ) << "construct";
		else
			return new QString;
	case PHPQt::Destruct:
		if( DestructDebug )
			return QDebug( msgType ) << "destruct";
		else
			return new QString;
	case PHPQt::UnmapPtr:
		if( UnmapPtrDebug )
			return QDebug( msgType ) << "unmapPtr";
		else
			return new QString;
	case PHPQt::UnmapHandle:
		if( UnmapHandleDebug )
			return QDebug( msgType ) << "unmapHandle";
		else
			return new QString;
	default:
		return QDebug( msgType );
	}
}
#endif

#ifdef PHPQT_DEBUG
static inline QDebug pDebug( PHPQt::Area area = PHPQt::NoLevel )
{
	return mapToArea( area, QtDebugMsg );
}
#else
static inline QDebug pDebug( PHPQt::Area area = PHPQt::NoLevel )
{
	return new QString;
}
#endif

#ifdef PHPQT_DEBUG
static inline QDebug pNotice( PHPQt::Area area = PHPQt::NoLevel )
{
	return QDebug(QtCriticalMsg) << area;
}
#else
static inline QDebug pNotice( PHPQt::Area area = PHPQt::NoLevel )
{
	return new QString;
}
#endif

static inline QDebug pError( PHPQt::Area area = PHPQt::NoLevel )
{
	return QDebug(QtFatalMsg) << area;
}

#endif /*PDEBUG_H_*/
