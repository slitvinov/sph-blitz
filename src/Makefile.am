bin_PROGRAMS=sph kernel_test particlemanager_test spParticle
AM_CXXFLAGS=-I${top_srcdir} -I${top_srcdir}/cpptcl

# add to all binaries
LDADD=${top_srcdir}/cpptcl/libcpptcl.a
${top_srcdir}/cpptcl/libcpptcl.a: 
	cd ${top_srcdir}/cpptcl; \
	${MAKE}

nomain=	 boundary.cpp boundary.h \
	glbtype.h glbfunc.cpp glbfunc.h \
	hydrodynamics.cpp hydrodynamics.h initiation.cpp \
	initiation.h interaction.cpp interaction.h \
	material.cpp \
	material.h \
	output.cpp output.h particle.cpp \
	particle.h particlemanager.cpp particlemanager.h \
	vec2d.h \
	Kernel/kernel.cpp Kernel/kernel.h \
	Kernel/quinticspline.cpp Kernel/quinticspline.h \
	Kernel/cubicspline.cpp Kernel/cubicspline.h \
	Kernel/cubicspline1D.cpp Kernel/cubicspline1D.h \
	Kernel/betaspline.h Kernel/betaspline.cpp \
	Kernel/harmonic.h Kernel/harmonic.cpp \
	TimeSolver/timesolver.cpp TimeSolver/timesolver.h \
	TimeSolver/hydrotimesolver.cpp TimeSolver/hydrotimesolver.h \
	TimeSolver/gastimesolverLeapFrog.cpp TimeSolver/gastimesolverLeapFrog.h \
	TimeSolver/gastimesolverPredCorr.cpp TimeSolver/gastimesolverPredCorr.h \
	main.doxygen

sph_SOURCES= sph.cpp $(nomain)

# examples
spParticle_SOURCES = sandbox/spParticle.cpp

# tests 
kernel_test_SOURCES= $(nomain) Kernel/kernel_test.cpp
particlemanager_test_SOURCES= $(nomain) particlemanager_test.cpp

EXTRA_DIST = Doxyfile
