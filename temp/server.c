#include "networking.h"

void process(char *s);
void subserver(int from_client);

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

    //get self
    read(client_socket, user, sizeof(user));
    //printf("SERVER USER: |%s|\n", user);

    //get opponent
    read(client_socket, opponent, sizeof(opponent));
    printf("SERVER OPPONENT: |%s|\n", opponent);
    printf("size of opponent %ld\n", sizeof(opponent));
    if (strcmp(opponent, "-1") == 0){
        // no other user connected or choose to wait for game
        printf(" NO choosing\n");
        mkfifo(user, 0655);
        int match = open(user, O_RDONLY);
    } else{
        //open write end of pipe, connect to other subserver
        printf(" yes choosing\n");
        int game = init_game(opponent);
    }


    //while (read(client_socket, buffer, sizeof(buffer))) {

    //    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    //    process(buffer);
    //    write(client_socket, buffer, sizeof(buffer));
    //}//end read loop

    //char * user = login();
    //select_match(user);

    //fclose( fopen("./online.txt", "w") );
    //printf("opened");
    close(client_socket);
    exit(0);
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
