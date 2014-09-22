#include <stdlib.h>

int strlen(char*);
int strcpy(char,char);
/* int strncpy(char,char); */
/* int strcat(char,char); */
/* itn strncat(char,char); */
/* int strcmp(char,char); */

int main(){

  printf("\n");

  printf("testing strlen: %d \n",strlen("testsfasdfasdfasd"));

  printf"testing strcpy: \n src: %s \n dest: %s \n",

  return 0;
}

//returns string length
int strlen(char *s){
  int i=0;
  while(s[i]){
    i++;
  }
  return i;
}

//copies string from src to location at dest
//returns pointer to dest
char strcpy(char *dest, char *src){
  int i=0;
  while(src[i]){
    dest[i]=src[i];
    i++;
  }
  return dest;
}
