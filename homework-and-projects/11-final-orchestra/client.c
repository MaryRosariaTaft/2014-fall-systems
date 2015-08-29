#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

//supposedly we're not supposed to have global variables in C
//but it works and there's also a section of a Wikipedia page about it so
static int socket_id;
typedef struct temp_name{
  char ch;
  int i;
} note;
static note n;

void sighandler(int signo){

  n.ch = 'z';
  write(socket_id, &n, sizeof(n));
  exit(0);

}

int main(int argc, char **argv){

  signal(SIGINT, sighandler);

  //create socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(24601); //same as the server port
  inet_aton("127.0.0.1", &(sock.sin_addr)); //translates ip address to binary and puts it inside the sock struct
  bind(socket_id, (struct sockaddr *)(&sock), sizeof(sock));

  note n;
  n.ch = '\0';
  n.i = 0; 

  //attempt connection
  int error_check;
  error_check = connect(socket_id, (struct sockaddr*)(&sock), sizeof(sock));
  printf("connect returned: %d\n", error_check);
  if(error_check==-1){
    printf("error: %s\n", strerror(errno));
    exit(-1);
  }
  
  //select and set instrument
  printf("What instrument would you like to play? Press key corresponding to your choice\n x - Violin\n c - Cello\n v - Clarinet\n b - Flute\n n - Trumpet\n m - Piano\n");
  read(STDIN_FILENO, &n.ch, 1);
  if (n.ch == 'x'){n.i = 0;}
  else if (n.ch == 'c'){n.i = 1;}
  else if (n.ch == 'v'){n.i = 2;}
  else if (n.ch == 'b'){n.i = 3;}
  else if (n.ch == 'n'){n.i = 4;}
  else if (n.ch == 'm'){n.i = 5;}

  //proceed to key-pressing magic
  struct termios info;
  tcgetattr(0, &info);          
  info.c_lflag &= ~ICANON;      
  info.c_cc[VMIN] = 1;          
  info.c_cc[VTIME] = 0;         
  tcsetattr(0, TCSANOW, &info);

  printf("Start pressing keys!\n");
  while(read(STDIN_FILENO, &n.ch, 1)){
    if (n.ch == 'z'){
      write(socket_id, &n, sizeof(n));
      break;
    }
    else if (n.ch == 'x'){n.i = 0;}
    else if (n.ch == 'c'){n.i = 1;}
    else if (n.ch == 'v'){n.i = 2;}
    else if (n.ch == 'b'){n.i = 3;}
    else if (n.ch == 'n'){n.i = 4;}
    else if (n.ch == 'm'){n.i = 5;}
    else{
      //write key-press input to the [sub]server
      write(socket_id, &n, sizeof(n));
      /* printf("[%c,%d]\n",n.ch,n.i); */
    }	
  }

  printf("Exiting.\n");

  return 0;

}

