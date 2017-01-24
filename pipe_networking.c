#include "pipe_networking.h"
int client_handshake(int* a){
  char * name;
  sprintf( name, "%d", getpid());
  mkfifo(name, 0644);
  
  int server = open("pipe1", O_WRONLY);
  write(server,  name, MESSAGE_BUFFER_SIZE);
  
  char buffer[MESSAGE_BUFFER_SIZE];
  int private = open(name, O_RDONLY);
  read(private, buffer, sizeof(buffer));
  remove(name);
  
  write(server, "hello", MESSAGE_BUFFER_SIZE);
  
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

int server_handshake1(char* buffer){
  mkfifo("pipe1", 0644);
  int client = open("pipe1", O_RDONLY);
  read(client, buffer, MESSAGE_BUFFER_SIZE);
  remove("pipe1");
  return client;
}


int server_handshake2(char* buffer, int client){
  int private = open(buffer, O_WRONLY);
  strncpy (buffer, "hi", MESSAGE_BUFFER_SIZE);
  write(private, buffer, MESSAGE_BUFFER_SIZE);
  read(client, buffer, MESSAGE_BUFFER_SIZE);
  return private;
}
