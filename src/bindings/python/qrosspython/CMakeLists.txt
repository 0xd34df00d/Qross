project(qrosspython)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})
find_package(PythonLibs REQUIRED)

include_directories(
    ${PYTHON_INCLUDE_PATH}
    ${QT_INCLUDE_DIR}
    ${QT_QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    ../../../
    #${QT_QTNETWORK_INCLUDE_DIR}
    #${QT_QTXML_INCLUDE_DIR}
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

add_library(qrosspython MODULE ${qrosspython_PART_SRCS})
set_target_properties(qrosspython PROPERTIES PREFIX "")
set_property(TARGET qrosspython PROPERTY VERSION "0.1")

# -ldl seems to be needed (on Linux at least).
# see http://lists.kde.org/?l=koffice-devel&m=116333261328694&w=2
# and http://websvn.kde.org/branches/work/kwin_composite/CMakeLists.txt?rev=603677&r1=603384&r2=603677
target_link_libraries(qrosspython ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
	qrosscore ${PYTHON_LIBRARIES} ${CMAKE_DL_LIBS})

install(TARGETS qrosspython DESTINATION lib)
