#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> //haven't used this here
//used to set file creation permission mask

int main(){

  //read(fd,buff,n)
  //reads n byte from fd's file and puts that data in the buffer
  //returns # of bytes which were read
  //buffer must be a pointer or address

  char line[256];
  int fd = open("temp_notes.txt",O_RDWR);
  int b = read(fd,line,256);
  printf("file descriptor: %d\n",fd);
  printf("read %d bytes: %s\n\n", b, line);

  strcpy(line,"test");
  b = write(fd,line,strlen(line));
  printf("file descriptor: %d\n",fd);
  printf("wrote %d bytes \n", b);
  
  b = read(fd,line,256);
  printf("read %d bytes: %s\n\n", b, line);

  close(fd);

  return 0;

}
