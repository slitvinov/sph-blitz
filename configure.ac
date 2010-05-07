#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([sph], [0.1], [slitvinov@gmail.com])
AC_CONFIG_SRCDIR([src/sph.cpp])
AM_INIT_AUTOMAKE(sph, 0.1)

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_BLITZ(
  [
    LDFLAGS="$LDFLAGS $BLITZ_LDFLAGS"
    CPPFLAGS="$CPPFLAGS $BLITZ_CPPFLAGS"
  ],
  [
    AC_MSG_ERROR([blitz++ library are required])
  ]	
)


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt])

AC_OUTPUT(Makefile src/Makefile)

