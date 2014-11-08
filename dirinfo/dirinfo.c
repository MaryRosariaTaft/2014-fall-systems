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

  printf("\n");

  char path[256];
  getcwd(path,256);
  strcat(path,"/");

  //list_files(path);

  printf("size (including subdirectories): %d\n\n", fsize(path));

  return 0;

}

void list_files(char *path){

  DIR *d; //directory stream
  d = opendir(path);
  struct dirent *info; //file information

  struct stat stats; //more file information

  //set up path to be edited for each file
  char current_path[256];
  strcpy(current_path,path);
  int len = strlen(current_path);

  printf("directory: %s \n",current_path);
  printf("files: \n");

  while (info = readdir(d)){
  
    //update stat buffer for each file
    strcpy(&current_path[len],info->d_name);
    stat(current_path,&stats);

    printf("\t");
    printf("%o\t",stats.st_mode%(8*8*8)); //mod it so that the file type doesn't show
    printf("%d\t",(int)stats.st_size);
    printf("%d\t",info->d_type);
    printf("%s\t",info->d_name);
    printf("\n");
  }

  closedir(d);

}

//precon: path has to be a directory path ending in a forward slash
int fsize(char *path){

  printf("path: %s\n",path);

  DIR *d;
  d = opendir(path);
  struct dirent *info;

  struct stat stats;

  char current_path[256];
  strcpy(current_path,path);
  int len = strlen(current_path);

  int size=0;

  while (info = readdir(d)){
  
    strcpy(&current_path[len],info->d_name);
    stat(current_path,&stats);

    printf("\tsubpath: %s\n",current_path);
    printf("\tfilename: %s",info->d_name);
    printf("\tfiletype: %d\n",info->d_type);

    if(info->d_type!=DT_DIR){ //not a directory
      printf("\t\tinside if\n");
      size += (int)stats.st_size;
    }
    if(info->d_type==DT_DIR){
      printf("\t\tinside elseif\n");
      if(!strcmp(info->d_name,"..") || !strcmp(info->d_name,".")){
	printf("\t\tspecial cond\n");
      }else{
	printf("\t\tspecial else\n");
	strcat(current_path,"/");
	size += fsize(current_path);
      }
      //size += fsize(current_path);
    }
    
  }

  closedir(d);

  return size;

}
