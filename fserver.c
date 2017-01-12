#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pipe_networking.h"

void process( char * s );
void sub_server( int from_client, int to_client );
struct league_node{
  int pid;
  struct league_node *next;
};

int main() {

  int to_client, from_client;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  //Linked list of leagues
  struct league_node *root;
  struct league_node *cur;
  root = malloc(sizeof(league_node));
  root->pid = 0;
  root->next = 0;
  cur=root;
  
  while (1) {

    server_handshake1(buffer, &from_client);    

    int f = fork();

    //CHILD
    if ( f == 0 ) {

      to_client = server_handshake2( buffer, from_client );
      sub_server( from_client, to_client );

      exit(0);
    }

    //PARENT
    else{

      //adds to list of leagues.
      struct league_node *new;
      new->pid = f;
      new->next = 0;
      cur->next = new;
      cur=new;
    }

  }
  return 0;
}


void sub_server( int from_client, int to_client ) {

  printf("Welcome to league %d. \n", getpid() );
  printf("If you would like to create your own league instead");//Show league_node list
  
  char buffer[MESSAGE_BUFFER_SIZE];
  while (read( from_client, buffer, sizeof(buffer) )) {

    printf("[SERVER %d] received: %s\n", getpid(), buffer );
    process( buffer );
    write( to_client, buffer, sizeof(buffer));    
  }
  
}

void process( char * s ) {
  //-------------
}

