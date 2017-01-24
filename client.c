#include "client.h"

int pipein = 0;
int pipeout = 0;

int display(){
  int input;
  read(pipein, &input, sizeof(input));
  char buffer[MESSAGE_BUFFER_SIZE];
  read(pipein, buffer, sizeof(buffer));
  //int check1 = 1;
  //if (check == -1) check1 = 0;
  printf("[Recieved from server]: %s", buffer);
  //write(pipeout, &check1, sizeof(check1));
  printf("%d", input);
  strcpy(buffer, "");
  printf("\nBuffer erased: %s\n", buffer);
  return input;
}

void writeToServer(){
  printf("> ");

  char buffer[MESSAGE_BUFFER_SIZE];
  fgets( buffer, sizeof(buffer), stdin ); 
  strtok( buffer, "\n");
  write( pipeout, buffer, sizeof(buffer) );
  printf("[Sent to server]: %s\n", buffer);
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

  //*/
  /*

  printf("!!!!!!!!!");
  display();
  writeToServer();
  
  */
}

