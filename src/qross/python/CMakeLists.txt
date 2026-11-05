add_library(qrosspython${SHLIB_SUFFIX} MODULE
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
    gil.h
    ref.h
)
target_link_libraries(qrosspython${SHLIB_SUFFIX} PRIVATE Qross::Core Python3::Python)
target_compile_definitions(qrosspython${SHLIB_SUFFIX} PRIVATE PY_SSIZE_T_CLEAN)
set_target_properties(qrosspython${SHLIB_SUFFIX} PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${QROSS_PLUGIN_BUILD_DIR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

install(TARGETS qrosspython${SHLIB_SUFFIX} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
