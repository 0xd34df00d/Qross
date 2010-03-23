project(kdebindings)

add_subdirectory(generator)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules )

# search packages used by KDE
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

# the MACRO_OPTIONAL_DEPEND_PACKAGE from KDE4 is broken
macro (OUR_MACRO_OPTIONAL_DEPEND_PACKAGE _name _module_needed)
   set(_packagename Find${_name}.cmake)
   find_file(${_name}_PACKAGE_DEPEND_FOUND ${_packagename} PATHS ${CMAKE_MODULE_PATH} )
   if(NOT ${_name}_PACKAGE_DEPEND_FOUND)
        MESSAGE(STATUS "cmake package ${_packagename} was not found. The package ${_module_needed} is needed to compile all part of this program.")
        set(DEPEND_PACKAGE_${_name} FALSE)
   else(NOT ${_name}_PACKAGE_DEPEND_FOUND)
        set(DEPEND_PACKAGE_${_name} TRUE)
   endif(NOT ${_name}_PACKAGE_DEPEND_FOUND)
endmacro (OUR_MACRO_OPTIONAL_DEPEND_PACKAGE)


add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS} -DQT3_SUPPORT)
include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

macro_optional_find_package(OpenGL)
set(SOPRANO_MIN_VERSION "2.0")
macro_optional_find_package(Soprano)
macro_optional_find_package(Nepomuk)
macro_optional_find_package(KdepimLibs)
macro_optional_find_package(Phonon)
macro_optional_find_package(QScintilla)

# Look for Okular
set( OKULAR_FOUND "no" )
our_macro_optional_depend_package(Okular "Okular")
if(DEPEND_PACKAGE_Okular)
  macro_optional_find_package(Okular)
endif(DEPEND_PACKAGE_Okular)

# Look for Akonadi
our_macro_optional_depend_package(Akonadi "Akonadi")
if(DEPEND_PACKAGE_Akonadi)
  macro_optional_find_package(Akonadi)
endif(DEPEND_PACKAGE_Akonadi)

# Look for KDevelop
set( KDEVPLATFORM_FOUND "no" )
option(WITH_KDevPlatform "Search for KDevPlatform package" OFF)
our_macro_optional_depend_package(KDevPlatform "KDevPlatform")
if(DEPEND_PACKAGE_KDevPlatform)
  macro_optional_find_package(KDevPlatform)
endif(DEPEND_PACKAGE_KDevPlatform)

macro_optional_add_subdirectory(smoke)
macro_optional_add_subdirectory(ruby)
macro_optional_add_subdirectory(python)
macro_optional_add_subdirectory(csharp)
macro_optional_add_subdirectory(java)
macro_optional_add_subdirectory(php)
macro_optional_add_subdirectory(falcon)

macro_display_feature_log()
