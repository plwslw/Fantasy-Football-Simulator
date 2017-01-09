#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MESSAGE_BUFFER_SIZE 256

int client_handshake(int* a){
  char * name = ".pipe2";
  mkfifo(name, 0644);
  int server = open("pipe1", O_WRONLY);
  write(server, name, 7);
  char buffer[MESSAGE_BUFFER_SIZE];
  int private = open(name, O_RDONLY);
  read(private, buffer, 3);
  remove(name);
  write(server, "hello", 6);
  *a = server;
  return private;
}

int server_handshake(int* a){
  mkfifo("pipe1", 0644);
  char buffer[MESSAGE_BUFFER_SIZE];
  int client = open("pipe1", O_RDONLY); 
  read(client, buffer, 7);
  remove("pipe1");
  int private = open(buffer, O_WRONLY);
  write(private, "hi", 3);
  read(client, buffer, 6);
  *a = client;
  return private;
}


