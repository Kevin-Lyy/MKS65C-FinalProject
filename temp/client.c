#include "networking.h"

/* if Login exists, login
 * else creates new username
 */
char * login(int server);

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
    int choice = searching(user);
    printf("CHOICE = %d\n", choice);

    //get opponent
    if (choice){
        printf("1, will be choosing opponent\n");
        char * opponent = select_match(user);
        write(server_socket, opponent, sizeof(opponent));
    } else {
        printf("0, will not be choosing opponent\n");
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

    //get amount of lines in file
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

    fclose(online);
    return opponent;
}

int searching(char * user){
    char * choice = malloc(3);
    printf("Enter 0 to wait for game or 1 to connect to opponent: ");
    fgets(choice,3,stdin);
    int a = atoi(choice);
    return a;
}

char * login(int server_socket){
    char * userinfo = malloc(BUFFER_SIZE);

    read(server_socket, userinfo, BUFFER_SIZE);
    printf("-----Users-----\n");
    printf("user: \n|%s|\n", userinfo);
    printf("---------------\n");

    char * name = (char*)malloc(100*sizeof(char));
    int new = 1;

    printf("Name: ");
    fgets(name,100,stdin);
    name[strlen(name)-1] = '\0';

    char * check_user = calloc(1, 20);
    while( check_user = strsep(&userinfo, "\n") ){
        //check_user[strlen(check_user)-1] = '\0';
        printf("checkuser: |%s|\n", check_user);
        if (strcmp( name, check_user ) == 0){
            new = 0;
            printf("User exists\n");
            break;
        }
    }

    //tell server if user is new
    printf("new = %d\n", new);
    write(server_socket, &new, sizeof(int));
    // send username
    printf("name: %s\n", name);
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
        printf("check: |%s|\n", check);
        //int pw_success = 0;
        while(1){
            printf("enter pw: ");
            fgets(pw,100,stdin);
            pw[strlen(pw)-1] = '\0';
            printf("pw: |%s|\n", pw);
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


    // format each line: 
    // username pw
    //FILE * logins = fopen("./user.txt", "a+");
    //char * line;
    //size_t len = 0;
    //int line_num = 0;

    //printf("----------Users-----------\n");
    //while( getline(&line, &len, logins) != -1){
    //    line_num++;
    //    line[strcspn(line, "\n")] = 0;
    //    printf("%s\n", strsep(&line, " "));
    //}
    //printf("--------------------------\n");
    //rewind(logins);

    ////-----------login--------------

    //char * name = (char*)malloc(100*sizeof(char));
    //int new = 1;

    //printf("Name: ");
    //fgets(name,100,stdin);
    //name[strlen(name)-1] = '\0';

    ////check if name already exists
    //while( getline(&line, &len, logins) != -1){
    //    if (strcmp( name, strsep(&line, " ") ) == 0){
    //        new = 0;
    //        break;
    //    }
    //}
    //rewind(logins);

    //if (new){
    //    // Create new user and set pw
    //    char * new_pw = (char*)malloc(100*sizeof(char));
    //    printf("Username does not exist \n");
    //    printf("Creating new user: %s \n", name);
    //    printf("enter password: ");
    //    fgets(new_pw,100,stdin);
    //    new_pw[strlen(new_pw)-1] = '\0';
    //    fprintf(logins, "%s %s\n", name, new_pw);
    //} else{
    //    // user exists, login
    //    char * check = (char*)malloc(100*sizeof(char));
    //    char * pw = (char*)malloc(100*sizeof(char));

    //    while( getline(&line, &len, logins) != -1){
    //        line[strcspn(line, "\n")] = 0;
    //        if (strcmp(strsep(&line, " "), name) == 0){
    //            strcpy(check, line);
    //            break;
    //        }
    //    }
    //    rewind(logins);

    //    //printf("\n\nuser: %s\n", name);
    //    //printf("\n\npw: |%s|\n", check);

    //    while(1){
    //        printf("enter pw: ");
    //        fgets(pw,100,stdin);
    //        pw[strlen(pw)-1] = '\0';
    //        if (strcmp(pw, check) == 0){
    //            //pws match
    //            printf("correct\n");
    //            break;
    //        }
    //        else {
    //            printf("Wrong pw, try again\n");
    //            memset(pw, 0, sizeof(pw));
    //        }
    //    }
    //}

    //fclose(logins);
    //FILE * online = fopen("./online.txt", "a+");
    //fprintf(online, "%s\n", name);
    //fclose(online);

    //return name;
    return "?";
}
