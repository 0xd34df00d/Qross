set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

if (USE_QT5)
	find_package (Qt5Core REQUIRED)
else ()
	find_package (Qt4 REQUIRED)
	include (${QT_USE_FILE})
endif ()

set(qrosstest_SRCS 
   testobject.cpp 
   main.cpp
   )

add_executable(qrosstest ${qrosstest_SRCS})
target_link_libraries(qrosstest ${QT_LIBRARIES} qrosscore${SHLIB_SUFFIX})

if (USE_QT5)
	QT5_USE_MODULES (qrosstest Script Widgets)
endif ()
