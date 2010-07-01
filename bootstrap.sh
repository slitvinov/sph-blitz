#! /bin/sh

aclocal -I m4
automake --foreign --add-missing --copy 
autoconf 
automake --foreign --add-missing --copy 
