#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){

  int socket_id;
  char buffer[256];
  int i, b;

  //create socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(24601); //port HAS TO BE the same as the server port
  inet_aton("149.89.150.1", &(sock.sin_addr)); //translate ip address to binary and put it inside our sock struct
  bind(socket_id, (struct sockaddr *)(&sock), sizeof(sock));

  //attempt a connection
  i = connect(socket_id, (struct sockaddr *)(&sock), sizeof(sock));
  printf("connect returned: %d\n", i);
  if(i==-1){
    printf("error: %s", strerror(errno));
  }

  //if i==0 then read() and write() work 

  return 0;

}
