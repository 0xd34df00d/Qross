include_directories(${CMAKE_SOURCE_DIR}/qross)

if (USE_QT5)
	find_package (Qt5Core REQUIRED)
else ()
	find_package (Qt4 REQUIRED)
	include (${QT_USE_FILE})
endif ()

set(qross_SRCS main.cpp)
add_executable(qross ${qross_SRCS})

target_link_libraries(qross ${QT_LIBRARIES} qrosscore)
install(TARGETS qross DESTINATION bin)

if (USE_QT5)
	QT5_USE_MODULES (qross Script Widgets)
endif ()
