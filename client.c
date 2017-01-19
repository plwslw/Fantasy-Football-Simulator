#include "client.h"

int pipein = 0;
int pipeout = 0;

int display(){
  int input;
  read(pipein, &input, sizeof(input));
  char buffer[MESSAGE_BUFFER_SIZE];
  char check = read(pipein, buffer, sizeof(buffer));
  check++; //0 -> 1
  printf("[Recieved from server]: %s", buffer);
  write(pipeout, &check, sizeof(&check));
  return input;;
}

void writeToServer(){
  printf("> ");

  char buffer[MESSAGE_BUFFER_SIZE];
  fgets( buffer, sizeof(buffer), stdin ); 
  strtok( buffer, "\n");
    
  write( pipeout, buffer, sizeof(buffer) ); 
}    



int main() {

  int to_server, from_server;

  from_server = client_handshake( &to_server );
  pipein = from_server;
  pipeout = to_server;

  while(1){
    while(display());
    writeToServer();
  }
  
  return 0;
}

