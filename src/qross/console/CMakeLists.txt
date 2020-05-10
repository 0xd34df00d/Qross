include_directories(${CMAKE_SOURCE_DIR}/qross)

find_package (Qt5Core REQUIRED)

set(qross_SRCS main.cpp)
add_executable(qross${SHLIB_SUFFIX} ${qross_SRCS})

target_link_libraries(qross${SHLIB_SUFFIX} ${QT_LIBRARIES}
	qrosscore${SHLIB_SUFFIX})
install(TARGETS qross${SHLIB_SUFFIX} DESTINATION bin)

QT5_USE_MODULES (qross${SHLIB_SUFFIX} Script Widgets)
