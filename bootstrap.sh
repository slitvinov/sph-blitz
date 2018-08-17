#! /bin/sh

set -eu

aclocal -I m4
autoconf
automake --foreign --add-missing --copy
