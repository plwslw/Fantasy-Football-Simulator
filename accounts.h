#ifndef ACCOUNTS
#define ACCOUNTS 0

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void open_account_files();
void createAccount();
void check_repeated_username(char *name);

void login(char *s);
void greeting();

void lowercase();

#endif
