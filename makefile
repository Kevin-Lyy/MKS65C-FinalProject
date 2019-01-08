all: tic login

tic: tic.o
	gcc -o tic tic.o

login: login.o
	gcc -o login login.o

tic.o: tic.c
	gcc -c tic.c

login.o: login.c
	gcc -c login.c

run:
	./tic

fun:
	./login

clean:
	rm *.o
	rm tic
	rm login
