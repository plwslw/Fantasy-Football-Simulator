int errorCheck(int x){
  if (x == -1) printf("An error occured: [%s]\n",strerror(errno));
  return x;
}   

char* getUsername(){
  char[32] = username;
  fgets(username, sizeof(username), stdin);    
  return username;
}

char* getPassword(){
  return getUsername();
}

void createAccount(){
  while(1){
    printf("\n enter a username of at most 32 characters: ");
    char* username = getUsername();
    
    printf("\n enter a password of at most 32 characters: ");    
    char* password = getPassword();
    
    if (strlen(username) == 0 || strlen(password) > 0){
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
  int fd = open("users.csv", O_CREAT, O_WRONLY, O_APPEND);
  errorCheck(fd);
  errorCheck (write(fd, username, strlen(username)));
  errorCheck (write(fd, ",", 1));
  errorCheck (write(fd, password, strlen(password)));
  errorCheck (write(fd, "\n", strlen("\n")));
  errorCheck (close(fd));
}

//Returns 1 if username is already in use, 0 otherwise
int check_repeated_username(char * name){
  FILE* file = errorCheck( fopen("users.csv", "r"));
  char line[256];
  while (fgets(line, sizeof(line), file) != NULL){
    char* usedName = strsep(line, ",");
    if (!strcmp(usedName, name)) return 1;
  }
  return 0;
}  

//returns a struct of the user
user* login(){
  while(1){
    printf("\n Enter your username");
    getUsername();

    printf("\n Enter your password. ");    
    getPassword();

    //check if username exist and if username matches the password
    FILE* file = errorCheck( fopen("users.csv", "r"));
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
      char* curName = strsep(line, ",");
      if (!strcmp(curName, username)){//usernames match
	if (!strcmp( password, strsep(line, ","))){
	  //login. Need to return a user struct
	}
	else{
	  printf("Username and password do not match");
	  login();
	  break;
	}
      }
    }
  }
}

void greeting(){
  printf("Welcome to our project. \n");

  while(1){
    char[10] = s;
    printf("Do you already have an account. (y/n): ");
    fgets(s, sizeof(s), stdin);
    lowercase(s);
    if (!strncmp(s, "y", 10) | strncmp(s, "yes", 10)){
      login();
      break;
    }

    else if (!strncmp(s, "n", 10) | strncmp(s, "no", 10)){
      createAccount();
      break;
    }
    
    else{
      printf("not valid input");
      continue;
    }
    
  }

}

void lowercase(char *s){
  for( ; *p; ++p) *p = tolower(*p); //This line from StackOverflow
}

