bin_PROGRAMS=test_timer
test_timer_SOURCES=test_timer.cpp
test_timer_LDADD=${top_builddir}/src/libsph.a
test_timer_CXXFLAGS=-I${top_srcdir}

${top_builddir}/src/libsph.a:
	cd ${top_builddir}/src; \
	${MAKE}
