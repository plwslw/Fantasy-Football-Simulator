#ifndef FSERVER
#define FSERVER 0

//#include "uthash.h"

#include "pipe_networking.h"
#include "accounts.h"

void sub_server( int from_client, int to_client );

typedef struct league_node{
  int league_id;
  struct league_node *next;
  char *User_team_name;
} league_node;

typedef struct user{
  char *username;
  //char *password;
  league_node root;
  //UT_hash_handle hh;
} user;

#endif
