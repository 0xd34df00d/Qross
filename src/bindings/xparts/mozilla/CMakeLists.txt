
include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES}  )


########### next target ###############

set(kmozillapart_LIB_SRCS kmozillapart.cpp )

kde4_add_library(kmozillapart SHARED ${kmozillapart_LIB_SRCS})

target_link_libraries(kmozillapart  ${KDE4_KDECORE_LIBS} kdexparts )

set_target_properties(kmozillapart PROPERTIES VERSION 1.0.0 SOVERSION 1 )
install(TARGETS kmozillapart DESTINATION ${LIB_INSTALL_DIR} )


########### next target ###############

set(kmozilla_SRCS kmozilla.c kmozilla_ext.c main.c )

kde4_add_executable(kmozilla ${kmozilla_SRCS})

target_link_libraries(kmozilla  ${KDE4_KDECORE_LIBS} gtkxparts gtkembedmoz xpcom )

install(TARGETS kmozilla DESTINATION ${BIN_INSTALL_DIR})


########### install files ###############

install( FILES  kmozilla.desktop DESTINATION ${SERVICES_INSTALL_DIR} )



#original Makefile.am contents follow:

#INCLUDES = -I$(srcdir)/../src/kde -I$(srcdir)/../src/interfaces -I$(srcdir)/../src/gtk -I$(prefix)/include -I$(top_srcdir) $(MOZILLA_INCLUDES) $(all_includes)
#
#AM_CFLAGS = $(GLIB_CFLAGS) $(GTK_CFLAGS)
#
#lib_LTLIBRARIES = libkmozillapart.la
#
#libkmozillapart_la_SOURCES = kmozillapart.cpp
#libkmozillapart_la_LDFLAGS = -module $(all_libraries)
#libkmozillapart_la_LIBADD = ../src/kde/libkdexparts.la
#
#servicedir = $(kde_servicesdir)
#service_DATA = kmozilla.desktop
#
#bin_PROGRAMS = kmozilla #kshell
#
#kmozilla_SOURCES = kmozilla.c kmozilla_ext.c main.c
#kmozilla_LDADD = ../src/gtk/libgtkxparts.la $(GTK_LIBS) $(GLIB_LIBS)
#kmozilla_LDFLAGS = $(GLIB_LDFLAGS) $(GTK_LDFLAGS) -L$(libdir) -L/usr/lib/mozilla -Wl,--rpath=/usr/lib/mozilla -lgtkembedmoz -lxpcom $(all_libraries)
#
##kshell_SOURCES = kshell.cpp
##kshell_LDADD = $(top_builddir)/xkparts/kde/libkdexparts.la
##kshell_LDFLAGS = $(all_libraries)
#
#METASOURCES = AUTO
#
