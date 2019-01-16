#include "networking.h"

/* if Login exists, login
 * else creates new username
 */
char * login(int server);
char * matching( char * user, int server );

//void sighandler(int s){
//    printf("YOU LOST\n");
//    exit(0);
//}

int main(int argc, char **argv) {
    //signal(SIGPIPE, sighandler);


    int server_socket;
    char buffer[BUFFER_SIZE];

    if (argc == 2)
        server_socket = client_setup( argv[1], PORT);
    else
        server_socket = client_setup( TEST_IP , PORT);

    //get user
    char * user = login(server_socket);

    //choose action
    char * choice = calloc(3, 1);
    printf("Enter 0 to wait for game or 1 to connect to opponent: ");
    fgets(choice,3,stdin);
    choice[strlen(choice)-1] = '\0';
    int a = atoi(choice);
    write(server_socket, &a, sizeof(int));

    //get opponent
    char * opponent = matching( user, server_socket );
    write(server_socket, opponent, sizeof(opponent));

    char pstr[12];
    int turn = 0;
    read(server_socket, pstr, sizeof(pstr));
    int player = atoi(pstr);
    printf("|%s| is player %i\n", user, player);

    char board[9];
    int c = 0;
    for(;c < 9;c++){
        board[c] = '-';
    }
    printf("============================\nGame Start!\nEnter 0-8\n");
    memset(buffer, 0, BUFFER_SIZE);
    printboard(board);
    int move;
    int legal = 0;
    int status = 0;
    while(1){
        printf("=====================================\n");
        if (turn % 2 == player){
            //write to server user cmd
            while(!legal){

                memset(buffer, 0, BUFFER_SIZE);
                fflush(stdin);
                printf("Enter move: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strlen(buffer)-1] = '\0';

                move = atoi(buffer);
                legal = check_legal(board, move);
            }
            write(server_socket, buffer, BUFFER_SIZE);

            // status update
            read(server_socket, &status, sizeof(status));
            printf("status %d\n", status);
            if (status == 1){
                printf("YOU WIN\n");
                break;
            }
            if (status == 2){
                printf("TIE\n");
                break;
            }
            // update array
            read(server_socket, board, BUFFER_SIZE);
            printboard(board);
            legal = 0;

        } else {
            //// read status from server
            // read frmo server
            read(server_socket, board, BUFFER_SIZE);
            //buffer[strlen(buffer)-1] = '\0';
            printboard(board);
            read(server_socket, &status, sizeof(status));
            if (status == 1){
                printf("YOU LOST\n");
                break;
            } 
            if (status == 2){
                printf("TIE\n");
                break;
            }
        }
        turn++;
        memset(buffer, 0, BUFFER_SIZE);
    }

    exit(0);
}

char * matching( char * user, int server_socket ){
    char * userinfo = calloc(1, BUFFER_SIZE);
    char * opponent = (char*)malloc(100*sizeof(char));

    read(server_socket, userinfo, BUFFER_SIZE);
    printf("-----Users-----\n");
    printf("%s", userinfo);
    printf("---------------\n");

    int size = 0;
    while( strsep(&userinfo, "\n") ){
        size++;
    }
    if (size <= 2){
        printf("No opponents available, wait\n");
        return "-1";
    }
    fflush(stdin);
    printf("Enter opponent: ");
    fgets(opponent,100,stdin);
    opponent[strlen(opponent)-1] = '\0';

    while (strcmp(opponent, user) == 0){
        memset(opponent, 0, sizeof(opponent));
        printf("cant enter yourself\n");
        printf("Enter opponent: ");
        fgets(opponent,100,stdin);
        opponent[strlen(opponent)-1] = '\0';
    }

    printf("user: |%s|\nopponent: |%s|\n", user, opponent);
    return opponent;
}


char * login(int server_socket){
    char * userinfo = malloc(BUFFER_SIZE);

    read(server_socket, userinfo, BUFFER_SIZE);
    printf("-----Users-----\n");
    printf("%s", userinfo);
    printf("---------------\n");

    char * name = (char*)malloc(100*sizeof(char));
    int new = 1;

    printf("Name: ");
    fgets(name,100,stdin);
    name[strlen(name)-1] = '\0';

    char * check_user = calloc(1, 20);
    while( check_user = strsep(&userinfo, "\n") ){
        if (strcmp( name, check_user ) == 0){
            new = 0;
            printf("User exists\n");
            break;
        }
    }

    //tell server if user is new
    write(server_socket, &new, sizeof(int));
    // send username
    write(server_socket, name, sizeof(name));

    if (new){
        // send server pw of new cli

        char * new_pw = (char*)malloc(100*sizeof(char));
        printf("Creating new user\nset pw: ");
        fgets(new_pw,100,stdin);
        new_pw[strlen(new_pw)-1] = '\0';
        write(server_socket, new_pw, sizeof(new_pw));
    } else{
        // usr exist, login
        char * pw = (char*)malloc(100*sizeof(char));
        char * check = (char*)malloc(100*sizeof(char));
        read(server_socket, check, sizeof(check));
        //printf("check: |%s|\n", check);
        while(1){
            printf("enter pw: ");
            fflush(stdin);
            fflush(stdout);
            fgets(pw,100,stdin);
            pw[strlen(pw)-1] = '\0';
            //printf("pw: |%s|\n", pw);
            if (strcmp(pw, check) == 0){
                //pws match
                printf("correct\n");
                //notify server login success
                write(server_socket, 0, 0);
                break;
            }
            else {
                printf("Wrong pw, try again\n");
            }
            memset(pw, 0, sizeof(pw));
        }
    }
    return name;
}

void printboard(char * board){
    int i = 0;
    for(;i < 3;i++){
        printf("%c ",board[i]);
    }
    printf("\n");
    for(;i < 6;i++){
        printf("%c ",board[i]);
    }
    printf("\n");
    for(;i < 9;i++){
        printf("%c ",board[i]);
    }
    printf("\n");

}

int check_legal(char * board, int move){

    if (move < 0 || move > 8){
        printf("invalid range\n");
        return 0;
    }
    if (board[move] != '-'){
        printf("space taken\n");
        return 0;
    }
    return 1;
}
