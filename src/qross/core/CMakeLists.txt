include_directories(${CMAKE_SOURCE_DIR}/..)

FIND_PACKAGE (Qt4 REQUIRED)
SET (QT_USE_QTSCRIPT TRUE)
SET (QT_USE_QTXML TRUE)
INCLUDE (${QT_USE_FILE})

set(qrosscore_LIB_SRCS
   qrossconfig.cpp
   interpreter.cpp
   script.cpp
   action.cpp
   actioncollection.cpp
   manager.cpp
   object.cpp
)

set(qrosscore_LIB_HEADERS
	action.h
	actioncollection.h
	interpreter.h
	manager.h
	script.h
)

QT4_WRAP_CPP (qrosscore_LIB_MOC_SRCS ${qrosscore_LIB_HEADERS})

add_library(qrosscore SHARED ${qrosscore_LIB_SRCS} ${qrosscore_LIB_MOC_SRCS})
target_link_libraries(qrosscore ${QT_LIBRARIES})

# TODO: DESTINATION
#install(TARGETS qrosscore)

install(FILES
	qross_export.h
    qrossconfig.h
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
    DESTINATION ${INCLUDE_INSTALL_DIR}/qross/core COMPONENT Devel)
