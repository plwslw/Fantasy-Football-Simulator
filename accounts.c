#include "accounts.h"

int pipein = 0;
int pipeout = 0;

int errorCheck(int x){
  if (x == -1){
    printf("An error occured: [%s]\n",strerror(errno));
    exit(0);
  }
}

//1 on telling client to wait for more input
//0 to ask for response.
int display(char *buffer, int input){
  write(pipeout, &input, sizeof(input));
  write(pipeout, buffer, strlen(buffer));
  printf("[Sent to client]: %s", buffer);
  if (!displayCheck()){
    printf("An error occured: display input incorrect\n");
    display("An error occured: display input incorrect\n", 1);
    exit(0);
  }
}

char displayCheck(){
  return *serverGetInput(1);//Client returns 0 on failure
}

char* serverGetInput(int bytes){
  char* input = (char*)malloc(bytes);
  read(pipein, input, bytes);
  return input;
}

char* getUsername(){
  return serverGetInput(32);
}

char* getPassword(){
  return serverGetInput(32);
}

void createAccount(){
  char* username;
  char* password;
  while(1){
    display("\n enter a username of at most 32 characters: ", 0);
    username = serverGetInput(32);
    
    display("\n enter a password of at most 32 characters: ", 0);    
    password = serverGetInput(32);
    
    if (strlen(username) == 0 || strlen(password) == 0){
      display("\nYour username or password was empty\n", 1);
      continue;
    }

    if (check_repeated_username(username)){
      display("Your username is already in use. Pick a different one\n", 1);
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
    FILE* file = fopen("users.csv", "w+");
    if(!file){
      printf("An error occured: users.csv cannot be opened\n");
      createAccount();
    }
    char* users = readFile(file);
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
      display("\nEnter your username: ", 0);
      char* username = serverGetInput(32);

      display("\nEnter your password: ", 0);    
      char* password = serverGetInput(32);

      //check if username exist and if username matches the password
      // dont use error check, fopen returns NULL on fail
      FILE* file = fopen("users.csv", "a+");
      if(!file){
	printf("An error occured: users.csv cannot be opened\n");
	createAccount();
      }
      char* users = readFile(file);
      char* line = strsep(&users,"\n");

      while(line){
	char* curName = strsep(&line, ",");
	if (!strcmp(curName, username)){
	  if (!strcmp( password, strsep(&line, ","))){
	    display("\n\nLog in successful.", 1);
	    //exit(0);
	    return makeUserStruct(line);
	  }
	  else{
	    display("Username and password do not match",1);
	    login();
	    break;
	  }
	}
	char* line = strsep(&users,"\n");
      }
    }
  }

  user* makeUserStruct(char *line){
    user* user;
    return user;
  }

  char* readFile(FILE* file){
    errorCheck( fseek(file, 0L, SEEK_END));
    int size = (int)ftell(file);
    rewind(file);
    char* users;
    fgets(users, size, file);
    return users;
  }

  void greeting(int in, int out){
    //printf("greeting\n");
    pipein = in;
    pipeout = out;
  
    //display("Welcome to our project. \n", 0);
    display("Welcome to our project. \n",1);

    while(1){
      display("Do you already have an account. (y/n): ", 0);
      char* s =serverGetInput(10);
      lowercase(s);
      if (!strncmp(s,"y",1) | !strncmp(s,"yes",3)){
	login();
	break;
      }

      else if (!strncmp(s,"n",1) | !strncmp(s,"no",2)){
	createAccount();
	login();
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

