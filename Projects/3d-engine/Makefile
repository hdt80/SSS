# compile for the correct OS

OS := $(shell uname)
MAKEFILE := mingw


.PHONY: static clean build run debug

ifeq ($(OS), Darwin)
MAKEFILE=osx
endif

static:
	$(MAKE) -f Makefile.$(MAKEFILE) static

clean:
	$(MAKE) -f Makefile.$(MAKEFILE) clean

# Builds by default
build:
	$(MAKE) -f Makefile.$(MAKEFILE) build

run:
	$(MAKE) -f Makefile.$(MAKEFILE) run

debug:
	$(MAKE) -f Makefile.$(MAKEFILE) debug

