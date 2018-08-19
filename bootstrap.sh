#! /bin/sh

set -eu

aclocal
autoconf
automake --foreign --add-missing --copy
