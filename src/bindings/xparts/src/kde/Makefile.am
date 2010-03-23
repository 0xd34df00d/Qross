
INCLUDES = -I$(srcdir)/../interfaces $(all_includes)

lib_LTLIBRARIES = libkdexparts.la

libkdexparts_la_SOURCES = xparthost_kpart.cpp xparthost.skel xpart.stub \
	kbrowsersignals.cpp xbrowsersignals.skel xbrowserextension.stub
libkdexparts_la_LIBADD = $(LIB_KPARTS)
libkdexparts_la_LDFLAGS = $(all_libraries) -no-undefined -version-info 1:0 

xpart_DIR=$(srcdir)/../interfaces
xparthost_DIR=$(srcdir)/../interfaces
xbrowsersignals_DIR=$(srcdir)/../interfaces
xbrowserextension_DIR=$(srcdir)/../interfaces

METASOURCES = AUTO

