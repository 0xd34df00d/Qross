INCLUDES = $(GLIB_INCLUDES) -I$(prefix)/include -I$(top_srcdir) $(all_includes)

AM_CFLAGS = $(GLIB_CFLAGS) $(GTK_CFLAGS)
AM_CXXFLAGS = $(GLIB_CFLAGS) $(GTK_CFLAGS)

lib_LTLIBRARIES = libgtkxparts.la

libgtkxparts_la_SOURCES = gtkpart.c gtkbrowserextension.c
libgtkxparts_la_LIBADD = $(GTK_LIBS) $(GLIB_LIBS) $(top_builddir)/dcopc/libdcopc.la
libgtkxparts_la_LDFLAGS = -L$(prefix)/lib $(all_libraries) -no-undefined

gtkxpartsinclude_HEADERS = gtkpart.h gtkbrowserextension.h
gtkxpartsincludedir = $(includedir)/xkparts
