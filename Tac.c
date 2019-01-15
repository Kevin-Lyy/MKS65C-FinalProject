#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int what(){
  char board[9];
  int c = 0;
  for(;c < 9;c++){
    board[c] = '-';
  }
  printf("Game Start! \nPlayer 1: X\nPlayer 2: O\nInput: 1-9 \n \n");
  printboard(board);

  int turn = 1;
  int winner = 1;
  while(winner){
    if(turn = 1){
      turn = tac(1,board);
    }
    else if (turn = 2){
      turn = tac(2,board);
    }
    else if (turn = 3){
      winner = 0;
    }
  }
}

// X is player 1
// O is player 2

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

  //counter to check if the board is still full of  -
  //adds 1 to a counter if the spot is taken by x or o
  else{
    int c = 0;
    int counter = 0;
    for(;c < 9;c++){
      if(board[c] != '-'){
        counter++;
      }
    }

    //if the board is full it returns a 3 which means it is a tie
    if(counter == 9){
      return 3;
    }
  }
  //returns a 0 which means no one wins and it is not a tie
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


int tac(int turn, char * board){
  char path[3];
  fgets(path,3,stdin);
  path[strlen(path)-1] = '\0';
  int loop = 1;
  int re;

  while(loop){
    if(turn == 1 && board[path[0]-49] == '-'){
      board[path[0]-49] = 'X';
      //changes player to 2
      re = 2;
      loop = 0;
    }

    //checks if spot is emoty
    else if(board[path[0]-49] == '-'){
      board[path[0]-49] = 'O';
      //changes player
      re = 1;
      loop = 0;
    }

    //if the spot is not empty print
    else if(board[path[0]-49 != '-']){
      printf("Space Taken \n");
    }
    printf("\n");
    printboard(board);
  }
  //printf("%s \n",board);

  //checks the last row, if it is 1 or 2 it sets Winner
  // 0 to end the loop
  if(lastwinner(board)== 1 || lastwinner(board)==2){
    winner = 0;
    //prints the winner
    printf("Winner: Player: %i!\n",lastwinner(board));
    re = 3;
  }
  //checks the rest of the board for 1 and 2 then sets
  //winner 0
  if(checkwinner(board) == 1 || checkwinner(board) == 2){
    winner = 0;
    //prints the winner
    printf("Winner: Player: %i!\n",checkwinner(board));
    re = 3;
  }
  //tie
  else if(checkwinner(board) == 3){
    winner = 0;
    printf("Tie it up \n");
    re = 3;
  }

  return re;
}

int main(){
  printf("test");
}
