CC=gcc
CFLAGS=-W -Wall -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600
EXEC=cy-wire

all: cy-wire

cy-wire: src/avl.c src/main.c
	$(CC) -o $@ $^ $(LDFLAGS)

src/avl.c: src/avl.o
	$(CC) -o $@ -c $< $(CFLAGS)

src/main.c: src/main.o
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm src/*.o

mrproper: clean
	rm $(EXEC)