cmake_minimum_required (VERSION 3.0)
project(qross VERSION 0.3.2)

set (SHLIB_SUFFIX "-qt5")

set (CMAKE_AUTOMOC TRUE)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-DSHLIB_SUFFIX="${SHLIB_SUFFIX}")

find_package (Qt5 COMPONENTS Core Script Widgets Xml)

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
