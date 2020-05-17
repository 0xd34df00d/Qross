include_directories(${CMAKE_SOURCE_DIR}/..)

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

add_library(qrosscore${SHLIB_SUFFIX} SHARED ${qrosscore_LIB_SRCS})
target_link_libraries(qrosscore${SHLIB_SUFFIX} Qt5::Script Qt5::Xml Qt5::Widgets)
set_property(TARGET qrosscore${SHLIB_SUFFIX} PROPERTY VERSION "0.1")

install(TARGETS qrosscore${SHLIB_SUFFIX} DESTINATION lib${LIB_SUFFIX})

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

include(GNUInstallDirs)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/qrosscore.pc.in ${CMAKE_CURRENT_BINARY_DIR}/qrosscore.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qrosscore.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
