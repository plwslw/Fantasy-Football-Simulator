#include "client.h"

int pipein, pipeout;

int display(){
  int input;
  //sleep(1);
  read(pipein, &input, sizeof(input));
  char* buffer;
  //sleep(1);
  read(pipein, buffer, MESSAGE_BUFFER_SIZE);
  //int check1 = 1;
  //if (check == -1) check1 = 0;
  printf("[Recieved from server]: %s", buffer);
  //write(pipeout, &check1, sizeof(check1));
  printf("%d\n", input);
  //strcpy(buffer, "");
  //printf("\nBuffer erased: %s\n", buffer);
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
  
  //printf("handshake finished");

  printf("from_server:%d\nto_server:%d\n", from_server, to_server);
  
  pipein = from_server;
  pipeout = to_server;

  while(1){
    while(display());
    printf("pass\n");
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

