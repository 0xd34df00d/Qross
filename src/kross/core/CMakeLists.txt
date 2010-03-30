include_directories(${CMAKE_SOURCE_DIR})

FIND_PACKAGE (Qt4 REQUIRED)
SET (QT_USE_QTSCRIPT TRUE)
SET (QT_USE_QTXML TRUE)
INCLUDE (${QT_USE_FILE})

set(krosscore_LIB_SRCS
   krossconfig.cpp
   interpreter.cpp
   script.cpp
   action.cpp
   actioncollection.cpp
   manager.cpp
   object.cpp
)

add_library(krosscore SHARED ${krosscore_LIB_SRCS})
target_link_libraries(krosscore ${QT_LIBRARIES})

set_target_properties(krosscore PROPERTIES VERSION ${GENERIC_LIB_VERSION} 
                                SOVERSION ${GENERIC_LIB_SOVERSION}
                     )

# TODO: DESTINATION
#install(TARGETS krosscore)

install(FILES
    kross_export.h
    krossconfig.h
    errorinterface.h
    childreninterface.h
    wrapperinterface.h
    metatype.h
    metafunction.h
    interpreter.h
    script.h
    action.h
    actioncollection.h
    manager.h
    object.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/kross/core COMPONENT Devel)
