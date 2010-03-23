PROJECT(PHP-Qt)

OPTION(PHPQT_MOC_DEBUG "debug moc" OFF)
OPTION(PHPQT_DEBUG "" OFF)
OPTION(PHPQT_CONSTRUCT_DEBUG "" OFF)
OPTION(PHPQT_DESTRUCT_DEBUG "" OFF)
OPTION(PHPQT_METHOD_DEBUG "" OFF)
OPTION(PHPQT_STATICMETHOD_DEBUG "" OFF)
OPTION(PHPQT_VIRTUALMETHOD_DEBUG "" OFF)
OPTION(PHPQT_SIGNAL_DEBUG "" OFF)
OPTION(PHPQT_SLOT_DEBUG "" OFF)
OPTION(PHPQT_MAPPTR_DEBUG "" OFF)
OPTION(PHPQT_UNMAPPTR_DEBUG "" OFF)
OPTION(PHPQT_MAPHANDLE_DEBUG "" OFF)
OPTION(PHPQT_UNMAPHANDLE_DEBUG "" OFF)

IF (CMAKE_BUILD_TYPE MATCHES "Debug")
 SET(PHPQT_DEBUG "1") 
ENDIF (CMAKE_BUILD_TYPE MATCHES "Debug")

CONFIGURE_FILE(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

include_directories( 
    ${QT_INCLUDE_DIR} 
    ${CMAKE_SOURCE_DIR}/smoke
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BUILD_DIR}
    ${PHP5_INCLUDE_DIR}
    ${PHP5_MAIN_INCLUDE_DIR}
    ${PHP5_TSRM_INCLUDE_DIR}
    ${PHP5_ZEND_INCLUDE_DIR}
    ${PHP5_REGEX_INCLUDE_DIR}
    ${PHP5_EXT_INCLUDE_DIR}
    ${PHP5_DATE_INCLUDE_DIR}
    ${PHP5_STANDARD_INCLUDE_DIR}
    )

set(phpqt_LIB_SRCS
    zphp/functions.cpp
    zphp/z_extension.cpp
    zphp/z_handler.cpp
    zphp/qstring.cpp
    phpqt_internals.cpp
    smokephp.cpp
    marshall_types.cpp
    handlers.cpp
    context.cpp
    MethodCallBase.cpp
    VirtualMethodCall.cpp
    EmitSignal.cpp
    MethodCall.cpp
    InvokeSlot.cpp
    MethodReturnValueBase.cpp
    MethodReturnValue.cpp
    VirtualMethodReturnValue.cpp
    unittests.cpp
    )

set(phpqt_MOC_HEADER
  unittests.h
)

qt_wrap_cpp( php_qt phpqt_LIB_SRCS ${phpqt_MOC_HEADER} )

add_library(php_qt MODULE ${phpqt_LIB_SRCS})

target_link_libraries(php_qt 
			     ${QT_QTCORE_LIBRARY} 
			     ${QT_QTTEST_LIBRARY}
			     smokeqt
)

if(${CMAKE_MODULE_LINKER_FLAGS} MATCHES "no-undefined")
  string(REPLACE "-Wl,--no-undefined" " " CMAKE_MODULE_LINKER_FLAGS ${CMAKE_MODULE_LINKER_FLAGS})
  set_target_properties(php_qt PROPERTIES PREFIX "")
  IF(APPLE)
    set_target_properties(php_qt PROPERTIES PREFIX "" LINK_FLAGS ${CMAKE_SHARED_MODULE_CREATE_C_FLAGS} SUFFIX ".so")
  ENDIF(APPLE)
#  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")
else(${CMAKE_MODULE_LINKER_FLAGS} MATCHES "no-undefined")
  set_target_properties(php_qt PROPERTIES PREFIX "")
  IF(APPLE)
    set_target_properties(php_qt PROPERTIES PREFIX "" LINK_FLAGS ${CMAKE_SHARED_MODULE_CREATE_C_FLAGS} SUFFIX ".so")
  ENDIF(APPLE)
endif(${CMAKE_MODULE_LINKER_FLAGS} MATCHES "no-undefined")


install(TARGETS php_qt DESTINATION ${PHP5_EXTENSION_DIR}/ )
