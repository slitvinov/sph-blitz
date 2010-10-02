bin_PROGRAMS=sph kernel_test particlemanager_test spParticle

# PLUGIN_PATH is a path to the compile.tcl 
# it is used to get dynamics loaded functions
AM_CXXFLAGS=-I${top_srcdir} -I${top_srcdir}/cpptcl \
	-DPLUGIN_PATH=\"${abs_top_srcdir}/plugins\"

# add to all binaries
LDADD=${top_builddir}/cpptcl/libcpptcl.a
AM_LDFLAGS=-Wl,-R $(abs_top_srcdir)/plugins/
${top_builddir}/cpptcl/libcpptcl.a:
	cd ${top_builddir}/cpptcl; \
	${MAKE}

nomain=	 boundary.cpp boundary.h \
	glbtype.h glbfunc.cpp glbfunc.h \
	hydrodynamics.cpp hydrodynamics.h \
	initiation.cpp initiation.h \
	material.cpp material.h \
	output.cpp output.h particle.cpp \
	particle.h particlemanager.cpp particlemanager.h \
	vec2d.h \
	Kernel/kernel.cpp Kernel/kernel.h \
	Kernel/quinticspline.cpp Kernel/quinticspline.h \
	Kernel/cubicspline.cpp Kernel/cubicspline.h \
	Kernel/cubicspline1D.cpp Kernel/cubicspline1D.h \
	Kernel/betaspline.h Kernel/betaspline.cpp \
	Kernel/harmonic.h Kernel/harmonic.cpp \
	ParticleGenerator/particlegenerator.h ParticleGenerator/particlegenerator.cpp \
	ParticleContext/nocontext.cpp ParticleContext/nocontext.h \
	ParticleContext/solidcontext.cpp ParticleContext/solidcontext.h \
	ParticleContext/particlecontext.cpp ParticleContext/particlecontext.h \
	Interaction/interaction.cpp  Interaction/interaction.h \
	Interaction/interactioncomp.cpp  Interaction/interactioncomp.h \
	Interaction/interactionin.cpp  Interaction/interactionin.h \
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
