set(qrosscore_SRCS
    qrossconfig.cpp
    interpreter.cpp
    script.cpp
    action.cpp
    actioncollection.cpp
    manager.cpp
    metafunction.cpp
    object.cpp
)

set(qrosscore_HEADERS
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
)

add_library(qrosscore${SHLIB_SUFFIX} SHARED ${qrosscore_SRCS} ${qrosscore_HEADERS})
add_library(Qross::Core ALIAS qrosscore${SHLIB_SUFFIX})

# Headers are included as <qross/core/...>, so the include root is the
# directory containing this project.
target_include_directories(qrosscore${SHLIB_SUFFIX}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(qrosscore${SHLIB_SUFFIX} PUBLIC Qt6::Core Qt6::Gui Qt6::Xml)
set_target_properties(qrosscore${SHLIB_SUFFIX} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    DEFINE_SYMBOL qrosscore_EXPORTS
)

install(TARGETS qrosscore${SHLIB_SUFFIX} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${qrosscore_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qross/core COMPONENT Devel)

configure_file(qrosscore.pc.in ${CMAKE_CURRENT_BINARY_DIR}/qrosscore.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qrosscore.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
