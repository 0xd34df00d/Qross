set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

FIND_PACKAGE (Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

set(krosstest_SRCS 
   testobject.cpp 
   main.cpp
   )
   
add_executable(krosstest ${krosstest_SRCS})
target_link_libraries(krosstest ${QT_LIBRARIES} krosscore)
