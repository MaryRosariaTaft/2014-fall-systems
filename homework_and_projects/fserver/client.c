#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void connect(int *to_server, int *from_server);
void process(int to_server, int from_server);

void sighandler(int signo){

  exit(0);

}

int main(){

  signal(SIGINT, sighandler);

  printf("client\n\n");

  int to_server;
  int from_server;
  
  connect(&to_server, &from_server);

}


void connect(int *to_server, int *from_server){

  char line[64]; //a.k.a. listening-pipe/getpid()/etc.
  char confirmation[64];
  int i;

  //make listening-pipe
  sprintf(line, "%d", getpid());
  mkfifo(line, 0644);

  //connect to server
  *to_server = open("ralph", O_WRONLY);
  if(*to_server == -1){
    printf("<client> error connecting to server: %s\n", strerror(errno));
    remove(line);
    exit(-1);
  }else{
    printf("<client> connected to server\n");
  }

  //write listening-pipe name to server
  i = write(*to_server, line, sizeof(line));
  if(i == -1){
    printf("<client> error writing to server: %s\n", strerror(errno));
    remove(line);
    exit(-1);
  }else{
    printf("<client> wrote pipe name: %s\n", line);
  }

  //ISSUE IN THE FOLLOWING LINES OF CODE:
  //have to remove listening-pipe if there's an open or read error
  //not currently implemented

  //open listening-pipe for (guess what) listening
  *from_server = open(line, O_RDONLY);
  if(*from_server == -1){
    printf("<client> error opening pipe for listening: %s\n", strerror(errno));
    exit(-1);
  }else{
    printf("<client> opened for listening\n");
  }

  //read confirmation message from server
  i = read(*from_server, confirmation, sizeof(confirmation));
  if(i == -1){
    printf("<client> error reading from server: %s\n", strerror(errno));
    exit(-1);
  }else{
    printf("<client> received confirmation message: %s\n", confirmation);
  }
  remove(line); //the server takes care of removing its WKP

  printf("\n-- TO EXIT, TYPE: -- \n exit\n- or -\n the redcoats are coming\n\n");

  while(1){
    process(*to_server, *from_server);
  }

}


void process(int to_server, int from_server){

    char line[256];
    int i;

    //get user input
    printf("\tEnter text: ");
    fgets(line, sizeof(line), stdin);
    *strchr(line, '\n') = '\0';

    //send user input to server
    i = write(to_server, line, sizeof(line));
    if(i == -1){
      printf("<client> error writing to server: %s\n", strerror(errno));
      exit(-1);
    }else{
      printf("<client> wrote +%s+\n", line);
    }

    //read response from server
    i = read(from_server, line, sizeof(line));
    if(i == -1){
      printf("<client> error reading from server: %s\n", strerror(errno));
      exit(-1);
    }else{
      printf("<client> received +%s+\n", line);
      //keyword-exit after receiving acknowledgement from server
      if(!strcmp(line, "EXITING")){
	printf("-- Goodbye! --\n");
	close(to_server);
	close(from_server);
	exit(0);
      }
      if(!strcmp(line, "DANGER")){
	printf("-- fare thee well --\n");
	close(to_server);
	close(from_server);
	exit(0);
      }
    }

}
