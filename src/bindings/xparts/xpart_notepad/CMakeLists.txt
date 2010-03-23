
include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES}  )


########### next target ###############

set(xp_notepad_SRCS xp_notepad.cpp )

message(FATAL_ERROR "DCOP stuff was removed in kde4, convert it to dbus please")

#kde4_add_dcop_skels(xp_notepad_SRCS xpart.h )
#kde4_add_dcop_stubs(xp_notepad_SRCS xparthost.h )

kde4_add_executable(xp_notepad ${xp_notepad_SRCS})

target_link_libraries(xp_notepad  ${KDE4_KDECORE_LIBS} kdexparts )

install(TARGETS xp_notepad DESTINATION ${BIN_INSTALL_DIR})


########### next target ###############

set(shell_xparthost_SRCS shell_xparthost.cpp )

kde4_add_executable(shell_xparthost ${shell_xparthost_SRCS})

target_link_libraries(shell_xparthost  ${KDE4_KDECORE_LIBS} kdexparts )

install(TARGETS shell_xparthost DESTINATION ${BIN_INSTALL_DIR})


########### next target ###############

set(xp_notepadpart_LIB_SRCS xp_notepad_factory.cpp )

kde4_add_library(xp_notepadpart SHARED ${xp_notepadpart_LIB_SRCS})

target_link_libraries(xp_notepadpart  ${KDE4_KDECORE_LIBS} kdexparts )

set_target_properties(xp_notepadpart PROPERTIES VERSION 1.0.0 SOVERSION 1 )
install(TARGETS xp_notepadpart DESTINATION ${LIB_INSTALL_DIR} )


########### install files ###############

install( FILES  xp_notepad.desktop DESTINATION ${SERVICES_INSTALL_DIR} )



#original Makefile.am contents follow:

#INCLUDES = -I$(srcdir)/../src/kde -I$(srcdir)/../src/interfaces -I$(prefix)/include -I$(top_srcdir) $(all_includes)
#
##AM_CFLAGS += $(GLIB_CFLAGS) $(GTK_CFLAGS)
#
#bin_PROGRAMS = xp_notepad shell_xparthost
#
#xpart_DIR=$(srcdir)/../src/interfaces
#xparthost_DIR=$(srcdir)/../src/interfaces
#
#xp_notepad_SOURCES = xp_notepad.cpp xpart.skel xparthost.stub
#xp_notepad_LDADD = ../src/kde/libkdexparts.la
##xp_notepad_LDFLAGS = -L$(prefix)/lib -lxpcom $(all_libraries)
#xp_notepad_LDFLAGS = -L$(prefix)/lib $(all_libraries)
#
#shell_xparthost_SOURCES = shell_xparthost.cpp
#shell_xparthost_LDADD = $(top_builddir)/xparts/src/kde/libkdexparts.la
#shell_xparthost_LDFLAGS = $(all_libraries)
#
#lib_LTLIBRARIES = libxp_notepadpart.la
#
#libxp_notepadpart_la_SOURCES = xp_notepad_factory.cpp
#libxp_notepadpart_la_LDFLAGS = -module $(all_libraries)
#libxp_notepadpart_la_LIBADD = ../src/kde/libkdexparts.la
#
#servicedir = $(kde_servicesdir)
#service_DATA = xp_notepad.desktop
#
#METASOURCES = AUTO 
#
