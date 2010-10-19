bin_PROGRAMS=sphprobe
sphprobe_SOURCES=sphprobe.cpp sphprobe.h

sphprobe_LDADD=${top_builddir}/src/libsph.a \
	${top_builddir}/cpptcl/libcpptcl.a \
	${top_builddir}/boost/libs/program_options/src/libboost_program_options.a

sphprobe_CXXFLAGS=-I${top_srcdir}

${top_builddir}/src/libsph.a:
	cd ${top_builddir}/src; \
	${MAKE}

${top_builddir}/cpptcl/libcpptcl.a:
	cd ${top_builddir}/cpptcl; \
	${MAKE}

${top_builddir}/boost/libs/program_options/src/libboost_program_options.a:
	cd ${top_builddir}/boost/libs/program_options/src/; \
	${MAKE}