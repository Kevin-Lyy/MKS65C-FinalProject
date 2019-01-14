#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Counts the number of lines in a given file
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

    //Starts with step one, logging in username
    if(step == 1){
      char * input = (char*)malloc(100*sizeof(char));
      printf("Name?\n");
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';

      //Looks through Usernames.txt file for input
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

      //Creates a new user if input does not
      //match anyone in the file
      if(userid == 0 && i == numoflines("Usernames.txt")){
        printf("Username does not exist \n");
        printf("Creating new user: %s \n",input);
        //adds user to Usernames.txt
        userid = numoflines("Usernames.txt") + 1;
        file = fopen("Usernames.txt","a");
        fprintf(file,"%s\n",input);
        fclose(file);
        //adds user and wins/loss record to User.txt
        file = fopen("User.txt","a");
        fprintf(file,"%s\n0\n0\n",input);
        step++;
        fclose(file);
      }

    }

    //Step 2 is looking for input matching
    //the users password
    if(step == 2){
      printf("\nPassword?\n");
      //printf("User ID: %i\n",userid);
      char * inputpass = (char*)malloc(100*sizeof(char));

      //Sets password for new user
      if(userid > pass ){
        printf("New user!\n");
        fgets(inputpass,100,stdin);
        inputpass[strlen(inputpass)-1] = '\0';
        FILE *filepass;
        filepass = fopen("Private.txt","a");
        fprintf(filepass,"%s\n",inputpass);
        step++;
        fclose(filepass);
      }

      //Looks through file, finds the line that matches
      //user and compares
      else{
        fgets(inputpass,100,stdin);
        inputpass[strlen(inputpass)-1] = '\0';

        char * pass = (char*)malloc(100*sizeof(char));;
        FILE *filepass;
        size_t len = 0;
        filepass = fopen("Private.txt","r");
        int c = 0;

        for(;c < users;c++){
          getline(&pass,&len,filepass);
          strtok(pass, "\n");
          if(c == userid){
            if(strcmp(inputpass,pass) == 0){
              step++;
              printf("\nLogin success! \n \n");
            }
          }
        }
        fclose(filepass);
        free(pass);

      }
    }

    //Final step, lists out opponents and
    //their win/loss record
    if(step == 3){
      printf("Pick an opponent:\n");

      char * username = (char*)malloc(10000*sizeof(char));
      size_t len = 0;
      FILE *userfile;
      userfile = fopen("User.txt","r");

      int i = 0;
      for(;i< usertxt;i++){
        getline(&username,&len,userfile);
        strtok(username, "\n");
        printf("%s\n",username);
        i++;
        if(i % 3 == 0){
          printf("\n");
        }
        i--;
      }
      fclose(userfile);
      free(username);

      //Input does not allow you to choose yourself
      char * input = (char*)malloc(100*sizeof(char));
      fgets(input,100,stdin);
      input[strlen(input)-1] = '\0';

      char * line2 = (char*)malloc(100*sizeof(char));
      size_t len2 = 0;
      FILE *file2;
      file2 = fopen("Usernames.txt","r");
      int c = 0;
      for(;c< users;c++){
        getline(&line2,&len2,file2);
        strtok(line2, "\n");
        if(strcmp(input,line2) == 0){
          if(userid == c){
            printf("\nYou cant pick you\n \n");
          }

        }
      }
      fclose(file2);
      free(line2);

      if(strcmp(input,"end") == 0){
        loop--;
      }

      free(input);

    }


  }

}
