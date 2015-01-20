#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

char *find(char *target, char *buffer);

int main(){

  char command[256];
  char *args_pointer = command;

  printf("We've been waiting for you.\n");
  fgets(command,sizeof(command),stdin);
  //"stdin" is going to register the newline character as a part of the string in addition to being an indicator of completed input, so I'll get rid of the newline here:
  command[strlen(command)-1]='\0';

  //printf("array before strsep: %s\n",args);
  //printf("pointer before strsep: %s\n",args_pointer);

  strsep(&args_pointer," ");

  //printf("array after strsep: %s\n",args); //points to first command
  //printf("pointer after strsep: %s\n",args_pointer); //points to the first flag (if there is one)

    char path[256];

  if(!args_pointer){

    execl(find(command,path),command,NULL);

  }else{

    //make array of 
    char *args[5];
    int i=0;
    while(args_pointer && i<6){
      args[i]=args_pointer;
      /* printf("ARG %d: %s\n",i,args_pointer); */
      strsep(&args_pointer," ");
      i++;
    }
    
    //call exec accordingly
    if(i==1){
      /* printf("path: %s\n",find(command,path)); */
      /* printf("command: %s\n",command); */
      /* printf("arg 0: %s\n",args[0]); */
      execl(find(command,path),command,args[0],NULL);
    }else if(i==2){
      execl(find(command,path),command,args[0],args[1],NULL);
    }else if(i==3){
      execl(find(command,path),command,args[0],args[1],args[2],NULL);
    }else if(i==4){
      execl(find(command,path),command,args[0],args[1],args[2],args[3],NULL);
    }else if(i==5){
      execl(find(command,path),command,args[0],args[1],args[2],args[3],args[4],NULL);
    }else{
      printf("too many arguments, aborting\n");
    }
  
  }

}

char *find(char *target, char *buffer){

  //lazy way of allocating space:
  char which[] = "which        ";

  //insert the desired command
  strcpy(&which[6],target);

  //then run it through the terminal and keep a copy of the result
  FILE *fp = popen(which,"r");
  fgets(which,sizeof(which),fp);
  pclose(fp);

  //set target to the new "which... " statement
  strcpy(buffer,which);

  //get rid of newline
  buffer[strlen(buffer)-1]='\0';

  /* printf("TARGET (ARGS): %s\n",target); */
  /* printf("BUFFER (PATH): %s\n",buffer); */

  return buffer;

}
