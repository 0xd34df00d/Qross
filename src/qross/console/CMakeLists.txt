include_directories(${CMAKE_SOURCE_DIR}/qross)

if (USE_QT5)
	find_package (Qt5Core REQUIRED)
else ()
	find_package (Qt4 REQUIRED)
	include (${QT_USE_FILE})
endif ()

set(qross_SRCS main.cpp)
add_executable(qross${SHLIB_SUFFIX} ${qross_SRCS})

target_link_libraries(qross${SHLIB_SUFFIX} ${QT_LIBRARIES}
	qrosscore${SHLIB_SUFFIX})
install(TARGETS qross${SHLIB_SUFFIX} DESTINATION bin)

if (USE_QT5)
	QT5_USE_MODULES (qross${SHLIB_SUFFIX} Script Widgets)
endif ()
