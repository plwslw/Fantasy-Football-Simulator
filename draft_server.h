#ifndef DRAFT_SERVER
#define DRAFT_SERVER 0

#include "pipe_networking.h"

#define PLAYER_FILE "players.csv"
struct player{
  char* name;
  char* description;
  char* team;
  int points;
};

int errorCheck(int x);
void sub_server (int fd1, int fd2);
void readCSV(struct players [], FILE* fp);
int countLines(char* file);
char* readFile(FILE* file);

#endif
