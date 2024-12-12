CC=gcc
CFLAGS=-W -Wall -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600
LDFLAGS=

all: cy-wire

cy-wire: avl.o csv.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

avl.o: avl.c
	$(CC) -o $@ -c $< $(CFLAGS)

csv.o: csv.c
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: main.c avl.c csv.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm *.o

mrproper: clean
	rm cy-wire
