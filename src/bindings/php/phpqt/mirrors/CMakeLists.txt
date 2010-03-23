PROJECT(mirrors)

find_package(Qt4 REQUIRED)
add_definitions(${QT_DEFINITIONS})
# include_directories(${QT_INCLUDE_DIR})
include(${QT_USE_FILE})

include_directories(
    ${QT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/smoke
    ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(mirrors_SRCS
	main.cpp
	smokemodel.cpp
	SmokeItem.cpp
)

SET(mirrors_UIS mirrorsMainWindow.ui)

#QT4_AUTOMOC(smokemodel.cpp)

qt4_automoc(${mirrors_SRCS})
qt4_wrap_ui(mirrors_UIC_H ${mirrors_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

ADD_EXECUTABLE(mirrors ${mirrors_SRCS} ${mirrors_UIC_H})
target_link_libraries(mirrors ${QT_LIBRARIES} smokeqt)

install(TARGETS mirrors DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
