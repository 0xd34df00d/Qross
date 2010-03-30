include_directories(${CMAKE_SOURCE_DIR}/kross)

FIND_PACKAGE (Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

set(kross_SRCS main.cpp)
add_executable(kross ${kross_SRCS})

target_link_libraries(kross ${QT_LIBRARIES} krosscore)
# TODO: DESTINATION
#install(TARGETS kross)
