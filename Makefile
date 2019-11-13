all: lib example
lib:; cd src && $(MAKE)
example: lib; cd example && $(MAKE)
test: example; atest test/*
clean:
	cd src && $(MAKE) clean
	cd example && $(MAKE) clean
lint:
	cd src && $(MAKE) lint
	cd example && $(MAKE) lint
.PHONY: all lib example test clean lint
