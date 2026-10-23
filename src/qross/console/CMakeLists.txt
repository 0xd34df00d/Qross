add_executable(qross${SHLIB_SUFFIX} main.cpp)
target_link_libraries(qross${SHLIB_SUFFIX} PRIVATE Qross::Core Qt6::Widgets)
install(TARGETS qross${SHLIB_SUFFIX} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
