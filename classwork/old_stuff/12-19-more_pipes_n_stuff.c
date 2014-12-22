#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void process(char *s);

//consider putting all the connection stuff into a separate function

int main(){

  int from_server;
  int to_server;
  char line[100];

  sprintf(line, "%d", getpid());
  mkfifo(line, 0664);

  to_server = open("mario", O_WRONLY);
  write(to_server, line, sizeof(line));

  *from_server = open(line, O_RDONLY);
  read(*from_server, line, sizeof(line));
  printf("<client> receiver +%s+\n",line);

  return to_server;

}

/*
//implementing the suggestion above main():

//declare stuff

to_server = handshake(&from_server)

while(1)
 fgets(line,sizeof(line),stdin)
 *strchr(\n) or line[strlen-1] to get rid of the newline and replace it with a terminating null
  and make sure to do error checkin'
 write(to_server)
 read(from_server)

close(to_server)
close(to_client)
 */

void process(char *s){

  while(*s){
    *s = (*s-'a'+13)%26+'a';
    //well that kind of assumes a lot
    s++;
  }

}

//make sure to remove the client pipe after the connections are set up
//signal handler + keyword exit to close the connection
//otherwise you have a program which needs keyboard interrupt to quit and you have a bunch of pipes hangin' around all over the place

//hey! great reminder, you can't cast ints to strings
//joy
//it's Friday

