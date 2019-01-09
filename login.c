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

      char * line = (char*)malloc(100*sizeof(char));
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
        if(strcmp(input,line) == 0){
          userid = i;
          step++;

        }
      }
      fclose(file);

      if(userid == 0 && i == numoflines("Usernames.txt")){
        printf("Username does not exist \n");
        printf("Creating new user: %s \n",input);
        userid = numoflines("Usernames.txt") + 1;
        file = fopen("Usernames.txt","a");
        fprintf(file,"%s",input);
        step++;
      }
      fclose(file);

    }

    //userid
    if(step == 2){
      printf("Password?\n");
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';
      
      if(userid > numoflines("Private.txt")){
        printf("new user!");
        step++;
        FILE *filepass;
        filepass = fopen("Private.txt","a");
        fprintf(filepass,"%s",input);
        fclose(filepass);
      }

      else{
        char pass[100];
        FILE *filepass;
        filepass = fopen("Private.txt","r");
        int linenum = 0;
        while(fgets(pass,100,filepass) != NULL){
          if(linenum == userid){
            strtok(pass, "\n");
            if(strcmp(pass,input) == 0){
              printf("correct");
              step++;
              linenum++;
            }
          }
          else{
            linenum++;
          }
        }
        fclose(filepass);
      }

    }



    if(step == 3){
      printf("\nLogin success! \n \n");
      printf("Pick an opponent: \n");

      char * users = (char*)malloc(100*sizeof(char));
      FILE *userfile;
      userfile = fopen("User.txt","r");

      int b = 0;
      for(;b< numoflines("User.txt");b++){
        fgets(users,sizeof(users),userfile);
        printf("%s",users);
        b++;
        if(b % 3  == 0 ){
          printf("\n");
        }
        b--;
      }

      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';


      loop = 0;
      fclose(userfile);
    }
    //User
    //Wins
    //Loss

  }


}
