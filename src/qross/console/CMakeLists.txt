include_directories(${CMAKE_SOURCE_DIR}/qross)

set(qross_SRCS main.cpp)
add_executable(qross${SHLIB_SUFFIX} ${qross_SRCS})

target_link_libraries(qross${SHLIB_SUFFIX} qrosscore${SHLIB_SUFFIX} Qt5::Script Qt5::Widgets)
install(TARGETS qross${SHLIB_SUFFIX} DESTINATION bin)
