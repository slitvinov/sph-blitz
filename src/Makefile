.POSIX:
LINK = $(CC)
CFLAGS = -g -O2

M = main
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
main.o\
step.o\
volume.o\
vv.o\
wiener.o\

$M: $O; $(LINK) $O $(LDFLAGS) -lm -o $@
.c.o:; $(CC) $(CFLAGS) -Iinc $< -c -o $@
dep:; ../scripts/dep
test: $M; cd ..; atest test/*
lint:; make CFLAGS='-g -Wall -Wextra -pedantic'

.PHONY: clean dep test lint
clean:; rm -f -- $M $O
include dep.make
