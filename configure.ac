#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ([2.63])
AC_INIT([sph], [0.1], [slitvinov@gmail.com])
AM_INIT_AUTOMAKE([sph], [0.1])
AC_CONFIG_SRCDIR([src/sph.cpp])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CXX
AC_PROG_RANLIB

# check tcl library
SC_PATH_TCLCONFIG 
AC_SUBST(TCL_BIN_DIR)
. ${TCL_BIN_DIR}/tclConfig.sh
TCL_LIB_SPEC=$(${SHELL} -c "echo ${TCL_LIB_SPEC}")
TCL_INCLUDE_SPEC=$(${SHELL} -c "echo ${TCL_INCLUDE_SPEC}")
#TCL_LIBS=$(${SHELL} -c "echo ${TCL_LIBS}")
TCL_LD_SEARCH_FLAGS=$(${SHELL} -c "echo ${TCL_LD_SEARCH_FLAGS}")
#LIBS="${TCL_LIB_SPEC} ${TCL_LD_SEARCH_FLAGS} ${TCL_LIBS} ${LIBS}"
LIBS="${TCL_LIB_SPEC} ${LIBS} ${TCL_LD_SEARCH_FLAGS}"
CPPFLAGS="${TCL_INCLUDE_SPEC} ${CPPFLAGS}"


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
#LIBS="$LIBS "


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt])

AC_OUTPUT(Makefile src/Makefile cpptcl/Makefile plugins/Makefile)

AC_MSG_NOTICE([================================================])
AC_MSG_NOTICE([CXX=$CXX])
AC_MSG_NOTICE([CXXFLAGS=$CXXFLAGS])
AC_MSG_NOTICE([CPPFLAGS=$CPPFLAGS])
AC_MSG_NOTICE([LIBS=$LIBS])