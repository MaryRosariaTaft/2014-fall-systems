/*

  - runs constantly unless given a signal not defined below (infinite loop)
  - intercepts the signals:
  SIGUSR1 --> results in the program appending the output of the "who" command to a file
  SIGUSR2 --> results in the program appending the output of the "ps" command to a different file
  SIGINT (keyboard interrupt) --> displays the contents of both files, then quits
  - note: execl takes over the program from which it's run; fork a subprocess to run "who" and "ps"

  - could/should be improved by using "which" or "whereis" to find paths for "who" and "ps" instead of writing out the path (in case of OS variations and such) (and I already wrote a "find()" function for that in the executor assignment, so that could probably be implemented here)

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static void sighandler(int signo){

  int f=0;
  
  int fd1;
  int fd2;
  
  if(signo==SIGUSR1){ //type: kill -s SIGUSR1 (pid)
    //printf("1\n");
    f=fork();
    fd2=dup(STDOUT_FILENO);
    if(!f){
      //printf("whochild %d\n",getpid());
      fd1=open("who.txt", O_CREAT | O_APPEND | O_RDWR);
      dup2(fd1,STDOUT_FILENO);
      execl("/usr/bin/who","who",NULL);
      //close(fd1); is not necessary (actually, it's useless, because execl() stops everything after it from being run
    }
    dup2(fd2,STDOUT_FILENO);
    close(fd2);
    f=0; //I believe this should not be necessary, but it certainly doesn't hurt
    //for testing //exit(-1);
  }else if(signo==SIGUSR2){ //type: kill -s SIGUSR2 (pid)
    //printf("2\n");
    f=fork();
    fd2=dup(STDOUT_FILENO);
    if(!f){
      //printf("pschild %d\n",getpid());
      fd1=open("ps.txt", O_CREAT | O_APPEND | O_RDWR);
      dup2(fd1,STDOUT_FILENO);
      execl("/bin/ps","ps",NULL);
    }
    dup2(fd2,STDOUT_FILENO);
    close(fd2);
    f=0;
    //for testing //exit(-1);
  }else if(signo==SIGINT){ //SIGINT==keyboard interrupt (Ctrl+C)
    //printf("key\n");
    fd1=open("who.txt",O_RDONLY);
    fd2=open("ps.txt",O_RDONLY);
    f=fork();
    if(!f){
      printf("\nwho:\n");
      execl("/bin/cat","cat","who.txt",NULL);
    }
    sleep(1);
    f=fork();
    if(!f){
      printf("\nps:\n");
      execl("/bin/cat","cat","ps.txt",NULL);
    }
    close(fd1);
    close(fd2);
    sleep(1);
    exit(-1);
  }

}


int main(){

  signal(SIGUSR1,sighandler);
  signal(SIGUSR2,sighandler);
  signal(SIGINT,sighandler);

  printf("%d\n",getpid());  
  
  while(1){
    sleep(1);
  }

  return 0;
  
}
