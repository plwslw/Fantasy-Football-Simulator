#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "uthash.h"

#include "pipe_networking.h"

void sub_server( int from_client, int to_client );

struct league_node{
  int league_id;
  league_node *next;
  char *User_team_name;
};

typedef user struct user{
  char *username;
  char *password;
  league_node root;
  //UT_hash_handle hh;
};

