.POSIX:
LINK = $(CXX)
CXXFLAGS = -g -O2
CFLAGS = -g -O2

M = sph
O = \
boundary.o\
diagnose.o\
err.o\
glbfunc.o\
hydrodynamics.o\
initiation.o\
interaction.o\
list.o\
material.o\
mls.o\
output.o\
particle.o\
manager.o\
quinticspline.o\
sph.o\
step.o\
volume.o\
vv.o\
wiener.o\

sph: $O
	$(LINK) $O $(LDFLAGS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -c -o $@

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

include dep.make

.cpp:
%: %.cpp

dep:
	../scripts/dep

test: sph
	cd ..; atest test/*

.PHONY: clean dep test
clean:; rm -f $M $O
