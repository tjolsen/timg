cfiles = $(shell ls *.c)
ofiles = $(cfiles:.c=.o)
exefiles = $(cfiles:.c=.exe)

LIB = libtimg.a
LIBDIR = ../lib/
CFLAGS = -I../src/ -O3 -march=native -c -Wall
LFLAGS = -L$(LIBDIR) -ltimg -lm -lpng -ljpeg -ltiff

CC = gcc

all: $(LIBDIR)/$(LIB) $(exefiles)

$(LIBDIR)/$(LIB):
	$(MAKE) -C .. lib/$(LIB)

%.exe: %.o 
	$(CC) -o $@ $< $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm $(ofiles) $(exefiles) *.png *.jpg *.tiff *.tif

.PHONY: all clean $(LIBDIR)/$(LIB)