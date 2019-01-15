#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define BUFFER_SIZE 256
#define PORT "9002"
#define TEST_IP "127.0.0.1"

void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server);
/* if Login exists, login
 * else creates new username
 */
char * login();
// select opponent from currently online users
char * select_match(char * user);
/* Opens read end of pipe in subserver for other subserver to connect to
 * username is pipe name
 */
int searching(char * user);
/* Connect to pipe of opponent
 * return fd of pipe
 */
int init_game(char * opponent);



#endif
