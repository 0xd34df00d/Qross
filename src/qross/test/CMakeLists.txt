add_executable(qrosstest testobject.cpp testobject.h main.cpp)
target_link_libraries(qrosstest PRIVATE Qross::Core Qt6::Widgets)

add_executable(tst_metafunction tst_metafunction.cpp)
target_link_libraries(tst_metafunction PRIVATE Qross::Core Qt6::Test)
add_test(NAME metafunction COMMAND tst_metafunction)
