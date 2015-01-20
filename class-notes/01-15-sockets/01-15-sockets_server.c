#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

char *process(char *s);

int main(int argc, char **argv){

  int socket_id, socket_client;
  char buffer[256];
  int i, b;

  //create socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port = htons(24601); //because why not
  listener.sin_addr.s_addr = INADDR_ANY; //incoming address, any
     //sin_addr is a struct in and of itself
  bind(socket_id, (struct sockaddr *)(&listener), sizeof(listener));

  listen(socket_id, 1);
  printf("listening\n");

  socket_client = accept(socket_id, NULL, NULL);
  //socket_client is new the new socket descriptor

  //have to close sockets somehwere sometime after doing stuff and while loops and such

  return 0;

}

char *process(char *s){

}
