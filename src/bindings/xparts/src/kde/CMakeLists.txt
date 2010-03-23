
include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES}  )


########### next target ###############

set(kdexparts_LIB_SRCS xparthost_kpart.cpp kbrowsersignals.cpp )

message(FATAL_ERROR "DCOP stuff was removed in kde4, convert it to dbus please")
#kde4_add_dcop_skels(kdexparts_LIB_SRCS xparthost.h xbrowsersignals.h )
#kde4_add_dcop_stubs(kdexparts_LIB_SRCS xpart.h xbrowserextension.h )

kde4_add_library(kdexparts SHARED ${kdexparts_LIB_SRCS})

target_link_libraries(kdexparts  ${KDE4_KDECORE_LIBS} ${KDE4_KPARTS_LIBS} )

set_target_properties(kdexparts PROPERTIES VERSION 1.0.0 SOVERSION 1 )
install(TARGETS kdexparts DESTINATION ${LIB_INSTALL_DIR} )


########### install files ###############




#original Makefile.am contents follow:

#
#INCLUDES = -I$(srcdir)/../interfaces $(all_includes)
#
#lib_LTLIBRARIES = libkdexparts.la
#
#libkdexparts_la_SOURCES = xparthost_kpart.cpp xparthost.skel xpart.stub \
#	kbrowsersignals.cpp xbrowsersignals.skel xbrowserextension.stub
#libkdexparts_la_LIBADD = $(LIB_KPARTS)
#libkdexparts_la_LDFLAGS = $(all_libraries) -no-undefined -version-info 1:0 
#
#xpart_DIR=$(srcdir)/../interfaces
#xparthost_DIR=$(srcdir)/../interfaces
#xbrowsersignals_DIR=$(srcdir)/../interfaces
#xbrowserextension_DIR=$(srcdir)/../interfaces
#
#METASOURCES = AUTO
#
