INCLUDES = -I$(srcdir)/../src/kde -I$(srcdir)/../src/interfaces -I$(srcdir)/../src/gtk -I$(prefix)/include -I$(top_srcdir) $(MOZILLA_INCLUDES) $(all_includes)

AM_CFLAGS = $(GLIB_CFLAGS) $(GTK_CFLAGS)

lib_LTLIBRARIES = libkmozillapart.la

libkmozillapart_la_SOURCES = kmozillapart.cpp
libkmozillapart_la_LDFLAGS = -module $(all_libraries)
libkmozillapart_la_LIBADD = ../src/kde/libkdexparts.la

servicedir = $(kde_servicesdir)
service_DATA = kmozilla.desktop

bin_PROGRAMS = kmozilla #kshell

kmozilla_SOURCES = kmozilla.c kmozilla_ext.c main.c
kmozilla_LDADD = ../src/gtk/libgtkxparts.la $(GTK_LIBS) $(GLIB_LIBS)
kmozilla_LDFLAGS = $(GLIB_LDFLAGS) $(GTK_LDFLAGS) -L$(libdir) -L/usr/lib/mozilla -Wl,--rpath=/usr/lib/mozilla -lgtkembedmoz -lxpcom $(all_libraries)

#kshell_SOURCES = kshell.cpp
#kshell_LDADD = $(top_builddir)/xkparts/kde/libkdexparts.la
#kshell_LDFLAGS = $(all_libraries)

METASOURCES = AUTO

