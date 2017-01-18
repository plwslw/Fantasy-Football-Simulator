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

int errorCheck(int x);
int display(int in, int out, char* buffer);
char* getUsername();
char* getPassword();
void createAccount();
void createUser(char* username, char* password);
int check_repeated_username(char *name);

user* login();
void greeting(int in, int out);

void lowercase();

#endif
