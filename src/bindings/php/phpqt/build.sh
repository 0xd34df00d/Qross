#!/bin/sh

# this script is for building PHP-Qt outside of SVN

# rename the cmake files
if test -f CMakeLists.txt.php-qt
then
    echo "renaming cmake file: "
    mv CMakeLists.txt CMakeLists.txt.kde
    echo "CMakeLists.txt -> CMakeLists.txt.kde"
    mv CMakeLists.txt.php-qt CMakeLists.txt
    echo "CMakeLists.txt.php-qt -> CMakeLists.txt"
fi

# check out smoke and kalyptus
./prepare_svn.sh

# create build dir
if ! test -d build
then
   mkdir build
fi

# run cmake and the build
if test -d build
then
    cd build/
    cmake ..
    make
fi

echo "\n"
echo "Don't forget to jump into your build dir, run make install and add the following line to your php.ini file:\n"
echo "extension=php_qt.so"
echo ""
echo "You might also want to run make test"
echo "Have fun :)"
echo ""
