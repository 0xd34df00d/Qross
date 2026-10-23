cmake_minimum_required(VERSION 3.21)
project(qross VERSION 0.3.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)

find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets Xml)

# Library and executable names carry the Qt major version, and the core
# derives the interpreter plugin names from the same suffix.
set(SHLIB_SUFFIX "-qt6")

add_compile_definitions(
    SHLIB_SUFFIX="${SHLIB_SUFFIX}"
    QT_NO_KEYWORDS
    QT_NO_FOREACH
    QT_DISABLE_DEPRECATED_UP_TO=0x060800
)

# the core library
add_subdirectory(core)
# commandline-prog to run scripts
add_subdirectory(console)
# unittests and such stuff
add_subdirectory(test)
