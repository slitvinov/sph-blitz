.POSIX:
.SUFFIXES: .o
.SUFFIXES: .c
CFLAGS = -g -O2
AR = ar
RANLIB = ranlib

M = libsph.a
O = \
boundary.o\
err.o\
ini.o\
kernel.o\
list.o\
material.o\
pair.o\
particle.o\
random.o\
step.o\
volume.o\
vv.o\

all: libsph.a
$M: $O; $(AR) rc $@ $O && $(RANLIB) $@
.c.o:; $(CC) -c $(CFLAGS) $<
dep: ../scripts/dep; $< *.c > dep.mk

clean:; rm -f -- $M $O
include dep.mk
