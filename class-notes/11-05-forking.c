#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

  printf("pid before other_function: %d\n",getpid());
  int f=fork();
  printf("pid after other_function: %d\n",getpid());
  printf("f:%d\n",f);
  if(f){
    sleep(1);
    printf("parent's parent's PID: %d\n",getppid());
  }else{
    printf("child's parent's PID: %d\n",getppid());
  }
  printf("\n");

  return 0;

}
