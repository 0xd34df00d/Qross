GET_FILENAME_COMPONENT(_cmake_module_path ${CMAKE_CURRENT_LIST_FILE}  PATH)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${_cmake_module_path}/pykde4/cmake/modules)

macro_optional_find_package(PythonLibrary)

#####################################################################
# Kross Python
#
# Install examples:
#   cmake -DCMAKE_INSTALL_PREFIX=/opt/kde4/ /path/to/kdebindings
#   cmake -DCMAKE_INSTALL_PREFIX=/opt/kde4/ -DENABLE_KROSSPYTHON=off /path/to/kdebindings
#   cmake -DCMAKE_INSTALL_PREFIX=/opt/kde4/ -DCMAKE_BUILD_TYPE=debugfull -DPYTHON_LIBRARY=/usr/lib/python2.5/config/libpython2.5.so -DPYTHON_LIBRARIES=/usr/lib/python2.5/config/libpython2.5.so -DPYTHON_INCLUDE_PATH=/usr/include/python2.5 /path/to/kdebindings

OPTION(ENABLE_KROSSPYTHON "build Kross Python scripting library" ON)
#OPTION(ENABLE_KROSSPYTHON "build Kross Python scripting library" OFF)

set(KROSSPYTHON_ENABLED "no")
if(ENABLE_KROSSPYTHON)
    if(PYTHON_LIBRARIES AND PYTHON_INCLUDE_PATH)
        #EXEC_PROGRAM(python ARGS -c "import distutils.sysconfig;print distutils.sysconfig.get_config_var('VERSION')" OUTPUT_VARIABLE PythonVersionOutVar RETURN_VALUE PythonVersionRetVal)
        add_subdirectory(krosspython)
        set(KROSSPYTHON_ENABLED "yes")
    endif(PYTHON_LIBRARIES AND PYTHON_INCLUDE_PATH)
    message(STATUS "Python Libraries: " ${PYTHON_LIBRARIES})
    message(STATUS "Python Include Path: " ${PYTHON_INCLUDE_PATH})
endif(ENABLE_KROSSPYTHON)
message(STATUS "Build Kross Python... " ${KROSSPYTHON_ENABLED})

#####################################################################
# PyKDE
#
# Install examples:
#   cmake -DCMAKE_INSTALL_PREFIX=/opt/kde4/ /path/to/kdebindings
#   cmake -DCMAKE_INSTALL_PREFIX=/opt/kde4/ -DENABLE_PYKDE4=off /path/to/kdebindings

OPTION(ENABLE_PYKDE4 "build PyKDE4" ON)
set(PYKDE4_ENABLED "no")
if(ENABLE_PYKDE4)
    IF(PYTHON_LIBRARIES AND PYTHON_INCLUDE_PATH)

        macro_optional_find_package(SIP)
        IF(SIP_VERSION STRLESS "040900")    # These version numbers also appear in pykde4/CMakeLists.txt
            MESSAGE(STATUS "The version of SIP found is too old. 4.9.0 or later is needed.")
            SET(SIP_FOUND FALSE)
        ENDIF(SIP_VERSION STRLESS "040900")
        IF(SIP_FOUND)

            macro_optional_find_package(PyQt4)
            IF(PYQT4_VERSION STRLESS "040700")  # These version numbers also appear in pykde4/CMakeLists.txt
                MESSAGE(STATUS "The version of PyQt found is too old. 4.7.0 or later is required.")
                SET(PYQT4_FOUND FALSE)
            ENDIF(PYQT4_VERSION STRLESS "040700")
            IF(PYQT4_FOUND)
                add_subdirectory(pykde4)
                set(PYKDE4_ENABLED "yes")
            ENDIF(PYQT4_FOUND)
        ENDIF(SIP_FOUND)
    ENDIF(PYTHON_LIBRARIES AND PYTHON_INCLUDE_PATH)
endif(ENABLE_PYKDE4)
message(STATUS "Build PyKDE4... " ${PYKDE4_ENABLED})
