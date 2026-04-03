.POSIX:
.SUFFIXES:
.SUFFIXES: .o
.SUFFIXES: .c
CFLAGS = -g -O2

M = libsph.a
O = \
lib.o\

all: $M
$M: $O; ar rc $@ $O && ranlib $@
.c.o:; $(CC) -c $(CFLAGS) $<
dep: ../scripts/dep; $< *.c > dep.mk

clean:; rm -f $M $O
include dep.mk
