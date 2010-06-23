bin_PROGRAMS=sph kernel_test


nomain=	 boundary.cpp boundary.h \
	diagnose.h diagose.cpp \
	dllist.h force.cpp force.h \
	glbcls.h glbfunc.cpp glbfunc.h \
	hydrodynamics.cpp hydrodynamics.h initiation.cpp \
	initiation.h interaction.cpp interaction.h \
	material.cpp \
	material.h mls.cpp mls.h \
	output.cpp output.h particle.cpp \
	particle.h particlemanager.cpp particlemanager.h \
	timesolver.cpp timesolver.h vec2d.cpp \
	vec2d.h wiener.cpp wiener.h \
	Kernel/kernel.cpp Kernel/kernel.h \
	Kernel/quinticspline.cpp Kernel/quinticspline.h \
	Kernel/cubicspline1D.cpp Kernel/cubicspline1D.h \
	Kernel/betaspline.h Kernel/betaspline.cpp

sph_SOURCES= sph.cpp $(nomain) 
kernel_test_SOURCES= $(nomain) Kernel/kernel_test.cpp

