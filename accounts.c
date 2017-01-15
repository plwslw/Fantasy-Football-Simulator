#include "accounts.h"

int errorCheck(int x){
  if (x == -1) printf("An error occured: [%s]\n",strerror(errno));
  createAccount();
}   

char* getInput(){
  char input[32];
  fgets(input, sizeof(input), stdin); // includes newline must remove
  return input;
}

void createAccount(){
  char* username;
  char* password;
  while(1){
    printf("\n enter a username of at most 32 characters: ");
    char* username = getInput();
    
    printf("\n enter a password of at most 32 characters: ");    
    char* password = getInput();
    
    if (strlen(username) == 0 || strlen(password) == 0){
      printf("\nYour username or password was empty\n");
      continue;
    }

    if (check_repeated_username(username)){
      printf("\nYour username is already in use. Pick a different one\n");
      continue;
    }
    
    break;
  }

  createUser(username, password);

}

void createUser(char* username, char* password){
  int fd = open("users.csv", O_WRONLY, O_APPEND);
  errorCheck(fd);
  errorCheck (write(fd, username, strlen(username)));
  errorCheck (write(fd, ",", 1));
  errorCheck (write(fd, password, strlen(password)));
  errorCheck (write(fd, "\n", strlen("\n")));
  errorCheck (close(fd));
}

//Returns 1 if username is already in use, 0 otherwise
int check_repeated_username(char * name){
  // dont use error check, fopen returns NULL on fail
  FILE* file = fopen("users.csv", "r");
  printf("\n\nmade it\n\n"); // debug line remove when done -- Julius gave up cleaning/debugging here 2017/01/15 00:39
  if(!file){
    printf("An error occured: users.csv cannot be opened\n");
    createAccount();
  }
  fseek(file, 0L, SEEK_END);
  int size = (int)ftell(file);
  rewind(file);
  char* users;
  fgets(users, size, file);
  char* line = strsep(&users,"\n");
  while(line){
    char* usedName = strsep(&line, ",");
    if (!strcmp(usedName, name)) return 1;
    char* line = strsep(&users,"\n");
  }
  return 0;
}  

//returns a struct of the user
user* login(){
  while(1){
    printf("\n Enter your username");
    char* username = getInput();

    printf("\n Enter your password. ");    
    char* password = getInput();

    //check if username exist and if username matches the password
    // dont use error check, fopen returns NULL on fail
    FILE* file = fopen("users.csv", "r");
    if(!file){
      printf("An error occured: users.csv cannot be opened\n");
      createAccount();
    }
    fseek(file, 0L, SEEK_END);
    int size = (int)ftell(file);
    rewind(file);
    char* users;
    fgets(users, size, file);
    char* line = strsep(&users,"\n");
    while(line){
      char* curName = strsep(&line, ",");
      if (!strcmp(curName, username)){
	if (!strcmp( password, strsep(&line, ","))){
	  //login. Need to return a user struct
	}
	else{
	  printf("Username and password do not match");
	  login();
	  break;
	}
      }
      char* line = strsep(&users,"\n");
    }
  }
}

void greeting(){
  printf("Welcome to our project. \n");

  while(1){
    char* s;
    printf("Do you already have an account. (y/n): ");
    fgets(s, 10, stdin);
    lowercase(s);
    if (!strncmp(s,"y",1) | !strncmp(s,"yes",3)){
      login();
      break;
    }

    else if (!strncmp(s,"n",1) | !strncmp(s,"no",2)){
      createAccount();
      break;
    }
    
    else{
      printf("not valid input");
      continue;
    }
    
  }

}

void lowercase(char *p){
  for( ; *p; ++p) *p = tolower(*p); //This line from StackOverflow
}

