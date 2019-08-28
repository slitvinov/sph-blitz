.POSIX:
LINK = $(CC)
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

$M: $O; $(LINK) $O $(LDFLAGS) -o $@
.c.o:; $(CC) $(CFLAGS) $< -c -o $@
dep:; ../scripts/dep
test: sph; cd ..; atest test/*
lint:; make CFLAGS='-g -Wall -Wextra -pedantic'

.PHONY: clean dep test lint
clean:; rm -f -- $M $O
include dep.make
