all: binaries

pipe_networking: pipe_networking.c pipe_networking.h
	gcc -c -g pipe_networking.c 

fserver: fserver.c fserver.h
	gcc -c -g fserver.c

client: client.c
	gcc -c -g client.c

account: accounts.c accounts.h
	gcc -c -g accounts.c

draft_server: draft_server.c draft_server.h
	gcc -c -g draft_server.c

draft_client: draft_client.c
	gcc -c -g draft_client.c

binaries: pipe_networking fserver client account draft_server draft_client
	gcc -g accounts.o pipe_networking.o fserver.o -o fserver
	gcc -g pipe_networking.o client.o -o client
	gcc -g pipe_networking.o draft_client.o -o draft_client
	gcc -g pipe_networking.o draft_server.o -o draft_server

clean:
	rm *.o
	rm client
	rm fserver
	rm pipe1
	rm *~
