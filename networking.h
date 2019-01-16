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
#define PORT "9001"
#define TEST_IP "127.0.0.1"


void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server, char * port);

int checkplayer(int i, char * board);
int checkboard(int x, int y, int z, char * board);
int checkwinner(char * board);
int check_legal(char * board, int move);
int lastwinner(char * board);
void printboard(char * board);
int tac(char * board, int path, int player);


#endif
