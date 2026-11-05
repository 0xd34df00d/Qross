add_library(qrossjs${SHLIB_SUFFIX} MODULE
    interpreter.cpp
    interpreter.h
    context.cpp
    context.h
    object.cpp
    object.h
)
target_link_libraries(qrossjs${SHLIB_SUFFIX} PRIVATE Qross::Core Qt6::Qml)
set_target_properties(qrossjs${SHLIB_SUFFIX} PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${QROSS_PLUGIN_BUILD_DIR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

install(TARGETS qrossjs${SHLIB_SUFFIX} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
