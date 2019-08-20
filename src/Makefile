.POSIX:
LINK = $(CXX)
CXXFLAGS = -g -O2
CFLAGS = -g -O2

M = sph
O = \
boundary.o\
diagnose.o\
glbfunc.o\
hydrodynamics.o\
initiation.o\
interaction.o\
material.o\
mls.o\
output.o\
particle.o\
particlemanager.o\
quinticspline.o\
sph.o\
timesolver.o\
vec2d.o\
wiener.o\

sph: $O
	$(LINK) $O $(LDFLAGS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -c -o $@

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

include dep.make

.cpp:
%: %.cppy

.PHONY: clean
clean:; rm -f $M $O
