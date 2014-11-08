#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

  printf("pid before fork: %d\n",getpid());
  //only one statement is printed to the terminal
  fork();
  printf("pid after 1st fork: %d\n",getpid());
  //two print statements result, because the parent or child runs [the latter] printf() and then the other one runs printf()
  //(parent/child order depends on OS)
  fork();
  printf("pid after 2nd fork: %d\n",getpid());
  //fun stuff

  return 0;

}

/*
fork() <unistd.h>
creates a separate process based on the current one, called the child, identical to the parent, but by COPYING, not using the same references as the parent
--> not always recursive / expoenential growth
--> child's PID is not the same as the parent's

different from threads
threads: cannot exist w/o a parent
--> as opposed to forked children, threads don't have their own stacks and heaps; in other words, threads use the data of their parents

"process" and "thread" are not interchangeable

forked processes can stand alone and exist without their parents
 */
