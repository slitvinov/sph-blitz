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
manager.o\
material.o\
mls.o\
output.o\
particle.o\
quinticspline.o\
sph.o\
step.o\
volume.o\
vv.o\
wiener.o\

sph: $O; $(LINK) $O $(LDFLAGS) -o $@
.cpp.o:; $(CXX) $(CXXFLAGS) $< -c -o $@
.c.o:; $(CC) $(CFLAGS) $< -c -o $@
dep:; ../scripts/dep
test: sph; cd ..; atest test/*
lint:; make CXXFLAGS='-Wall -Wextra' CFLAGS='-Wall -Wextra'

.PHONY: clean dep test lint
clean:; rm -f -- $M $O
include dep.make
