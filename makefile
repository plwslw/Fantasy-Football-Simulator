all: make

pipe_networking: pipe_networking.c 
	gcc -c pipe_networking.c 

fserver: fserver.c
	gcc -c fserver.c

client: client.c
	gcc -c client.c

binaries: pipe_networking fserver client
	gcc pipe_networking.o fserver.o -o fserver
	gcc pipe_networking.o client.o -o client

clean:
	*.o
	client
	fserver
	pipe1
