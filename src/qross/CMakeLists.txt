CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

option (USE_QT5 "Build with Qt5 support" OFF)

set (SHLIB_SUFFIX "")
if (USE_QT5)
	set (SHLIB_SUFFIX "-qt5")
endif ()

set (CMAKE_AUTOMOC TRUE)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DSHLIB_SUFFIX="${SHLIB_SUFFIX}")

# the core library
add_subdirectory( core )
# the ui library
add_subdirectory( ui )
# optional modules
#add_subdirectory( modules )
# commandline-prog to run scripts
add_subdirectory( console )

# unittests and such stuff
add_subdirectory( test )

# KDE Javascript using kjs and kjsembed
# test kjsembed I think
#add_subdirectory( kjs )

# QtScript backend
add_subdirectory( qts )
