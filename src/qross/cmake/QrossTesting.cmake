# Runs SCRIPT through qrosstest with the plugins of this build tree. The
# runner needs a QGuiApplication because Action derives from QAction, hence
# the offscreen platform.
function(qross_add_script_test name script)
    if(NOT BUILD_TESTING)
        return()
    endif()
    add_test(NAME ${name} COMMAND qrosstest ${script})
    set_tests_properties(${name} PROPERTIES
        ENVIRONMENT "QROSS_PLUGIN_PATH=${QROSS_PLUGIN_BUILD_DIR};QT_QPA_PLATFORM=offscreen"
    )
endfunction()
