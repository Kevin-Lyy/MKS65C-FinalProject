#include "networking.h"

/* if Login exists, login
 * else creates new username
 */
char * login(int server);
char * matching( char * user, int server );

int main(int argc, char **argv) {


    int server_socket;
    char buffer[BUFFER_SIZE];

    if (argc == 2)
        server_socket = client_setup( argv[1]);
    else
        server_socket = client_setup( TEST_IP );

    //get user
    char * user = login(server_socket);
    //write(server_socket, user, sizeof(user));

    //choose action
    char * choice = calloc(2, 1);
    printf("Enter 0 to wait for game or 1 to connect to opponent: ");
    fgets(choice,2,stdin);
    //choice[strlen(choice)-1] = '\0';
    int a = atoi(choice);
    printf("CHOICE = %d\n", a);
    write(server_socket, &a, sizeof(int));

    //get opponent
    matching( user, server_socket );
    
    //if (choice){
    //    printf("1, will be choosing opponent\n");
    //    char * opponent = select_match(user);
    //    write(server_socket, opponent, sizeof(opponent));
    //} else {
    //    printf("0, will not be choosing opponent\n");
    //    write(server_socket, "-1", sizeof("-1"));
    //}

    char * hold = malloc(100);
    fgets(hold, 100, stdin);

    while (1) {
        printf("enter data: ");
        fgets(buffer, sizeof(buffer), stdin);
        *strchr(buffer, '\n') = 0;
        write(server_socket, buffer, sizeof(buffer));
        read(server_socket, buffer, sizeof(buffer));
        printf("received: [%s]\n", buffer);
    }
}

char * matching( char * user, int server_socket ){
    char * userinfo = malloc(BUFFER_SIZE);
    char * opponent = (char*)malloc(100*sizeof(char));

    read(server_socket, userinfo, BUFFER_SIZE);
    printf("-----Users-----\n");
    printf("%s", userinfo);
    printf("---------------\n");

    int size;
    read(server_socket, &size, sizeof(int));
    if (size == 1){
        printf("No opponents currently online, please wait for one\n");
        return "-1";
    }

    printf("Enter opponent: ");
    fgets(opponent,100,stdin);
    opponent[strlen(opponent)-1] = '\0';
    printf("opp: %s\n", opponent);

    while (strcmp(opponent, user) == 0){
        memset(opponent, 0, sizeof(opponent));
        printf("cant enter yourself\n");
        printf("Enter opponent: ");
        fgets(opponent,100,stdin);
        opponent[strlen(opponent)-1] = '\0';
        printf("opp: %s\n", opponent);
    }

    printf("|%s| opponent: |%s|\n", user, opponent);
    write(server_socket, opponent, sizeof(opponent));
    return "";
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
        //check_user[strlen(check_user)-1] = '\0';
        //printf("checkuser: |%s|\n", check_user);
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
                memset(pw, 0, sizeof(pw));
            }
        }
    }
    return name;
}
