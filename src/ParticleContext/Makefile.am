bin_PROGRAMS=test_particlecontext
test_particlecontext_SOURCES=test_particlecontext.cpp

test_particlecontext_LDADD=${top_builddir}/src/libsph.a ${top_builddir}/cpptcl/libcpptcl.a
test_particlecontext_CXXFLAGS=-I${top_srcdir}

${top_builddir}/src/libsph.a:
	cd ${top_builddir}/src; \
	${MAKE}

${top_builddir}/cpptcl/libcpptcl.a:
	cd ${top_builddir}/cpptcl; \
	${MAKE}
