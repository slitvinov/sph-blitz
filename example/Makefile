.POSIX:
.SUFFIXES:
.SUFFIXES: .c

CFLAGS = -g -Og
SPH_FLAGS = -I../src -L../src -lsph -lm

M = \
kernel\
list\
random\
sdpd\

all: $M
.c:; $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(SPH_FLAGS) 
lint:; $(MAKE) CFLAGS='-g -Og -Wall -Wextra -pedantic'
dep:; ls *.c | awk '{i = o = $$1; sub(/\.c$$/, ".o", o); print o ": " i}' > dep.make

.PHONY: clean lint dep
clean:; rm -f -- $M $(M:=.o)

include dep.make
