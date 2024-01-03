.POSIX:
.SUFFIXES:
.SUFFIXES: .o
.SUFFIXES: .c
CFLAGS = -g -O2
AR = ar
RANLIB = ranlib

M = libsph.a
O = \
err.o\
ini.o\
kernel.o\
list.o\
material.o\
particle.o\

all: libsph.a
$M: $O; $(AR) rc $@ $O && $(RANLIB) $@
.c.o:; $(CC) -c $(CFLAGS) $<
dep: ../scripts/dep; $< *.c > dep.mk

clean:; rm -f -- $M $O
include dep.mk
