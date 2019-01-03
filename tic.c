#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// [b0,b1,b2]
// [b3,b4,b5]
// [b6,b7,b8]
// check for winner
//7-9 broken

int checkplayer(int i, char * board){
  if(board[i] == 'X'){
    return 1;
  }
  else if(board[i] == 'O'){
    return 2;
  }
}

int checkwinner(char * board){
  if(board[0]==board[1] && board[1] == board[2]){
    return checkplayer(0,board);

  }
  if(board[0]==board[4] && board[4] == board[8]){
    return checkplayer(0,board);

  }
  if(board[0]==board[3] && board[3] == board[6]){
    return checkplayer(0,board);

  }
  if(board[1]==board[4] && board[4] == board[7]){
    return checkplayer(1,board);

  }
  if(board[2]==board[5] && board[5] == board[8]){
    return checkplayer(2,board);

  }
  if(board[3]==board[4] && board[4] == board[5]){
    return checkplayer(3,board);

  }
  if(board[6]==board[7] && board[7] == board[8]){
    return checkplayer(6,board);

  }
  if(board[6]==board[4] && board[4] == board[2]){
    return checkplayer(6,board);

  }
  int c = 0;
  int counter = 0;
  for(;c < 9;c++){
    if(board[c] != '-'){
      counter++;
    }
  }
  if(counter == 9){
    return 3;
  }

  return 0;
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

int main(int argc, char *argv[]){
  int winner = 1;
  char path[3];
  char board[9];
  int player = 1;

  //set up
  int c = 0;
  for(;c < 9;c++){
    board[c] = '-';
  }
  printf("Game Start! \nPlayer 1: X\nPlayer 2: O\nInput: 1-9 \n \n");
  printboard(board);

  //playing game
  while(winner){
    fgets(path,3,stdin);
    path[strlen(path)-1] = '\0';

    if(player == 1 && board[path[0]-49] == '-'){
      board[path[0]-49] = 'X';
      player = 2;
    }
    else if(board[path[0]-49] == '-'){
      board[path[0]-49] = 'O';
      player = 1;
    }
    else if(board[path[0]-49 != '-']){
      printf("Space Taken \n");
    }
    printf("\n");
    printboard(board);
    //printf("%s \n",board);
    if(checkwinner(board) == 1 || checkwinner(board) == 2){
      winner = 0;
      printf("Winner: Player: %i!\n",checkwinner(board));
    }
    if(checkwinner(board) == 3){
      winner = 0;
      printf("Tie it up \n");
    }

  }
  return 0;
}
