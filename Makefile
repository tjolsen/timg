subdirs = src test

lib=libtimg.a

ARFLAGS = -r

all: $(subdirs) lib/$(lib)

lib/$(lib): src
	ar $(ARFLAGS) $@ $(wildcard src/*.o)

src:
	$(MAKE) -C $@

test: lib/$(lib)
	$(MAKE) -C $@

clean:
	rm lib/$(lib); for dir in $(subdirs); do $(MAKE) -C $$dir clean; done; 

.PHONY: $(subdirs) clean all
