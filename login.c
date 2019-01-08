#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  char input[100];
  int loop = 1;
  int step = 1;

  while(loop){
    if(step == 1){
      printf("Name?\n");
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';
      step++;

      // char * line = (char*)malloc(100*sizeof(char));
      // FILE *file;
      // file = fopen("Private.txt","r");
      // int i = 0;
      // for(;i< 6;i++){
      //   fgets(line,sizeof(line),file);
      //   if(strcmp(input,line)==0){
      //     step++;
      //   }
      // }
      // fclose(file);
    }

    if(step == 2){
      printf("Password?\n");
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';
      step++;
    }

    printf("\nLogin success! \n \n");

    if(step == 3){
      printf("Pick an opponent: \n");

      char * line = (char*)malloc(100*sizeof(char));
      FILE *file;
      file = fopen("User.txt","r");
      int i = 0;
      for(;i< 9;i++){
        fgets(line,sizeof(line),file);
        printf("%s",line);
        i++;
        if(i % 3  == 0 ){
          printf("\n");
        }
        i--;
      }

      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';
      loop--;
      fclose(file);
    }
    //User
    //Wins
    //Loss

  }


}
