#####################################################################
# Kross Java
#
# Install examples:
#   cmake -DCMAKE_INSTALL_PREFIX=/opt/kde4/ /path/to/kdebindings
#   cmake -DCMAKE_INSTALL_PREFIX=/opt/kde4/ -DENABLE_KROSSJAVA=off /path/to/kdebindings

OPTION(ENABLE_KROSSJAVA "build Kross Java scripting library" OFF)

set(KROSSJAVA_ENABLED "no")

if(ENABLE_KROSSJAVA)
    set(KROSSJAVA_ENABLED "yes")
    add_subdirectory(krossjava)
endif(ENABLE_KROSSJAVA)

message(STATUS "Build Kross Java... " ${KROSSJAVA_ENABLED})
