bin_PROGRAMS=sph kernel_test particlemanager_test
AM_CXXFLAGS=-I${top_srcdir}


nomain=	 boundary.cpp boundary.h \
	dllist.h \
	glbcls.h glbfunc.cpp glbfunc.h \
	hydrodynamics.cpp hydrodynamics.h initiation.cpp \
	initiation.h interaction.cpp interaction.h \
	material.cpp \
	material.h \
	output.cpp output.h particle.cpp \
	particle.h particlemanager.cpp particlemanager.h \
	timesolver.cpp timesolver.h vec2d.cpp \
	vec2d.h \
	Kernel/kernel.cpp Kernel/kernel.h \
	Kernel/quinticspline.cpp Kernel/quinticspline.h \
	Kernel/cubicspline1D.cpp Kernel/cubicspline1D.h \
	Kernel/betaspline.h Kernel/betaspline.cpp

sph_SOURCES= sph.cpp $(nomain) 

kernel_test_SOURCES= $(nomain) Kernel/kernel_test.cpp
particlemanager_test_SOURCES= $(nomain) particlemanager_test.cpp

