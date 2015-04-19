# compile for the correct OS

OS = $(shell uname)
MAKEFILE = osx

.PHONY: static clean build run debug

ifeq ($(OS), wsindows32)
	MAKEFILE = mingw
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
	$(MAKE) -f Makefile.$(MAKEfile) debug

