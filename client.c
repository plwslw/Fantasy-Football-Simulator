#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pipe_networking.h"

int pipein = 0;
int pipeout = 0;

int display(){
  char input;
  int check = read(pipein,&input,sizeof(char)); // fgets check
  char buffer[256];
  read(pipein,buffer,256);
  printf(buffer);
  int s_side_check = 1;
  if(check == -1){
    s_side_check = 0;
    write(pipeout,&s_side_check,sizeof(int));
    printf("An error occured: [%s]\n",strerror(errno));
    exit(1);
  }
  write(pipeout,&s_side_check,sizeof(int));
  if(input){
    write(pipeout,getInput(256),256);
  }
}

char* getInput(int bytes){
  char* input = (char*)malloc(bytes);
  fgets(input, sizeof(input), stdin); // includes newline must remove
  strtok(input,"\n");
  return input;
}

int main() {

  int to_server, from_server;

  from_server = client_handshake( &to_server );
  pipein = from_server;
  pipeout = to_server;
  char buffer[MESSAGE_BUFFER_SIZE];

  while(1){
    
    /* read( from_server, buffer, sizeof(buffer) ); */
    /* printf( "received: %s\n", buffer ); */
    
    /* printf("enter message: "); */
    /* fgets( buffer, sizeof(buffer), stdin ); */
    /* char *p = strchr(buffer, '\n'); */
    /* *p = 0; */
    
    /* write( to_server, buffer, sizeof(buffer) ); */
    
  }
  
  return 0;
}
