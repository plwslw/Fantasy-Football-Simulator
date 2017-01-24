all: binaries

pipe_networking: pipe_networking.c pipe_networking.h
	gcc -c -g pipe_networking.c 

fserver: fserver.c fserver.h
	gcc -c -g fserver.c

client: client.c
	gcc -c -g client.c

account: accounts.c accounts.h
	gcc -c -g accounts.c

binaries: pipe_networking fserver client account
	gcc -g accounts.o pipe_networking.o fserver.o -o fserver
	gcc -g pipe_networking.o client.o -o client

clean:
	rm *.o
	rm client
	rm fserver
	rm pipe1
	rm *~
