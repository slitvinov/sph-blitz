#! /bin/sh

#libtoolize  --force  --copy
aclocal -I m4
automake --foreign --add-missing --copy 
autoconf 