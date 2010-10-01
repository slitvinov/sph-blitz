lib_LIBRARIES=libcpptcl.a
bin_PROGRAMS= cpptcl_test

libcpptcl_a_SOURCES=cpptcl.cc cpptcl.h

# add a preprocessor variable to find dump.tcl file
# TODO: should be changed in the future
AM_CXXFLAGS=-I${top_srcdir} -DCPPTCL_SRC=\"${abs_top_srcdir}/cpptcl\"

cpptcl_test_SOURCES= cpptcl_test.cc cpptcl.cc cpptcl.h