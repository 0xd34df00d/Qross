project(qrossruby)
cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(RUBY_LIBRARY /usr/lib64/libruby.so.1.8)
find_package(Ruby)

include_directories( ${RUBY_INCLUDE_PATH}
    ${QT_INCLUDE_DIR}
    ${QT_QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
	)

set(qrossruby_PART_SRCS
   rubyvariant.cpp
   rubyinterpreter.cpp
   rubyextension.cpp
   rubyscript.cpp
   rubymodule.cpp
   rubycallcache.cpp
   rubyobject.cpp
   )

add_library(qrossruby MODULE ${qrossruby_PART_SRCS})
set_target_properties(qrossruby PROPERTIES PREFIX "")
target_link_libraries(qrossruby ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
	${KDE4_QROSSCORE_LIBS} ${RUBY_LIBRARY} qrosscore)
install(TARGETS qrossruby DESTINATION lib)
