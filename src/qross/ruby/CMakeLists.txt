add_library(qrossruby${SHLIB_SUFFIX} MODULE
    interpreter.cpp
    interpreter.h
    context.cpp
    context.h
    object.cpp
    object.h
    wrapper.cpp
    wrapper.h
    function.cpp
    function.h
    variant.cpp
    variant.h
    call.cpp
    call.h
    rubyapi.h
)
target_link_libraries(qrossruby${SHLIB_SUFFIX} PRIVATE Qross::Core Qt6::Gui Ruby::Ruby)
set_target_properties(qrossruby${SHLIB_SUFFIX} PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${QROSS_PLUGIN_BUILD_DIR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

install(TARGETS qrossruby${SHLIB_SUFFIX} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
