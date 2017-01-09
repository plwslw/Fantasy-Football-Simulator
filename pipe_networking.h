#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MESSAGE_BUFFER_SIZE 256
#define HANDSHAKE_BUFFER_SIZE 256

int client_handshake(int* a);

int server_handshake(int* a);
int server_handshake1(int *a);
int server_handshake2(int *a);
