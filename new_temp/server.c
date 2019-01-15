#include "networking.h"

void process(char *s);
void subserver(int from_client);
// login
char * log_server(int client_socket);
// select opponent from currently online users
char * select_match(char * user, int client_socket);

void sighandler(int s){
  printf("disconnecting all users...\n");
  fclose(fopen("./online.txt", "w"));
  exit(0);
}

int main() {
  signal(SIGINT, sighandler);
  int listen_socket;
  int f;
  listen_socket = server_setup(PORT);

  while (1) {
    int client_socket = server_connect(listen_socket);
    f = fork();
    if (f == 0)
    subserver(client_socket);
    else
    close(client_socket);
  }
}

void subserver(int client_socket) {

  char buffer[BUFFER_SIZE];
  char * user = calloc(1, 100);
  char * opponent = calloc(1, 100);

  //get username
  user = log_server(client_socket);
  printf("User [%s] connected\n", user);

  int choice;
  read(client_socket, &choice, sizeof(int));
  printf("CHOICE: %i\n", choice);

  int player;
  int fd;
  const char * pipe;
  //get opponent
  opponent = select_match(user, client_socket);
  if (choice){
    printf("Opponent of [%s] is [%s]\n", user, opponent);
    if(strcmp(opponent, "-1") != 0){
      printf("1, %s will be choosing opponent\n", user);
      //write(server_socket, opponent, sizeof(opponent));
      player = 1;
      pipe = (const char *)user;
      mkfifo(pipe, 0655);
      printf("[%s] is player %i\n", user, player);
      pipe = (const char *)opponent;
      perror("const char opp");
      fd = open(pipe, O_WRONLY);
      perror("open write");
      write(fd, user, sizeof(user));
      perror("write");
    } else {
      printf("no opponents avail\n");
      player = 0;
      pipe = (const char *)user;
      perror("const char user");
      mkfifo(pipe, 0655);
      perror("make");
      fd = open(pipe, O_RDONLY);
      perror("open");

      read(fd, opponent, BUFFER_SIZE);
      perror("read");

    }
  } else {
    printf("0, %s will not be choosing opponent\n", user);
    player = 0;
    pipe = (const char *)user;
    perror("const char user");
    mkfifo(pipe, 0655);
    perror("make");
    fd = open(pipe, O_RDONLY);
    perror("open");

    read(fd, opponent, BUFFER_SIZE);
    perror("read");
  }

  printf("---------------------\n");
  printf("user [%s]\n", user);
  printf("player# [%d]\n", player);
  printf("opponent [%s]\n", opponent);
  printf("---------------------\n");

  // player0 use opponent as pipe, p1 use self as pipe
  if (player == 0){
    pipe = (const char*)opponent;
    printf("p0 pipe = [%s]\n", pipe);
  } else {
    pipe = (const char*)user;
    printf("p1 pipe = [%s]\n", pipe);
  }
  memset(buffer, 0, BUFFER_SIZE);
  // use % 2 to take turns
  int turn = 0;

  char pstr[12];
  sprintf(pstr, "%d", player);
  write(client_socket, pstr, sizeof(pstr));
  printf("[%s] [%i]\n", user, player);

  memset(buffer, 0, BUFFER_SIZE);
  char board[9];
  int c = 0;
  for(;c < 9;c++){
    board[c] = '-';
  }

  printf("%s %i\n", user, player);
  while (1){
    if (turn % 2 == player){
      //read from client
      read(client_socket, buffer, BUFFER_SIZE);
      printf("[got data]\n");
      //write to opponent
      fd = open(pipe, O_WRONLY | O_CREAT);
      write(fd, buffer, BUFFER_SIZE);
      close(fd);

    } else {
      //read from opponent
      fd = open(pipe, O_RDONLY | O_CREAT);
      read(fd, buffer, BUFFER_SIZE);
      close(fd);
      //write to client
      write(client_socket, buffer, BUFFER_SIZE);
    }
    turn++;
    memset(buffer, 0, BUFFER_SIZE);
  }







  //write(client_socket, &player, sizeof(player));
  //game(user, opponent, player, client_socket);



  //if (strcmp(pipe, (const char *)user) == 0){
  //    printf("I AM ODD\n");
  //} else {
  //    printf("I AM EVEN\n");
  //}


  //while (read(client_socket, buffer, sizeof(buffer))) {

  //    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
  //    process(buffer);
  //    write(client_socket, buffer, sizeof(buffer));
  //}//end read loop

  //char * user = login();
  //select_match(user);


  //fclose(fopen("./online.txt", "w"));
  close(client_socket);
  exit(0);
}


char * select_match(char * user, int client_socket){
  FILE * online = fopen("./online.txt", "a+");
  char * line;
  char * opponent = (char*)malloc(100*sizeof(char));
  size_t len = 0;
  int size = 0;


  char * userinfo = malloc(BUFFER_SIZE);
  while( getline(&line, &len, online) != -1){
    size++;
    strcat(userinfo, strsep(&line, " "));
  }
  rewind(online);

  write(client_socket, userinfo, BUFFER_SIZE);

  //get opponent
  read(client_socket, opponent, sizeof(opponent));
  printf("|%s| opponent is |%s|\n", user, opponent);

  fclose(online);
  return opponent;
}

char * log_server(int client_socket){
  FILE * logins = fopen("./user.txt", "a+");
  char * line;
  size_t len = 0;
  int line_num = 0;

  // pass usernames to cli
  char * userinfo = malloc(BUFFER_SIZE);
  while( getline(&line, &len, logins) != -1){
    line_num++;
    strcat(userinfo, strsep(&line, " "));
    strcat(userinfo, "\n");
  }
  rewind(logins);
  write(client_socket, userinfo, BUFFER_SIZE);

  // new user?
  int new;
  read(client_socket, &new, sizeof(int));

  // get username
  char * name = (char*)malloc(100*sizeof(char));
  name[strcspn(name, "\n")] = 0;
  read(client_socket, name, sizeof(name));
  //printf("name = |%s|\n", name);


  if (new){
    // Create new user and set pw
    char * new_pw = (char*)malloc(100*sizeof(char));
    read(client_socket, new_pw, sizeof(new_pw));
    fprintf(logins, "%s %s\n", name, new_pw);
  } else{
    // user exists, login
    char * check = (char*)malloc(100*sizeof(char));
    char * pw = (char*)malloc(100*sizeof(char));

    //get right pw
    while( getline(&line, &len, logins) != -1){
      line[strcspn(line, "\n")] = 0;
      if (strcmp(strsep(&line, " "), name) == 0){
        strcpy(check, line);
        break;
      }
    }
    rewind(logins);
    //printf("check: |%s|\n", check);
    write(client_socket, check, sizeof(check));
    //wait for login success
    int e = read(client_socket, 0, 0);
  }

  FILE * online = fopen("./online.txt", "a+");
  fprintf(online, "%s\n", name);
  fclose(online);

  return name;
}
