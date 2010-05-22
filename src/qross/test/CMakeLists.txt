set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

FIND_PACKAGE (Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

set(qrosstest_SRCS 
   testobject.cpp 
   main.cpp
   )
   
QT4_WRAP_CPP (qrosstest_LIB_MOC_SRCS "testobject.h")
   
add_executable(qrosstest ${qrosstest_SRCS} ${qrosstest_LIB_MOC_SRCS})
target_link_libraries(qrosstest ${QT_LIBRARIES} qrosscore)
