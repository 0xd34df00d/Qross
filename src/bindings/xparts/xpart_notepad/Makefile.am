INCLUDES = -I$(srcdir)/../src/kde -I$(srcdir)/../src/interfaces -I$(prefix)/include -I$(top_srcdir) $(all_includes)

#AM_CFLAGS += $(GLIB_CFLAGS) $(GTK_CFLAGS)

bin_PROGRAMS = xp_notepad shell_xparthost

xpart_DIR=$(srcdir)/../src/interfaces
xparthost_DIR=$(srcdir)/../src/interfaces

xp_notepad_SOURCES = xp_notepad.cpp xpart.skel xparthost.stub
xp_notepad_LDADD = ../src/kde/libkdexparts.la
#xp_notepad_LDFLAGS = -L$(prefix)/lib -lxpcom $(all_libraries)
xp_notepad_LDFLAGS = -L$(prefix)/lib $(all_libraries)

shell_xparthost_SOURCES = shell_xparthost.cpp
shell_xparthost_LDADD = $(top_builddir)/xparts/src/kde/libkdexparts.la
shell_xparthost_LDFLAGS = $(all_libraries)

lib_LTLIBRARIES = libxp_notepadpart.la

libxp_notepadpart_la_SOURCES = xp_notepad_factory.cpp
libxp_notepadpart_la_LDFLAGS = -module $(all_libraries)
libxp_notepadpart_la_LIBADD = ../src/kde/libkdexparts.la

servicedir = $(kde_servicesdir)
service_DATA = xp_notepad.desktop

METASOURCES = AUTO 

