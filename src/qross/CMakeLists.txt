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
# commandline-prog to run scripts
add_subdirectory( console )

# unittests and such stuff
add_subdirectory( test )

# QtScript backend
add_subdirectory( qts )
