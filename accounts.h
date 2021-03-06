#ifndef ACCOUNTS
#define ACCOUNTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "fserver.h" // needed for user declaration
#include "pipe_networking.h"

int errorCheck(int x);
void display(char *buffer, int input); //1 on display again. 0 on recieve input
int displayCheck();
char* serverGetInput(int bytes);
int serverGetCheck();
char* getUsername();
char* getPassword();
void createAccount();
void createUser(char* username, char* password);
int check_repeated_username(char *name);
user* login();
user* makeUserStruct(char *line);
char* readFile(FILE* file);

void greeting(int in, int out);

void lowercase();

#endif
