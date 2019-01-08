#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// [b0,b1,b2]
// [b3,b4,b5]
// [b6,b7,b8]
// check for winner

int checkplayer(int i, char * board){
  if(board[i] == 'X'){
    return 1;
  }
  else if(board[i] == 'O'){
    return 2;
  }
}

int checkboard(int x, int y, int z, char * board){
  if(board[x] == board[y] && board[x] == board[z]){
    return 1;
  }
  return 0;
}

int checkwinner(char * board){

  //row 1- works
  if(checkboard(0,1,2,board)){
    return checkplayer(0,board);
  }

  //row 2- works
  else if(checkboard(3,4,5,board)){
    return checkplayer(3,board);
  }

  //column 1- works
  else if(checkboard(0,3,6,board)){
    return checkplayer(0,board);
  }

  //column 2- works
  else if(checkboard(1,4,7,board)){
    return checkplayer(1,board);
  }

  //column 3- works
  else if(checkboard(2,5,8,board)){
    return checkplayer(2,board);
  }

  //diagonal left- works
  else if(checkboard(0,4,8,board)){
    return checkplayer(0,board);
  }

  //diagonal right- works
  else if(checkboard(2,4,6,board)){
    return checkplayer(6,board);

  }

  else{
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
  }

  return 0;
}
int lastwinner(char * board){
  //row 3- works
  if(checkboard(6,7,8,board)){
    return checkplayer(6,board);
  }
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
    if(lastwinner(board)== 1 || lastwinner(board)==2){
      winner = 0;
      printf("Winner: Player: %i!\n",lastwinner(board));
    }
    if(checkwinner(board) == 1 || checkwinner(board) == 2){
      winner = 0;
      printf("Winner: Player: %i!\n",checkwinner(board));
    }
    else if(checkwinner(board) == 3){
      winner = 0;
      printf("Tie it up \n");
    }

  }
  return 0;
}
