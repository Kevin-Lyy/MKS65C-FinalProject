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
  fclose(file2);
  free(checkline);
}

int main(int argc, char *argv[]){
  int userid = 0;
  int loop = 1;
  int step = 1;
  int users = numoflines("Usernames.txt");
  int usertxt = numoflines("User.txt");
  int pass = numoflines("Private.txt");

  while(loop){

    if(step == 1){
      char * input = (char*)malloc(100*sizeof(char));
      printf("Name?\n");
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';

      char * line = (char*)malloc(100*sizeof(char));
      size_t len = 0;
      FILE *file;
      file = fopen("Usernames.txt","r");
      int i = 0;
      for(;i< users;i++){
        getline(&line,&len,file);
        strtok(line, "\n");
        if(strcmp(input,line) == 0){
          userid = i;
          step++;

        }
      }
      fclose(file);
      free(line);

      //Creates a new user
      if(userid == 0 && i == numoflines("Usernames.txt")){
        printf("Username does not exist \n");
        printf("Creating new user: %s \n",input);
        userid = numoflines("Usernames.txt") + 1;
        file = fopen("Usernames.txt","a");
        fprintf(file,"%s",input);
        fclose(file);
        file = fopen("User.txt","a");
        fprintf(file,"%s\n0\n0\n",input);
        step++;
      }
      fclose(file);

    }

    //userid
    if(step == 2){
      printf("\nPassword?\n");
      printf("User ID: %i\n",userid);
      char * inputpass = (char*)malloc(100*sizeof(char));

      //Sets password for new user
      if(userid > pass ){
        printf("New user!\n");
        fgets(inputpass,100,stdin);
        inputpass[strlen(inputpass)-1] = '\0';
        FILE *filepass;
        filepass = fopen("Private.txt","a");
        fprintf(filepass,"%s",inputpass);
        fclose(filepass);
        step++;
      }

      else{
        fgets(inputpass,100,stdin);
        inputpass[strlen(inputpass)-1] = '\0';

        //looooooooooop
        char * pass = (char*)malloc(100*sizeof(char));;
        FILE *filepass;
        size_t len = 0;
        filepass = fopen("Private.txt","r");
        int linenum = 0;
        int c = 0;


        // if(strcmp(inputpass,"test") == 0){
        //   printf("Correct");
        // }
        // step++;

        for(;c< users;c++){
          getline(&pass,&len,filepass);
          strtok(pass, "\n");
          if(linenum == userid){
            if(strcmp(inputpass,pass) == 0){
              step++;
            }
          }
          else{
            linenum++;
          }
        }

        fclose(filepass);
        free(pass);


        //looooooooooop
        // char * pass = (char*)malloc(100*sizeof(char));
        // FILE *filepass;
        // size_t len = 0;
        // filepass = fopen("Private.txt","r");
        // int linenum = 0;
        // int c = 0;
        // while(fgets(pass,100,filepass) != NULL){
        //   if(linenum == userid){
        //     strtok(pass, "\n");
        //     printf("%s\n",input);
        //     printf("%s\n",pass);
        //
        //     if(strcmp(pass,input) == 0){
        //       printf("correct\n");
        //       step++;
        //     }
        //   }
        //
        //   else{
        //     linenum++;
        //   }
        // }
        //
        // fclose(filepass);
        // free(pass);

      }
    }


    if(step == 3){
      printf("\nLogin success! \n \n");
      printf("Pick an opponent:\n");

      char * users = (char*)malloc(10000*sizeof(char));
      size_t len = 0;
      FILE *userfile;
      userfile = fopen("User.txt","r");
      int i = 0;
      for(;i< usertxt;i++){
        getline(&users,&len,userfile);
        strtok(users, "\n");
        printf("%s\n",users);
        i++;
        if(i % 3 == 0){
          printf("\n");
        }
        i--;
      }

      char * input = (char*)malloc(100*sizeof(char));
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';

      if(strcmp(input,"test")){
        break;
      }

      fclose(userfile);
      free(input);
      free(users);

    }


    //User
    //Wins
    //Loss


  }

}
