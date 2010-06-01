CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# the core library
add_subdirectory( core )
# the ui library
add_subdirectory( ui )
# optional modules
#add_subdirectory( modules )
# commandline-prog to run scripts
add_subdirectory( console )

# unittests and such stuff
add_subdirectory( test )

# KDE Javascript using kjs and kjsembed
# test kjsembed I think
#add_subdirectory( kjs )

# QtScript backend
add_subdirectory( qts )
