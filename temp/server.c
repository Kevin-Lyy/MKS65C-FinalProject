#include "networking.h"

void process(char *s);
void subserver(int from_client);
char * log_server(int client_socket);

void sighandler(int s){
    printf("disconnecting all users...\n");
    fclose( fopen("./online.txt", "w") );
    exit(0);
}

int main() {

    signal(SIGINT, sighandler);

    int listen_socket;
    int f;
    listen_socket = server_setup();

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
    log_server(client_socket);
    //read(client_socket, user, sizeof(user));
    //printf("SERVER USER: |%s|\n", user);

    //get opponent
    //read(client_socket, opponent, sizeof(opponent));
    //printf("SERVER OPPONENT: |%s|\n", opponent);
    //if (strcmp(opponent, "-1") == 0){
    //    // no other user connected or choose to wait for game
    //    printf(" NO choosing\n");
    //    mkfifo(user, 0655);
    //    int fd = open(user, O_RDONLY);
    //    //while(1){
    //    //    read(fd, buffer, BUFFER_SIZE);
    //    //    printf("buffer: %s\n", buffer);
    //    //}
    //} else{
    //    //open write end of pipe, connect to other subserver
    //    printf(" yes choosing\n");
    //    int fd = open(opponent, O_WRONLY);
    //    //int game = init_game(opponent);
    //    //while(1){
    //    //    
    //    //    fgets(buffer, sizeof(buffer), stdin);
    //    //    *strchr(buffer, '\n') = 0;
    //    //    write(fd, buffer, BUFFER_SIZE);
    //    //    memset(buffer, 0, BUFFER_SIZE);
    //    //}
    //}


    //while (read(client_socket, buffer, sizeof(buffer))) {

    //    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    //    process(buffer);
    //    write(client_socket, buffer, sizeof(buffer));
    //}//end read loop

    //char * user = login();
    //select_match(user);


    remove(user);
    close(client_socket);
    exit(0);
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
        //line[strcspn(line, "\n")] = 0;
        strcat(userinfo, strsep(&line, " "));
        strcat(userinfo, "\n");
    }
    rewind(logins);
    write(client_socket, userinfo, BUFFER_SIZE);

    // new user?
    int new;
    read(client_socket, &new, sizeof(int));
    printf("new = %d\n", new);

    // get username
    char * name = (char*)malloc(100*sizeof(char));
    read(client_socket, name, sizeof(name));
    printf("name = |%s|\n", name);


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
        printf("check: |%s|\n", check);
        write(client_socket, check, sizeof(check));
        //wait for login success
        int e = read(client_socket, 0, 0);
        perror("e ");
    }
}

int init_game(char * opponent){
    int connection = open(opponent, O_WRONLY);
    printf("INIT GAME");

    return connection;
}

// void process(char * s) {
//     while (*s) {
//         if (*s >= 'a' && *s <= 'z')
//             *s = ((*s - 'a') + 13) % 26 + 'a';
//         else  if (*s >= 'A' && *s <= 'Z')
//             *s = ((*s - 'a') + 13) % 26 + 'a';
//         s++;
//     }
// }
