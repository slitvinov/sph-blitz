.POSIX:
LINK = $(CC)
CFLAGS = -g -O2
AR = ar
RANLIB = ranlib

SPH_LDFLAGS = -L. -lsph -lm
SPH_CFLAGS = -Iinc

M = main
L = libsph.a
O = \
boundary.o\
diag.o\
err.o\
glbfunc.o\
hydro.o\
ini.o\
pair.o\
list.o\
manager.o\
material.o\
mls.o\
output.o\
particle.o\
kernel.o\
step.o\
volume.o\
vv.o\
wiener.o\

all: libsph.a $M
$L: $O; $(AR) rc $@ $^ && $(RANLIB) $@
$M: $M.o $L; $(LINK) $M.o -o $@ $(LDFLAGS) $(SPH_LDFLAGS)
.c.o:; $(CC) -c -o $@ $(CFLAGS) $(SPH_CFLAGS) $<
dep:; ../scripts/dep
test: $M; cd ..; atest test/*
lint:; make CFLAGS='-g -Wall -Wextra -pedantic'

.PHONY: clean dep test lint
clean:; rm -f -- $M $L $O
include dep.make
