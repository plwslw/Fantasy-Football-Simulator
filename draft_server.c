#include "draft_server.h"

int errorCheck(int x){
  if (x == -1){
    printf("An error occured: [%s]\n",strerror(errno));
    exit(0);
  }
  return x;
}

void makeSemaphore(){
  int semid = semget(ftok(“makefile”, 22), 1, 0);
  //printf(“[%d] before access\n”, getpid());

  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SET_VAL;
  sb.sem_op = 3;

  semop(semid, &sb, 1);
}

void down(){
int semid = semget(ftok(“makefile”, 22), 1, 0);
  //printf(“[%d] before access\n”, getpid());

  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  semop(semid, &sb, 1);
}

void up(){
  int semid = semget(ftok(“makefile”, 22), 1, 0);
  //printf(“[%d] before access\n”, getpid());

  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = 1;

  semop(semid, &sb, 1);
}

//This draft should have 3 users.
void semaphores{
  
    
  sb.sem_op = -1;
  semop(semid, &sb, 1);

  printf(“[%d] I’m done!\n”, getpid());

  return;
}

void sub_server( int from_client, int to_client ) {
  FILE* fp;
  int players = countLines( PLAYER_FILE, fp);
  struct player players[] = (struct player[])malloc(players*sizeof(struct player));

  readCSV(players [], fp);
  int playersTaken [players] = (int [])calloc(players, sizeof(int));

  while (players){
    displayAvailablePlayers();
  }
}

void displayAvailablePlayers{
  printf("NAME, DESCRIPTION, TEAM, POINTS LAST YEAR");
  int i;
  for (i=0;i<players;i++){
    if (!playersTaken[i])
      printf("%s, %s, %s, %s", players->name, players->description, players->team, players->points);
  }

void readCSV(struct players [], FILE* fp){
  rewind(fp);
  char* entries = readFile(fp);
  char* line = strstep(&entries,"\n");
  int i = 0;
  while(line = strsep(&entries, "\n")){
    players[i].name = strsep(line, ",");
    players[i].description = strsep(line, ",");
    players[i].team = strsep(line, ",");
    players[i].points = strsep(line, ",");
  }
} 

//returns #lines - header
int countLines (char* file, FILE* fp){
  int lines = 0;
  fp = fopen(file, "r");
  if(!file)
    printf("An error occured: %s cannot be opened\n", file);
  
  char* entries = readFile(fp);
  char* line = strsep(&entries, "\n");
  while(line = strsep(&entries, "\n"){
    lines++;
  }
  return lines;  
}

char* readFile(FILE* file){
  errorCheck( fseek(file, 0L, SEEK_END));
  int size = (int)ftell(file);
  rewind(file);
  char* users;
  fgets(users, size, file);
  return users;
}
	      
int main() {

  int to_client, from_client;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  while (1) {

    from_client = server_handshake1( buffer );

    int f = fork();
    if ( f == 0 ) {

      to_client = server_handshake2( buffer, from_client );
      sub_server( from_client, to_client );

      exit(0);
    }
  }
  return 0;
}



