# Find qrosscore library

# Qrosscore_INCLUDE_DIR
# Qrosscore_LIBRARY
# Qrosscore_FOUND

# Copyright (c) 2010 0xd34df00d (0xd34df00d@gmail.com)

FIND_PATH(Qrosscore_INCLUDE_DIR NAMES qross/core/script.h PATH ENV)
FIND_LIBRARY(Qrosscore_LIBRARY NAMES torrent-rasterbar)

IF(Qrosscore_INCLUDE_DIR AND Qrosscore_LIBRARY)
	SET(Qrosscore_FOUND 1)
ENDIF()

IF(Qrosscore_FOUND)
	MESSAGE(STATUS "Found qrosscore libraries at ${Qrosscore_LIBRARY}")
	MESSAGE(STATUS "Found qrosscore headers at ${Qrosscore_INCLUDE_DIR}")
ELSE()
	IF(Qrosscore_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could NOT find required qrosscore library, aborting")
	ELSE()
		MESSAGE(STATUS "Could NOT find qrosscore")
	ENDIF()
ENDIF()
