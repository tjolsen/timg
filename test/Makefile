cfiles = $(shell ls *.c)
ofiles = $(cfiles:.c=.o)
exefiles = $(cfiles:.c=.exe)

LIB = ../lib/libtimg.a
LIBDIR = ../lib/
CFLAGS = -I../src/ -O3 -march=native -c -Wall
LFLAGS = -L$(LIBDIR) -ltimg -lpng -ljpeg

CC = gcc

all: $(LIBDIR)/$(LIB) $(exefiles)
	echo $(exefiles)

$(LIBDIR)/$(LIB):
	$(MAKE) -C .. lib

%.exe: %.o 
	$(CC) -o $@ $< $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm $(ofiles) $(exefiles) *.png

.PHONY: all clean $(LIB)