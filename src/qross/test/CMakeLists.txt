set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

find_package (Qt5Core REQUIRED)

set(qrosstest_SRCS
   testobject.cpp
   main.cpp
   )

add_executable(qrosstest ${qrosstest_SRCS})
target_link_libraries(qrosstest ${QT_LIBRARIES} qrosscore${SHLIB_SUFFIX})

QT5_USE_MODULES (qrosstest Script Widgets)
