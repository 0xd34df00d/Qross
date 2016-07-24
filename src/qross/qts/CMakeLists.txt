include_directories(${CMAKE_SOURCE_DIR}/..)

if (USE_QT5)
	find_package (Qt5Core REQUIRED)
else ()
	find_package (Qt4 REQUIRED)
	set (QT_USE_QTUITOOLS TRUE)
	set (QT_USE_QTSCRIPT TRUE)
	include (${QT_USE_FILE})
endif ()

########### next target ###############
set(qrossqtsplugin_LIB_SRCS plugin.cpp)
add_library(qrossqtsplugin SHARED ${qrossqtsplugin_LIB_SRCS})
set_property(TARGET qrossqtsplugin PROPERTY VERSION "0.1")


if (USE_QT5)
	get_target_property(QMAKE_EXECUTABLE Qt5::qmake LOCATION)
	function(QUERY_QMAKE VAR RESULT)
	exec_program(${QMAKE_EXECUTABLE} ARGS "-query ${VAR}" RETURN_VALUE return_code OUTPUT_VARIABLE output )
	if (NOT return_code)
		file(TO_CMAKE_PATH "${output}" output)
		set(${RESULT} ${output} PARENT_SCOPE)
	endif ()
	endfunction(QUERY_QMAKE)

	query_qmake(QT_INSTALL_PLUGINS QT_PLUGINS_DIR)
else ()
	target_link_libraries(qrossqtsplugin ${QT_LIBRARIES} qrosscore${SHLIB_SUFFIX})
endif ()

install(TARGETS qrossqtsplugin DESTINATION ${QT_PLUGINS_DIR}/script)

if (USE_QT5)
	QT5_USE_MODULES (qrossqtsplugin Script UiTools Widgets)
endif ()

########### next target ###############

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/qross)
set(qrossqtstest_SRCS main.cpp)
add_executable(qrossqtstest ${qrossqtstest_SRCS})

target_link_libraries(qrossqtstest ${QT_LIBRARIES})

if (USE_QT5)
	QT5_USE_MODULES (qrossqtstest Gui Script Widgets)
endif ()
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
target_link_libraries(qrossqts${SHLIB_SUFFIX} ${QT_LIBRARIES}
	qrosscore${SHLIB_SUFFIX})
install(TARGETS qrossqts${SHLIB_SUFFIX} DESTINATION lib${LIB_SUFFIX})

if (USE_QT5)
	QT5_USE_MODULES (qrossqts${SHLIB_SUFFIX} Script Widgets) 
endif ()
