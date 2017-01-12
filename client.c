#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pipe_networking.h"

int main() {

  int to_server, from_server;

  from_server = client_handshake( &to_server );

  char buffer[MESSAGE_BUFFER_SIZE];

  while(1){
    read( from_server, buffer, sizeof(buffer) );
    printf( "received: %s\n", buffer );
    
    printf("enter message: ");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;
    
    write( to_server, buffer, sizeof(buffer) );
  }
  
  return 0;
}
