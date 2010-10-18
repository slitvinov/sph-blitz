lib_LIBRARIES=libcpptcl.a


libcpptcl_a_SOURCES=cpptcl.cc cpptcl.h
# add a preprocessor variable to find dump.tcl file
# TODO: should be changed in the future
AM_CXXFLAGS=-I${top_srcdir} -DCPPTCL_SRC=\"${abs_top_srcdir}/cpptcl\"

EXTRA_DIST=details

bin_PROGRAMS= cpptcl_test
cpptcl_test_SOURCES= cpptcl_test.cc
cpptcl_test_LDADD=${top_builddir}/cpptcl/libcpptcl.a
