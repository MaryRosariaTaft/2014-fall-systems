#include <stdlib.h>
#include <stdio.h>

//initialize and then find the length of a string

int main(){
  char string[/*6*/]="hello";
  int i;
  /* string[0]='h'; */
  /* string[1]='e'; */
  /* string[2]='l'; */
  /* string[3]='l'; */
  /* string[4]='o'; */
  /* string[5]=0; */
  char *pstring=string;
  int length=0;
  while(1){
    if(*pstring!=0){
      length++;
      pstring++;//moves one byte (char) at a time
    }else{
      printf("String length, not including terminating null: %d \n",length);
      return length;
    }
  }

  /*

//or just do:

int i=0;
while(s[i]){//s[i] is false if s[i]==0
i++;
}
printf("%d",s);

   */
}
