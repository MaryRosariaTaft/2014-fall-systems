#include <stdio.h>
#include <stdlib.h>

//dynamically allocate 10-double array and 20-char array (string) (including terminating null)

int main(){

  int *p;
  p=(int *)malloc(10*sizeof(double));

  /*OR
    p=(int *)calloc(10,sizeof(double));
  */


  char *p1;
  p1=(char *)malloc(20*sizeof(char));
  p1[0]=0; //when this is printed as a string, it'll look like an empty string

  /*OR
p=(char *)calloc(20,sizeof(char));
//terminating null asignment is not necessary, since calloc ensures taht all bits are set to 0
   */

  //after the memory has been used, release it so other parts of your program or operating system can use it
  free(p);
  free(p1);

}
