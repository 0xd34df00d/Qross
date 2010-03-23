
include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES}  )


########### install files ###############

install( FILES  xpart.h xparthost.h DESTINATION ${INCLUDE_INSTALL_DIR}/xkparts )



#original Makefile.am contents follow:

#
#xkpartsinclude_HEADERS = xpart.h xparthost.h
#xkpartsincludedir = $(includedir)/xkparts
