# - Try to find SMOKE
#
# defines
#
# SMOKE_FOUND - smoke was found on the system
# SMOKE_INCLUDE_DIR - where to find the smoke headers
# SMOKE_LIBRARY - where to find the smoke library

# copyright (c) 2007 Arno Rehn arno@arnorehn.de
#
# Redistribution and use is allowed according to the terms of the GPL license.

FIND_PATH (SMOKE_QT_INCLUDE_DIR smoke.h)
FIND_LIBRARY (SMOKE_QT_LIBRARY smokeqt)

SET (SMOKE_QT_FOUND FALSE)

IF (SMOKE_QT_INCLUDE_DIR AND SMOKE_QT_LIBRARY)
	SET (SMOKE_QT_FOUND TRUE)
ENDIF (SMOKE_QT_INCLUDE_DIR AND SMOKE_QT_LIBRARY)

IF (SMOKE_QT_FOUND)
	IF (NOT SmokeQt_FIND_QUIETLY)
		MESSAGE(STATUS "Found SmokeQt: ${SMOKE_QT_LIBRARY}")
	ENDIF (NOT SmokeQt_FIND_QUIETLY)
ELSE (SMOKE_QT_FOUND)
	IF (SmokeQt_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find SmokeQt")
	ENDIF (SmokeQt_FIND_REQUIRED)
ENDIF (SMOKE_QT_FOUND)

MARK_AS_ADVANCED(SMOKE_QT_INCLUDE_DIR SMOKE_LIBRARY)
