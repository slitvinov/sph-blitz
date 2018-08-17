AC_PREREQ([2.63])
AC_INIT([sph], [0.1], [slitvinov@gmail.com])
AC_CONFIG_SRCDIR([src/sph.cpp])
AM_INIT_AUTOMAKE(sph, 0.1)
AC_PROG_CXX

AC_CHECK_BLITZ(
  [
    LDFLAGS="$LDFLAGS $BLITZ_LDFLAGS"
    CPPFLAGS="$CPPFLAGS $BLITZ_CPPFLAGS"
  ],
  [
    AC_MSG_ERROR([blitz++ library are required])
  ]	
)
AC_OUTPUT(Makefile src/Makefile)
