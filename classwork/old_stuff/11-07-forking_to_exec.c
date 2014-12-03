#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  printf("before executing\n");

  int f = fork();

  if(!f){
    execl("/bin/ls","ls","-a","-l",NULL); //child
  }else{
    //parent
  }

  printf("after executing\n");

}
