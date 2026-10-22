project(qrosspython)
cmake_minimum_required(VERSION 2.8)

option(USE_QT5 "Build with Qt5 support" OFF)

set (SHLIB_SUFFIX "")
if (USE_QT5)
	set (SHLIB_SUFFIX "-qt5")
	find_package (Qt5Core REQUIRED)
else ()
	find_package (Qt4 REQUIRED)
	set (QT_USE_QTSCRIPT TRUE)
	set (QT_USE_QTXML TRUE)
	set (QT_USE_QTTEST TRUE)
	include (${QT_USE_FILE})
endif ()

if (${CMAKE_MAJOR_VERSION} EQUAL 2)
	set (PythonLibs_FIND_VERSION 2.7)
	find_package(PythonLibs REQUIRED)
else ()
	find_package(PythonLibs "2.7" REQUIRED)
endif ()

include_directories(
    ${PYTHON_INCLUDE_PATH}
    ../../../
)

########### next target ###############

set(libqrosspythoncxx_SRCS
    cxx/cxxsupport.cxx
    cxx/cxx_extensions.cxx
    cxx/cxxextensions.c
    cxx/IndirectPythonInterface.cxx
)

########### next target ###############

set(qrosspython_PART_SRCS ${libqrosspythoncxx_SRCS}
   pythonvariant.cpp
   pythonextension.cpp
   pythonmodule.cpp
   pythonscript.cpp
   pythoninterpreter.cpp
   pythonobject.cpp
)

add_library(qrosspython${SHLIB_SUFFIX} MODULE ${qrosspython_PART_SRCS})
set_target_properties(qrosspython${SHLIB_SUFFIX} PROPERTIES PREFIX "")
set_property(TARGET qrosspython${SHLIB_SUFFIX} PROPERTY VERSION "0.1")

# -ldl seems to be needed (on Linux at least).
# see http://lists.kde.org/?l=koffice-devel&m=116333261328694&w=2
# and http://websvn.kde.org/branches/work/kwin_composite/CMakeLists.txt?rev=603677&r1=603384&r2=603677
target_link_libraries(qrosspython${SHLIB_SUFFIX} ${QT_LIBRARIES}
	qrosscore${SHLIB_SUFFIX} ${PYTHON_LIBRARIES} ${CMAKE_DL_LIBS})

install(TARGETS qrosspython${SHLIB_SUFFIX} DESTINATION lib${LIB_SUFFIX})

if (USE_QT5)
	QT5_USE_MODULES (qrosspython${SHLIB_SUFFIX} Script Test Xml Widgets)
	include_directories (${Qt5Core_PRIVATE_INCLUDE_DIRS})
endif ()
