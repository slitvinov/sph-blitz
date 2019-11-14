.POSIX:
CFLAGS = -g -O2
AR = ar
RANLIB = ranlib

SPH_CFLAGS = -Isph

M = libsph.a
O = \
boundary.o\
err.o\
hydro.o\
ini.o\
kernel.o\
list.o\
manager.o\
material.o\
output.o\
pair.o\
particle.o\
random.o\
step.o\
volume.o\
vv.o\

all: libsph.a
$M: $O; $(AR) rc $@ $^ && $(RANLIB) $@
.c.o:; $(CC) -c $(CFLAGS) $(SPH_CFLAGS) $<
dep:; ../scripts/dep
lint:; make CFLAGS='-g -Og -Wall -Wextra -pedantic'

.PHONY: clean dep lint
clean:; rm -f -- $M $O
include dep.make
