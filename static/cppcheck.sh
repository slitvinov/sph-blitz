#! /bin/bash

# to use output log in emacs compiletion-mode
cppcheck --enable=all  .  Kernel/ 2>&1  | tee cppcheck.log | sed -e 's,\[\.\/,,g' -e 's,\],:,g'  | sed -e 's,::,:,g'