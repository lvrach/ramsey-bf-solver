CC=gcc
CFLAGS=-O3 -fopenmp -Wall

ifdef NODES
else
NODES = 10
endif

ramsey: ramsey.c
	$(CC) -o ramsey ramsey.c $(CFLAGS) -D POINTS=$(NODES)
clean:
	rm ramsey
