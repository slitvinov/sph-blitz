.POSIX:
LINK = $(CC)
CFLAGS = -g -O2

SPH_LDFLAGS = -L../src -lsph -lm
SPH_CFLAGS = -I../src/inc

M = \
sdpd\
inv\

O = $(M:=.o)

all: $M
sph: sph.o
.o:; $(LINK) -o $@ $< $(LDFLAGS) $(SPH_LDFLAGS)
.c.o:; $(CC) -c -o $@ $(CFLAGS) $(SPH_CFLAGS) $<
lint:; make CFLAGS='-g -Wall -Wextra -pedantic'

.SUFFIXES: .o .c

dep:; ls *.c | awk '{i = o = $$1; sub(/\.c$$/, ".o", o); print o ": " i}' > dep.make

.PHONY: clean lint dep
clean:; rm -f -- $M $O


include dep.make
