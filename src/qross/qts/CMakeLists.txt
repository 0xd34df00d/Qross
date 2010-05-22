include_directories(${CMAKE_SOURCE_DIR}/..)

FIND_PACKAGE (Qt4 REQUIRED)
SET (QT_USE_QTUITOOLS TRUE)
SET (QT_USE_QTSCRIPT TRUE)
INCLUDE (${QT_USE_FILE})

########### next target ###############
set(qrossqtsplugin_LIB_SRCS plugin.cpp)
add_library(qrossqtsplugin SHARED ${qrossqtsplugin_LIB_SRCS})

target_link_libraries(qrossqtsplugin ${QT_LIBRARIES} qrosscore)
install(TARGETS qrossqtsplugin DESTINATION ${PLUGIN_INSTALL_DIR}/plugins/script)

########### next target ###############

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/qross)
set(qrossqtstest_SRCS main.cpp)
add_executable(qrossqtstest ${qrossqtstest_SRCS})

target_link_libraries(qrossqtstest ${QT_LIBRARIES})
# set(qrossqtsplugintest_SRCS main.cpp)
# target_link_libraries(qrossqtsplugintest ${KDE4_KDECORE_LIBS} )
# kde4_add_executable(qrossqtsplugintest ${qrossqtsplugintest_SRCS})
# #install(TARGETS qrossqtsplugintest DESTINATION ${BIN_INSTALL_DIR})

########### next target ###############

#include_directories(${CMAKE_SOURCE_DIR}/qross ${KDE4_KJS_INCLUDES} ${CMAKE_SOURCE_DIR}/kjsembed ${KDE4_KDECORE_INCLUDES} ${KDE4_KDEUI_INCLUDES} ${KDE4_KIO_INCLUDES})
set(qrossqts_PART_SRCS interpreter.cpp script.cpp)
# TODO: add_plugin?
#add_plugin(qrossqts ${qrossqts_PART_SRCS})
#target_link_libraries(qrossqts ${QT_LIBRARIES} qrosscore)
#
#install(TARGETS qrossqts DESTINATION ${PLUGIN_INSTALL_DIR})
