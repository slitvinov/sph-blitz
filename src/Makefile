.POSIX:
.SUFFIXES:
.SUFFIXES: .o
.SUFFIXES: .c
CFLAGS = -g -O2

M = libsph.a
O = \
err.o\
ini.o\
kernel.o\
list.o\
material.o\
particle.o\

all: $M
$M: $O; ar rc $@ $O && ranlib $@
.c.o:; $(CC) -c $(CFLAGS) $<
dep: ../scripts/dep; $< *.c > dep.mk

clean:; rm -f $M $O
include dep.mk
