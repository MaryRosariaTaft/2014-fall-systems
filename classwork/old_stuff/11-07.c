#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

  printf("before executing\n");

  int f = fork();

  if(!f){
    execl("/bin/ls","ls","-a","-l",NULL);
  }else{

  }

  printf("after executing\n");

}
