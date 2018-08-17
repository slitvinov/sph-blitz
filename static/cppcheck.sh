#! /bin/bash

# to use output log in emacs compilation mode
cppcheck --enable=all  .  2>&1  | sed -e 's,\[\.\/,,g' -e 's,\],:,g'  | sed 's,::,:,g' | sed 's,^\[,,g'
