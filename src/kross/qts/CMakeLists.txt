include_directories(${CMAKE_SOURCE_DIR})

FIND_PACKAGE (Qt4 REQUIRED)
SET (QT_USE_QTUITOOLS TRUE)
SET (QT_USE_QTSCRIPT TRUE)
INCLUDE (${QT_USE_FILE})

########### next target ###############
set(krossqtsplugin_LIB_SRCS plugin.cpp)
add_library(krossqtsplugin SHARED ${krossqtsplugin_LIB_SRCS})

target_link_libraries(krossqtsplugin ${QT_LIBRARIES} krosscore)
if (NOT CYGWIN)
    set_target_properties(krossqtsplugin PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})
endif (NOT CYGWIN)

install(TARGETS krossqtsplugin DESTINATION ${PLUGIN_INSTALL_DIR}/plugins/script)

########### next target ###############

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/kross)
set(krossqtstest_SRCS main.cpp)
add_executable(krossqtstest ${krossqtstest_SRCS})

target_link_libraries(krossqtstest ${QT_LIBRARIES} krossqtsplugin)
# set(krossqtsplugintest_SRCS main.cpp)
# target_link_libraries(krossqtsplugintest ${KDE4_KDECORE_LIBS} )
# kde4_add_executable(krossqtsplugintest ${krossqtsplugintest_SRCS})
# #install(TARGETS krossqtsplugintest DESTINATION ${BIN_INSTALL_DIR})

########### next target ###############

#include_directories(${CMAKE_SOURCE_DIR}/kross ${KDE4_KJS_INCLUDES} ${CMAKE_SOURCE_DIR}/kjsembed ${KDE4_KDECORE_INCLUDES} ${KDE4_KDEUI_INCLUDES} ${KDE4_KIO_INCLUDES})
set(krossqts_PART_SRCS interpreter.cpp script.cpp)
# TODO: add_plugin?
#add_plugin(krossqts ${krossqts_PART_SRCS})
#target_link_libraries(krossqts ${QT_LIBRARIES} krosscore)
#
#install(TARGETS krossqts DESTINATION ${PLUGIN_INSTALL_DIR})
