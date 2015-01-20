#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(){

  struct stat sb; //stat buffer
  /*
    stat contains the following:
    st_size //size of the file
    st_uid //user I.D.
    st_gid //group I.D.
    st_mode //file permissions
    st_atime //last access
    st_mtime //last modification
    //note - touching counts not only as access but as modification
    and more!
  */

  stat("data.txt",&sb);

  printf("File size: %lu \n", sb.st_size);

  printf("Mode: %o \n", sb.st_mode); //%o for octal number output

  printf("Last access time: %s \n", ctime(&(sb.st_atime))); //ctime() is in time.h



}
