all: binaries

pipe_networking: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c 

fserver: fserver.c fserver.h
	gcc -c fserver.c

client: client.c
	gcc -c client.c

account: accounts.c accounts.h
	gcc -c accounts.c

binaries: pipe_networking fserver client
	gcc accounts.o pipe_networking.o fserver.o -o fserver
	gcc pipe_networking.o client.o -o client

clean:
	rm *.o
	rm *~
	rm client
	rm fserver
	rm pipe1
