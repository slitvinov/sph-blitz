.POSIX:
LINK = $(CC)
CFLAGS = -g -Og

SPH_LDFLAGS = -L../src -lsph -lm
SPH_CFLAGS = -I../src

M = \
kernel\
list\
sdpd\

O = $(M:=.o)

all: $M
.o:; $(LINK) -o $@ $< $(LDFLAGS) $(SPH_LDFLAGS)
.c.o:; $(CC) -c $(CFLAGS) $(SPH_CFLAGS) $<
lint:; make CFLAGS='-g -Og -Wall -Wextra -pedantic'

.SUFFIXES: .o .c
%: %.c

dep:; ls *.c | awk '{i = o = $$1; sub(/\.c$$/, ".o", o); print o ": " i}' > dep.make

.PHONY: clean lint dep
clean:; rm -f -- $M $O

include dep.make
