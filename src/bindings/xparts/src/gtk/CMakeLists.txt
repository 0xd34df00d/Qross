
include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES}  )


########### next target ###############

set(gtkxparts_LIB_SRCS gtkpart.c gtkbrowserextension.c )

kde4_add_library(gtkxparts SHARED ${gtkxparts_LIB_SRCS})

target_link_libraries(gtkxparts  ${KDE4_KDECORE_LIBS} dcopc )

set_target_properties(gtkxparts PROPERTIES VERSION 1.0.0 SOVERSION 1 )
install(TARGETS gtkxparts DESTINATION ${LIB_INSTALL_DIR} )


########### install files ###############

install( FILES  gtkpart.h gtkbrowserextension.h DESTINATION ${INCLUDE_INSTALL_DIR}/xkparts )



#original Makefile.am contents follow:

#INCLUDES = $(GLIB_INCLUDES) -I$(prefix)/include -I$(top_srcdir) $(all_includes)
#
#AM_CFLAGS = $(GLIB_CFLAGS) $(GTK_CFLAGS)
#AM_CXXFLAGS = $(GLIB_CFLAGS) $(GTK_CFLAGS)
#
#lib_LTLIBRARIES = libgtkxparts.la
#
#libgtkxparts_la_SOURCES = gtkpart.c gtkbrowserextension.c
#libgtkxparts_la_LIBADD = $(GTK_LIBS) $(GLIB_LIBS) $(top_builddir)/dcopc/libdcopc.la
#libgtkxparts_la_LDFLAGS = -L$(prefix)/lib $(all_libraries) -no-undefined
#
#gtkxpartsinclude_HEADERS = gtkpart.h gtkbrowserextension.h
#gtkxpartsincludedir = $(includedir)/xkparts
