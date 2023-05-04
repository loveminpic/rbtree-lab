.PHONY: clean

CFLAGS=-Wall -g

test : test.o
	gcc -o test test.o

test.o : test.c
	gcc -c -o test.o test.c

clean:
	rm -f driver *.o
