cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories( ${QT_INCLUDE_DIR}
			${CMAKE_CURRENT_SOURCE_DIR}
			${CMAKE_CURRENT_SOURCE_DIR}/php )

########### next target ###############

set(uic_bin_SRCS 
   customwidgetsinfo.cpp 
   databaseinfo.cpp 
   driver.cpp 
   treewalker.cpp 
   ui4.cpp 
   uic.cpp 
   validator.cpp 
   ${CMAKE_CURRENT_SOURCE_DIR}/php/phpextractimages.cpp # remove
   ${CMAKE_CURRENT_SOURCE_DIR}/php/phpwritedeclaration.cpp 
   ${CMAKE_CURRENT_SOURCE_DIR}/php/phpwriteincludes.cpp 
   ${CMAKE_CURRENT_SOURCE_DIR}/php/phpwriteicondata.cpp 
   ${CMAKE_CURRENT_SOURCE_DIR}/php/phpwriteicondeclaration.cpp 
   ${CMAKE_CURRENT_SOURCE_DIR}/php/phpwriteiconinitialization.cpp 
   ${CMAKE_CURRENT_SOURCE_DIR}/php/phpwriteinitialization.cpp 
   main.cpp )

add_executable(phpuic ${uic_bin_SRCS})
set_target_properties(phpuic PROPERTIES OUTPUT_NAME phpuic)
set_target_properties(phpuic PROPERTIES COMPILE_FLAGS -DQT_UIC_PHP_GENERATOR)

target_link_libraries(phpuic  ${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY} )

install(TARGETS phpuic DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


########### next target ###############


########### install files ###############
