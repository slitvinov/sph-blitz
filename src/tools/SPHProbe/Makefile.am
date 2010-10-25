bin_PROGRAMS=sphprobe norm
sphprobe_SOURCES=sphprobe.cpp utils.cpp utils.h
norm_SOURCES=norm.cpp utils.cpp utils.h

sphprobe_LDADD=${top_builddir}/src/libsph.a \
	${top_builddir}/cpptcl/libcpptcl.a \
	${top_builddir}/boost/libs/program_options/src/libboost_program_options.a \
	${GSL_LIBS}
sphprobe_CXXFLAGS=-I${top_srcdir} ${GSL_CFLAGS}
norm_LDADD=${top_builddir}/src/libsph.a \
	${top_builddir}/cpptcl/libcpptcl.a \
	${top_builddir}/boost/libs/program_options/src/libboost_program_options.a \
	${GSL_LIBS}
norm_CXXFLAGS=-I${top_srcdir} ${GSL_CFLAGS}


${top_builddir}/src/libsph.a:
	cd ${top_builddir}/src; \
	${MAKE}

${top_builddir}/cpptcl/libcpptcl.a:
	cd ${top_builddir}/cpptcl; \
	${MAKE}

${top_builddir}/boost/libs/program_options/src/libboost_program_options.a:
	cd ${top_builddir}/boost/libs/program_options/src/; \
	${MAKE}