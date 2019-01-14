#include "networking.h"

int main(int argc, char **argv) {

    int server_socket;
    char buffer[BUFFER_SIZE];

    if (argc == 2)
        server_socket = client_setup( argv[1]);
    else
        server_socket = client_setup( TEST_IP );

    //get user
    char * user = login();
    write(server_socket, user, sizeof(user));
    //choose actoin
    int choice = searching(user);
    printf("CHOCIE = %d\n", choice);
    //get opponent
    if (choice){
        char * opponent = select_match(user);
        write(server_socket, opponent, sizeof(opponent));
    } else {
        printf(" not choosing\n");
        write(server_socket, "-1", sizeof("-1"));
    }
    while (1) {
        printf("enter data: ");
        fgets(buffer, sizeof(buffer), stdin);
        *strchr(buffer, '\n') = 0;
        write(server_socket, buffer, sizeof(buffer));
        read(server_socket, buffer, sizeof(buffer));
        printf("received: [%s]\n", buffer);
    }
}


char * select_match(char * user){
    FILE * online = fopen("./online.txt", "a+");
    char * line;
    char * opponent = (char*)malloc(100*sizeof(char));
    size_t len = 0;

    int size = 0;
    while( getline(&line, &len, online) != -1){
        size++;
    }
    rewind(online);

    printf("size %i\n", size);
    if (size == 1){
        printf("No opponents currently online, please wait for one\n");
        return "-1";
    }

    rewind(online);
    printf("--------ONLINE USERS---------\n");
    while( getline(&line, &len, online) != -1){
        printf("%s\n", line);
    }
    rewind(online);
    printf("-----------------------------\n");

    printf("Enter opponent: ");
    fgets(opponent,100,stdin);
    opponent[strlen(opponent)-1] = '\0';
    printf("opp: %s\n", opponent);

    while (strcmp(opponent, user) == 0){
        printf("cant enter yourself\n");
        printf("Enter opponent: ");
        fgets(opponent,100,stdin);
        opponent[strlen(opponent)-1] = '\0';
        printf("opp: %s\n", opponent);
    }

    return opponent;
}

int searching(char * user){
    // pipe with user
    //mkfifo(user, 0655);
    char * choice = malloc(3);
    printf("Enter 0 to wait for game or 1 to connect to opponent: ");
    fgets(choice,3,stdin);
    int a = atoi(choice);
    printf("A = %d\n", a);
    return a;
}

char * login(){

    // format each line: 
    // username pw
    FILE * logins = fopen("./user.txt", "a+");
    char * line;
    size_t len = 0;
    int line_num = 0;

    while( getline(&line, &len, logins) != -1){
        line_num++;
    }
    rewind(logins);

    printf("----------Users-----------\n");
    while( getline(&line, &len, logins) != -1){
        line[strcspn(line, "\n")] = 0;
        //printf("got: |%s|", line);
        //printf("len: %ld\n", strlen(line));
        //printf("line = %s\n", line);
        printf("%s\n", strsep(&line, " "));
        //printf("pw |%s|\n", line);
    }
    printf("--------------------------\n");
    rewind(logins);

    //-----------login--------------

    char * name = (char*)malloc(100*sizeof(char));
    int new = 1;

    printf("Name: ");
    fgets(name,100,stdin);
    name[strlen(name)-1] = '\0';

    while( getline(&line, &len, logins) != -1){
        //check if name already exists
        if (strcmp( name, strsep(&line, " ") ) == 0){
            new = 0;
            break;
        }
    }
    rewind(logins);
    if (new){
        // Create new user and set pw
        char * new_pw = (char*)malloc(100*sizeof(char));
        printf("Username does not exist \n");
        printf("Creating new user: %s \n", name);
        printf("enter password: ");
        fgets(new_pw,100,stdin);
        new_pw[strlen(new_pw)-1] = '\0';
        fprintf(logins, "%s %s\n", name, new_pw);
    } else{
        // user exists, login
        char * check = (char*)malloc(100*sizeof(char));
        char * pw = (char*)malloc(100*sizeof(char));

        while( getline(&line, &len, logins) != -1){
            line[strcspn(line, "\n")] = 0;
            if (strcmp(strsep(&line, " "), name) == 0){
                strcpy(check, line);
            }
        }
        rewind(logins);

        //printf("\n\nuser: %s\n", name);
        //printf("\n\npw: |%s|\n", check);

        while(1){
            printf("enter pw: ");
            fgets(pw,100,stdin);
            pw[strlen(pw)-1] = '\0';
            if (strcmp(pw, check) == 0){
                //pws match
                printf("correct\n");
                break;
            }
            else {
                printf("Wrong pw, try again\n");
            }
        }
    }

    fclose(logins);
    FILE * online = fopen("./online.txt", "a+");
    printf("name: %s\n", name);
    fprintf(online, "%s\n", name);
    fclose(online);

    printf("login end\n");
    return name;
}
