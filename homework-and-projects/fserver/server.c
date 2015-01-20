#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void connect(int *from_client, int *to_client, int client_num);
void process(int from_client, int to_client, int client_num);

void sighandler(int signo){

  remove("ralph");
  exit(0);

}

int main(){

  signal(SIGINT, sighandler);

  printf("server\n\n");

  printf("PROBLEMS:\n no notification when a client exits via keyboard interrupt\n no way to close server from client\n and the only way to close the server from the shell running it is to use the keyboard interrupt\n\n");

  int from_client;
  int to_client;
  int client_num = 0;

  while(1){
    connect(&from_client, &to_client, client_num);
    client_num++;
  }

}


void connect(int *from_client, int *to_client, int client_num){

  char line[256];
  int i;

  //make WKP, open for listening
  mkfifo("ralph", 0664);
  *from_client = open("ralph", O_RDONLY);
  if(*from_client == -1){
    printf("<server> error opening WKP: %s\n", strerror(errno));
    exit(-1);
  }else{
    printf("<server> opened WKP\n");
  }

  //read message from client containing pipe name
  i = read(*from_client, line, sizeof(line));
  if(i == -1){
    printf("<server> error reading from client: %s\n", strerror(errno));
    close(*from_client);
    exit(-1);
  }else{
    printf("<server> client's pipe name: %s\n", line);
  }
  remove("ralph"); //the client takes care of removing its pipe

  //connect to client
  *to_client = open(line, O_WRONLY);
  if(*to_client == -1){
    printf("<server> error connecting to client: %s\n", strerror(errno));
    close(*from_client);
    close(*to_client);
    exit(-1);
  }else{
    printf("<server> connected to client\n");
  }

  //send confirmation message to client
  i = write(*to_client, "hamana-hamana-hamana-hamana", 29);
  if(i == -1){
    printf("<server> error writing to client: %s\n", strerror(errno));
    close(*from_client);
    close(*to_client);
    exit(-1);
  }else{
    printf("<server> sent confirmation message\n");
  }

  //fork off subserver via child process
  int f = fork();
  if(f){
    close(*from_client);
    close(*to_client);
    printf("<server> forking off subserver to handle client %d\n", client_num);
    //now connect() will run again, since it's being called in a while-loop in main()
  }else{
    process(*from_client, *to_client, client_num);
  } 

}


void process(int from_client, int to_client, int client_num){

  char line[256];
  int i = 0, j = 0;
  int count = 0;

  //checks for errors reading/writing
  while(i != -1 && j != -1){

    //read client's message
    i = read(from_client, line, sizeof(line));
    if(i == -1){
      printf("<server> error reading from client: %s\n", strerror(errno));
      close(from_client);
      close(to_client);
      exit(-1);
    }
    printf("<server> (client %d, line %d) read +%s+\n", client_num, count, line);

    if(!strncmp(line, "exit", 4)){
      printf("<server> closing connection with client %d\n", client_num);
      write(to_client, "EXITING", 7);
      exit(0);
    }
    if(!strncmp(line, "the redcoats are coming", 23)){
      printf("-- NOOOO --\n");
      printf("<server> (client %d) closing connection with client %d\n", client_num, client_num);
      write(to_client, "DANGER\0", 7);
      exit(0);
    }

    //remove the last character, then send it back
    line[strlen(line) - 1] = '\0';
    j = write(to_client, line, sizeof(line));
    if(j == -1){
      printf("<server> error writing to client: %s\n", strerror(errno));
      close(from_client);
      close(to_client);
      exit(-1);
    }
    printf("<server> (client %d, line %d) wrote +%s+\n", client_num, count, line);
    
    count++;
  }

}
