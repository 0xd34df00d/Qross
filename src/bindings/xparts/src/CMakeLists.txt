
add_subdirectory( interfaces )
add_subdirectory( kde )

message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}: skipped subdir $(SUPPORTGTKDIR)")
include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES}  )


########### install files ###############




#original Makefile.am contents follow:

#
#if include_GTK_support
#SUPPORTGTKDIR=gtk
#endif
#
#SUBDIRS = interfaces kde $(SUPPORTGTKDIR)
#
