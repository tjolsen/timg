subdirs = src test

lib=libtimg.a

ARFLAGS = -r

all: $(subdirs) lib/$(lib)

lib/$(lib): src
	ar $(ARFLAGS) $@ $(shell find src/ | grep .o$$)

src:
	$(MAKE) -C $@

test: lib/$(lib)
	$(MAKE) -C $@

clean:
	for dir in $(subdirs); do $(MAKE) -C $$dir clean; done
	rm lib/$(lib)

.PHONY: $(subdirs) clean all