add_executable(qrosstest testobject.cpp testobject.h main.cpp)
target_link_libraries(qrosstest PRIVATE Qross::Core Qt6::Widgets)
