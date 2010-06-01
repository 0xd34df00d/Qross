include_directories(${CMAKE_SOURCE_DIR}/qross)

FIND_PACKAGE (Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

set(qross_SRCS main.cpp)
add_executable(qross ${qross_SRCS})

target_link_libraries(qross ${QT_LIBRARIES} qrosscore)
install(TARGETS qross DESTINATION bin)
