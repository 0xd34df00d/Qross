include_directories(${CMAKE_SOURCE_DIR}/..)

find_package (Qt5 COMPONENTS UiTools)

########### next target ###############
set(qrossqtsplugin_LIB_SRCS plugin.cpp)
add_library(qrossqtsplugin SHARED ${qrossqtsplugin_LIB_SRCS})
set_property(TARGET qrossqtsplugin PROPERTY VERSION "0.1")
target_link_libraries(qrossqtsplugin Qt5::Script Qt5::UiTools Qt5::Widgets)


get_target_property(QMAKE_EXECUTABLE Qt5::qmake LOCATION)
function(QUERY_QMAKE VAR RESULT)
exec_program(${QMAKE_EXECUTABLE} ARGS "-query ${VAR}" RETURN_VALUE return_code OUTPUT_VARIABLE output )
if (NOT return_code)
	file(TO_CMAKE_PATH "${output}" output)
	set(${RESULT} ${output} PARENT_SCOPE)
endif ()
endfunction(QUERY_QMAKE)

query_qmake(QT_INSTALL_PLUGINS QT_PLUGINS_DIR)

install(TARGETS qrossqtsplugin DESTINATION ${QT_PLUGINS_DIR}/script)

########### next target ###############

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/qross)
set(qrossqtstest_SRCS main.cpp)
add_executable(qrossqtstest ${qrossqtstest_SRCS})

target_link_libraries(qrossqtstest Qt5::Gui Qt5::Script Qt5::Widgets)

# set(qrossqtsplugintest_SRCS main.cpp)
# target_link_libraries(qrossqtsplugintest ${KDE4_KDECORE_LIBS} )
# kde4_add_executable(qrossqtsplugintest ${qrossqtsplugintest_SRCS})
# #install(TARGETS qrossqtsplugintest DESTINATION ${BIN_INSTALL_DIR})

########### next target ###############

#include_directories(${CMAKE_SOURCE_DIR}/qross ${KDE4_KJS_INCLUDES} ${CMAKE_SOURCE_DIR}/kjsembed ${KDE4_KDECORE_INCLUDES} ${KDE4_KDEUI_INCLUDES} ${KDE4_KIO_INCLUDES})
set(qrossqts_PART_SRCS interpreter.cpp script.cpp)
set(qrossqts_PART_HEADERS script.h)

add_library(qrossqts${SHLIB_SUFFIX} MODULE ${qrossqts_PART_SRCS})
set_target_properties(qrossqts${SHLIB_SUFFIX} PROPERTIES PREFIX "")
set_property(TARGET qrossqts${SHLIB_SUFFIX} PROPERTY VERSION "0.1")
target_link_libraries(qrossqts${SHLIB_SUFFIX} qrosscore${SHLIB_SUFFIX} Qt5::Script Qt5::Widgets)
install(TARGETS qrossqts${SHLIB_SUFFIX} DESTINATION lib${LIB_SUFFIX})
