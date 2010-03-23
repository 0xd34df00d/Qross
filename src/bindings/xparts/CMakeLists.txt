
add_subdirectory( src )
add_subdirectory( xpart_notepad )

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES}  )


########### install files ###############




#original Makefile.am contents follow:

#
#SUBDIRS = src xpart_notepad
#
#EXTRA_DIST = Makefile.cvs glib.m4 gtk.m4 
#
#dist-hook:
#	cd $(top_distdir) && perl $(top_srcdir)/am_edit
