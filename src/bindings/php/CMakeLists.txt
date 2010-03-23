OPTION(ENABLE_PHP-QT "build PHP-Qt" OFF)

if( ENABLE_PHP-QT)

   include(FindPHP5)

   if( PHP5_FOUND)
      add_subdirectory(phpqt)
   else(PHP5_FOUND)
      MESSAGE(STATUS "PHP5 could not be found! phpqt will not build")
   endif(PHP5_FOUND)
endif( ENABLE_PHP-QT)
