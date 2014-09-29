#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.60)

AC_INIT(sphopt, 0.1, Sergej.Litvinov@aer.mw.tum.de)
AC_CONFIG_AUX_DIR(config) 
AC_CONFIG_MACRO_DIR(m4)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_STRTOD

#AC_CHECK_FUNCS([pow sqrt])
#Test for program options library from the Boost C++ libraries
AX_BOOST_BASE([1.33])
AX_BOOST_PROGRAM_OPTIONS

GSLVERSION=1.2
AM_PATH_GSL($GSLVERSION,,
            AC_MSG_ERROR([need to have at least GNU scientific library $GSLVERSION installed]))

AC_CHECK_NETCDF(
  [
       LIBS="$LIBS $NC_LIBS"
       LDFLAGS="$LDFLAGS $NC_LDFLAGS"
       CPPFLAGS="$CPPFLAGS $NC_CPPFLAGS"
   ],
   [
       echo "*** Use --with-netcdf for the root netcdf directory."
       echo "*** Otherwise use --with-netcdf-include switch for includes directory"
       echo "*** and --with-netcdf-libdir switch for libraries directory."
       AC_MSG_ERROR([netcdf library and netcdf headers are required.])
   ]
)


AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT