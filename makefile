all: tic.o
	gcc -o hello tic.o

tic.o:tic.c
	gcc -c tic.c

run:
	./hello

clear:
	rm *.o
	rm *out
