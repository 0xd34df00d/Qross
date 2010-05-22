include_directories(
    ${CMAKE_SOURCE_DIR}/qross
    ${CMAKE_SOURCE_DIR}/kjsembed
    )
    
FIND_PACKAGE (Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

########### next target ###############

set(qrosskjs_PART_SRCS
   kjsscript.cpp 
   kjsinterpreter.cpp
)

# TODO: add_plugin?
#kde4_add_plugin(qrosskjs ${qrosskjs_PART_SRCS})
#target_link_libraries(qrosskjs ${QT_LIBRARIES} qrosscore kjs kjsembed)
#install(TARGETS qrosskjs DESTINATION ${PLUGIN_INSTALL_DIR})
