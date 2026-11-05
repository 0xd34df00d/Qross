# Points a test at the plugins of this build tree. The offscreen platform
# lets qrosstest, which needs a QApplication for its QWidget slots, run
# without a display.
function(qross_set_test_environment name)
    set_tests_properties(${name} PROPERTIES
        ENVIRONMENT "QROSS_PLUGIN_PATH=${QROSS_PLUGIN_BUILD_DIR};QT_QPA_PLATFORM=offscreen"
    )
endfunction()

# Runs SCRIPT through qrosstest.
function(qross_add_script_test name script)
    if(NOT BUILD_TESTING)
        return()
    endif()
    add_test(NAME ${name} COMMAND qrosstest ${script})
    qross_set_test_environment(${name})
endfunction()
