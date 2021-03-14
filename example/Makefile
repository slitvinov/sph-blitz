.POSIX:
.SUFFIXES: .c
LINK = $(CC)
CFLAGS = -g -Og

SPH_FLAGS = -I../src -L../src -lsph -lm

M = \
kernel\
list\
random\
sdpd\

all: $M
.c:; $(CC) $(CFLAGS) -o $@ $< $(SPH_FLAGS) $(LDFLAGS)
clean:; rm -f -- $M
