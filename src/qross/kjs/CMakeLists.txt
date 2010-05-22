include_directories(
    ${CMAKE_SOURCE_DIR}/kross
    ${CMAKE_SOURCE_DIR}/kjsembed
    )
    
FIND_PACKAGE (Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})

########### next target ###############

set(krosskjs_PART_SRCS
   kjsscript.cpp 
   kjsinterpreter.cpp
)

# TODO: add_plugin?
#kde4_add_plugin(krosskjs ${krosskjs_PART_SRCS})
#target_link_libraries(krosskjs ${QT_LIBRARIES} krosscore kjs kjsembed)
#install(TARGETS krosskjs DESTINATION ${PLUGIN_INSTALL_DIR})
