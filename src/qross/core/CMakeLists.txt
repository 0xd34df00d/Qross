include_directories(${CMAKE_SOURCE_DIR}/..)

if (USE_QT5)
	find_package (Qt5Core REQUIRED)
else ()
	find_package (Qt4 REQUIRED)
	set (QT_USE_QTSCRIPT TRUE)
	set (QT_USE_QTXML TRUE)
	include (${QT_USE_FILE})
endif ()

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

if (USE_QT5)
	QT5_WRAP_CPP (qrosscore_LIB_MOC_SRCS ${qrosscore_LIB_HEADERS})
else ()
	QT4_WRAP_CPP (qrosscore_LIB_MOC_SRCS ${qrosscore_LIB_HEADERS})
endif ()

add_library(qrosscore SHARED ${qrosscore_LIB_SRCS} ${qrosscore_LIB_MOC_SRCS})
target_link_libraries(qrosscore ${QT_LIBRARIES})
set_property(TARGET qrosscore PROPERTY VERSION "0.1")

install(TARGETS qrosscore DESTINATION lib${LIB_SUFFIX})

install(FILES FindQrosscore.cmake DESTINATION share/cmake/Modules)
install(FILES FindQrosscore.cmake DESTINATION share/leechcraft/cmake)

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
    DESTINATION include/qross/core COMPONENT Devel)

if (USE_QT5)
	QT5_USE_MODULES (qrosscore Script Xml Widgets)
endif ()
