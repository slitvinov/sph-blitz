#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([sph], [0.1], [slitvinov@gmail.com])
AC_CONFIG_SRCDIR([src/sph.cpp])
AM_INIT_AUTOMAKE(sph, 0.1)

# Checks for programs.
AC_PROG_CXX


# check tcl library
SC_PATH_TCLCONFIG 
AC_SUBST(TCL_BIN_DIR)
. ${TCL_BIN_DIR}/tclConfig.sh
TCL_LIB_SPEC=$(${SHELL} -c "echo ${TCL_LIB_SPEC}")
TCL_INCLUDE_SPEC=$(${SHELL} -c "echo ${TCL_INCLUDE_SPEC}")
LIBS="${TCL_LIB_SPEC} ${LIBS}"
CXXFLAGS="${TCL_INCLUDE_SPEC} ${CXXFLAGS}"


# Checks for blitz++ 
AC_CHECK_BLITZ(
  [
    LDFLAGS="$LDFLAGS $BLITZ_LDFLAGS"
    CPPFLAGS="$CPPFLAGS $BLITZ_CPPFLAGS"
  ],
  [
    AC_MSG_ERROR([blitz++ library are required])
  ]	
)

# if using the  GNU C++, mark BLITZ_INCDIR as system 
# to avoid warnings
if test "$GXX" = yes; then
  CPPFLAGS="$CPPFLAGS -isystem$BLITZ_INCDIR"
fi


# TODO: 
# link to  google log 
# assuming it is in the same directory as blitz++
LIBS="$LIBS $BLITZ_LIBDIR/libglog.a -pthread"


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt])

AC_OUTPUT(Makefile src/Makefile
		   src/tools/SPHProbe/Makefile
		   )

AC_MSG_NOTICE([================================================])
AC_MSG_NOTICE([CXX=$CXX])
AC_MSG_NOTICE([CXXFLAGS=$CXXFLAGS])
AC_MSG_NOTICE([CPPFLAGS=$CPPFLAGS])
AC_MSG_NOTICE([LIBS=$LIBS])
