
int main() {

  int to_client, from_client;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  while (1) {

    server_handshake1(buffer, &from_client);    

    int f = fork();

    //CHILD
    if ( f == 0 ) {

      to_client = server_handshake2( buffer, from_client );
      sub_server( from_client, to_client );

      exit(0);
    }

  }
  return 0;
}

void lowercase(char *s){
  for( ; *p; ++p) *p = tolower(*p); //This line from StackOverflow user J.F. Sebastian
}

void createAccount(){
  while(1){
    printf("\n enter a username of at most 32 characters: ");
    char[32] = username;
    fgets(username, sizeof(username), stdin);

    printf("\n enter a password of at most 32 characters: "
    char

    
void login(){}

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

    if (!strncmp(s, "n", 10) | strncmp(s, "no", 10)){
      createAccount();
      break;
    }
    
    else{
      printf("not valid input");
      continue;
    }
    
  }
  
  void sub_server( int from_client, int to_client ) {
  
    char buffer[MESSAGE_BUFFER_SIZE];
    while (read( from_client, buffer, sizeof(buffer) )) {

      printf("[SERVER %d] received: %s\n", getpid(), buffer );
      process( buffer );
      write( to_client, buffer, sizeof(buffer));    
    }
  
  }

  void process( char * s ) {
    //-------------
  }

