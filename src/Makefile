cfiles = $(shell ls *.c)
ofiles = $(cfiles:.c=.o)

CFLAGS = -O3 -march=native -c -Wall
CC = gcc

all: $(ofiles)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm *.o

.PHONY: all clean