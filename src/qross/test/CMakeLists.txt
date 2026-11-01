add_executable(qrosstest testobject.cpp testobject.h main.cpp)
target_link_libraries(qrosstest PRIVATE Qross::Core Qt6::Widgets)

add_executable(tst_metafunction tst_metafunction.cpp)
target_link_libraries(tst_metafunction PRIVATE Qross::Core Qt6::Test)
add_test(NAME metafunction COMMAND tst_metafunction)

# The runner must fail for a file that no interpreter claims.
qross_add_script_test(qrosstest_rejects_unknown_files ${CMAKE_CURRENT_SOURCE_DIR}/testobject.h)
set_tests_properties(qrosstest_rejects_unknown_files PROPERTIES WILL_FAIL TRUE)

if(QROSS_WITH_JAVASCRIPT)
    add_executable(tst_javascript tst_javascript.cpp)
    target_link_libraries(tst_javascript PRIVATE Qross::Core Qt6::Qml Qt6::Test)
    add_test(NAME javascript COMMAND tst_javascript)
    qross_set_test_environment(javascript)

    qross_add_script_test(javascript_unittest ${CMAKE_CURRENT_SOURCE_DIR}/unittest.js)
endif()
