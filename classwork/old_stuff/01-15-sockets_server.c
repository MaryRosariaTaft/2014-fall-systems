#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

char *process(char *s);

int main(int argc, char **argv){

  int socket_id;
  char buffer[256];
  int i, b;

  //create socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //

  return 0;

}

char *process(char *s){

}
