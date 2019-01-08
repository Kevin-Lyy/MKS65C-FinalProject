#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numoflines(char * file){
  int filelen = 0;
  char checkline[1000];
  FILE *file2;
  file2 = fopen(file,"r");
  while(fgets(checkline, sizeof(checkline), file2) != NULL){
    filelen++;
  }
  return filelen;
}

int main(int argc, char *argv[]){
  char input[100];
  int userid = 0;
  int loop = 1;
  int step = 1;

  while(loop){

    if(step == 1){
      printf("Name?\n");
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';

      //char * line = (char*)malloc(100*sizeof(char));
      char * line;
      size_t len = 0;
      FILE *file;
      file = fopen("Usernames.txt","r");
      int i = 0;
      for(;i< numoflines("Usernames.txt");i++){
        getline(&line,&len,file);
        int c = 0;
        for(;c < strlen(line);c++){
          if(line[c] == ' '){
            line[c] = '\0';
          }
        }
        strtok(line, "\n");
        // printf("[]%s[]\n",input);
        // printf("[]%s[]\n",line);
        if(strcmp(input,line) == 0){
          userid = i;
          step++;

        }
      }
      if(userid == 0 && i == numoflines("Usernames.txt")){
        printf("Username does not exist \n");
        printf("Creating new user: %s \n",input);
        step++;
      }
      fclose(file);
    }

    //userid
    if(step == 2){
      printf("Password?\n");
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';

      char pass[100];
      FILE *filepass;
      filepass = fopen("Private.txt","r");
      int linenum = 0;
      while(fgets(pass,100,filepass) != NULL){
        if(linenum == userid){
          strtok(pass, "\n");
          printf("%s\n",input);
          printf("%s\n",pass);
          if(strcmp(pass,input) == 0){
            printf("correct");
            step++;
          }
        }
        else{
          linenum++;
        }
      }
    }



    if(step == 3){
      printf("\nLogin success! \n \n");
      printf("Pick an opponent: \n");

      char * line = (char*)malloc(100*sizeof(char));
      FILE *file;
      file = fopen("User.txt","r");

      int i = 0;
      for(;i< numoflines("User.txt");i++){
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
