include_directories(${CMAKE_SOURCE_DIR})

FIND_PACKAGE (Qt4 REQUIRED)
SET (QT_USE_QTSCRIPT TRUE)
SET (QT_USE_QTXML TRUE)
INCLUDE (${QT_USE_FILE})

set(krossui_LIB_SRCS
   model.cpp
   view.cpp
   plugin.cpp
#   guiclient.cpp
   )

add_library(krossui SHARED ${krossui_LIB_SRCS})
target_link_libraries(krossui krosscore ${QT_LIBRARIES})
set_target_properties(krossui PROPERTIES VERSION ${GENERIC_LIB_VERSION} 
                                         SOVERSION ${GENERIC_LIB_SOVERSION}
                     )

# TODO: DESTINATION
#install(TARGETS krossui)

########### install files ###############

#install(FILES guiclient.h model.h view.h DESTINATION ${INCLUDE_INSTALL_DIR}/kross/ui)
install(FILES model.h view.h plugin.h DESTINATION ${INCLUDE_INSTALL_DIR}/kross/ui COMPONENT Devel)
