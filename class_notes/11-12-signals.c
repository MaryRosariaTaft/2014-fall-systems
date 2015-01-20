/*
IPC - inter-process communication
signals:
- an int sent from one process to another
- int will correspond to a preset signal
kill
- command line program to send a signal
- syntax: kill -<SIGNO> <PID>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sighandler(int signo){

  //signal sent is parameter input
  //static functions in C: isolated to the file that it's defined in (this function only exists in 11-12.c; cannot be linked to another file; wouldnt' be accessible in another file; etc.)

  //anything written outside of the if statements will only be called if sighandler() is signaled

  if(signo==SIGINT){ //SIGINT: keyboard interrupt (Ctrl+C)
    printf("ha?\n");
  }else if(signo==SIGQUIT){
    printf("will die now\n");
    exit(-1);
  }

}

int main(){

  /* signal(SIGINT,sighandler); */
  /* signal(SIGQUIT,sighandler); */
  //if the above were not here included, interrupt and quit signals would be handled by the default signal handler rather than by the sighandler() written above

  int i=0;

  while(1){
    printf("Giorno\tnum: %d\tpid: %d",i++,getpid());
    sleep(1);
  }

  return 0;

}
