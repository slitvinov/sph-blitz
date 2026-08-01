all: lib example
lib:; cd src && $(MAKE)
example: lib; cd example && $(MAKE)
test: example; test/regression.sh
clean:
	cd src && $(MAKE) clean
	cd example && $(MAKE) clean
lib.o: sph.h
.PHONY: all lib example test clean
