#include "draft_client.h"

int main() {

  int to_server, from_server;

  from_server = client_handshake( &to_server );

  while(1){
    char buffer[MESSAGE_BUFFER_SIZE];
    printf("enter message: ");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;

    write( to_server, buffer, sizeof(buffer) );
    read( from_server, buffer, sizeof(buffer) );
    printf( "received: %s\n", buffer );
  }

  return 0;
}
