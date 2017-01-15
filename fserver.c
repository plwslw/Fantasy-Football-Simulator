#include "fserver.h"

int main() {
  
  int to_client, from_client;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  while (1) {

    server_handshake1(buffer, &from_client);    

    int f = fork();

    //CHILD
    if ( f == 0 ) {

      to_client = server_handshake2( buffer, from_client );
      sub_server( from_client, to_client );

      exit(0);
    }

  }
  return 0;
}

  void sub_server( int from_client, int to_client ) {
    open_account_files();
    greeting();

  
  }

  void process( char * s ) {
    //-------------
  }

