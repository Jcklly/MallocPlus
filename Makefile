all: memgrind.c mymalloc.o
	gcc -g memgrind.c mymalloc.o

mymalloc.o: mymalloc.c
	gcc -c mymalloc.c

clean:
	rm a.out; rm mymalloc.o
