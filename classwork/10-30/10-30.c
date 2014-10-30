#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

  int x=5;
  int y=-1;

  char string[100]; //char *string doesn't work --> a memory chunk hasn't yet been allocated for the characters

  sprintf(string, "The point (x,y) is (%d,%d).", x, y);

  printf("%s\n",string);

  /* printf("Enter stuff\t"); */
  /* fgets(string, sizeof(string)-1,stdin); //the "-1" is so that there's a terminating null allowance; will wait for terminal input because it takes "stdin" */
  /* printf("%s",string); */

  char *s1, *s2;

  strcpy(string,"replacing\tthe\told\tstring\twith\tnew\tstuff");

  printf("string: %s\n",string);

  s1 = string;

  s2 = strsep(&s1,"\t");

  printf("s1: %s\n",s1);
  printf("s2: %s\n",s2);

  return 0;

}

/*
  fgets(<DESTINATION>,<BYTES>,<FILE POINTER>) in <stdio.h>
  fgets(s,n,f); --> reads at most n characters from file stream f (including newlines from terminal input!) and stores it in s and WILL include a terminating null

  files pointers (FILE *)--> NOT file descriptors; more like directory streams (DIR *)
  stdin is a FILE * variable

  strsep(<STRING>,<DELIMITER>) in <string.h>
  used for parsing a string with a common delimiter
  locates the first occurrence of the delimiter in a string and replaces it with NULL
  returns the beginning of the original string set a parameter to a string started at 1 index past the location of the new null

*/
