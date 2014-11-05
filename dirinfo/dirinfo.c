#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "dirinfo.h"

int main(){

  // I can't even print out the problems I'm having because when I add or remove or change the print statements--even the ones without variables--I get a "symbol lookup error", specifically, "undefined symbol: putchar"
  // and as the code is, there's another symbol lookup error, "undefined symbol: closedir", which I don't understand, especially since I included <sys/types.h> and <dirent.h>
  // anyway, regarding total directory size:
  // I tried making a recursive function, and that failed (please see the comments above/within size())
  // and since it failed, I tried using a variable 'dir_size' inside of list_files(); and that failed, too
  // Life is generally frustrating.  My apologies.

  printf("\n");

  char path[256];
  getcwd(path,256);
  strcat(path,"/");

  list_files(path);

  //printf("size: %d \n",size(path));

  return 0;

}

void list_files(char *path){

  DIR *d; //directory stream
  d = opendir(path);
  struct dirent *info; //file information

  struct stat *stats; //more file information

  //set up path to be edited for each file
  char current_path[256];
  strcpy(current_path,path);
  int len = strlen(current_path);

  //int dir_size; //get rid of this after size() works

  printf("directory: %s \n",current_path);
  //printf("total size: %d \n",size(current_path));
  printf("files: \n");

  while (info = readdir(d)){
  
    //update stat buffer for each file
    strcpy(&current_path[len],info->d_name);
    stat(current_path,stats);

    printf("\t");
    printf("%o\t",stats->st_mode%(8*8*8)); //mod it so that the file type doesn't show
    printf("%d\t",(int)stats->st_size);
    /* if(info->d_type!=DT_DIR){ */
    /*   dir_size += (int)stats->st_size; */
    /* } */
    //once size() is working:
    //first get rid of the above 'if' statement
    //then write:
    //if the current file *is* a directory
    //strcat(current_path,"/");
    //then just print size(current_path), directory or not
    printf("%d\t",info->d_type);
    //oh joy, this causes an error, too:
    //printf("%s\t",ctime(stats->st_mtime));
    printf("%s\t",info->d_name);
    printf("\n");
  }

  //don't know why this print statement isn't working
  //printf("total size (not including subdirectories): %d",dir_size);

  closedir(d);

}


//cannot figure out why stat() won't work with given path
//therefore also have not tested the recursion

/*

int size(char *path){

  int total_size=0;

  DIR *d;
  d = opendir(path);
  struct dirent *info;

  struct stat *stats;

  char current_path[256];
  strcpy(current_path,path);
  int len = strlen(current_path);

  while (info = readdir(d)){
  
    strcpy(&current_path[len],info->d_name);
    stat(current_path,stats);
    printf("path: %s\n",current_path);
    printf("%s\n\n",strerror(errno));

     if(info->d_type==DT_DIR){
      //if the file is a directory, strcat(current_path,"/")
      //then: total_size += size(current_path);
    }else{
      //total_size += (int)stats->st_size;
    }

  }

  closedir(d);

  return total_size;
  
}

*/
