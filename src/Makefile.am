bin_PROGRAMS=sph kernel_test particlemanager_test
AM_CXXFLAGS=-I${top_srcdir} 


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
	Kernel/betaspline.h Kernel/betaspline.cpp \
	TimeSolver/timesolver.cpp TimeSolver/timesolver.h \
	TimeSolver/hydrotimesolver.cpp TimeSolver/hydrotimesolver.h \
	TimeSolver/gastimesolver.cpp TimeSolver/gastimesolver.h \
	cpptcl.cc cpptcl.h \
	main.doxygen

sph_SOURCES= sph.cpp $(nomain) 

kernel_test_SOURCES= $(nomain) Kernel/kernel_test.cpp
particlemanager_test_SOURCES= $(nomain) particlemanager_test.cpp

EXTRA_DIST = Doxyfile