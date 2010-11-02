bin_PROGRAMS=sph kernel_test particlemanager_test spParticle
AM_CXXFLAGS=-I${top_srcdir} 


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
	Interaction/interaction.cpp  Interaction/interaction.h \
	Interaction/interactioncomp.cpp  Interaction/interactioncomp.h \
	Interaction/interactionin.cpp  Interaction/interactionin.h \
	SolidObstacles/solidObstacles.cpp  SolidObstacles/solidObstacles.h \		SolidObstacles/cavity.cpp  SolidObstacles/cavity.h \
	SolidObstacles/noObstacles.cpp  SolidObstacles/noObstacles.h \
	TimeSolver/timesolver.cpp TimeSolver/timesolver.h \
	TimeSolver/hydrotimesolver.cpp TimeSolver/hydrotimesolver.h \
	TimeSolver/gastimesolverLeapFrog.cpp TimeSolver/gastimesolverLeapFrog.h \
	TimeSolver/gastimesolverPredCorr.cpp TimeSolver/gastimesolverPredCorr.h \
	cpptcl.cc cpptcl.h \
	main.doxygen

sph_SOURCES= sph.cpp $(nomain)

# examples
spParticle_SOURCES = sandbox/spParticle.cpp

# tests 
kernel_test_SOURCES= $(nomain) Kernel/kernel_test.cpp
particlemanager_test_SOURCES= $(nomain) particlemanager_test.cpp

EXTRA_DIST = Doxyfile
