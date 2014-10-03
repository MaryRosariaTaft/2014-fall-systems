#include <stdlib.h>
#include <stdio.h>

int main(){
  int i;
  double d;
  char c;
  int a[5];
  int *pi;
  double *pd;
  char *pc;
  //the following creates a pointer to the whole chunk of a
  int (*pa)[5];
  //if it were declared int *pa and initialized pa=&a, pa will only refer to the 1st int int a (4 bytes)

  //assign pointers to locations of variables:
  pi=&i;
  pd=&d;
  pc=&c;
  pa=&a;
  printf("Pointers' memory addresses \n");
  printf("int: %lu \n",pi);
  printf("double: %lu \n",pd);
  printf("char: %lu \n",pc);
  printf("array: %lu \n",pa);
  pi++;
  pd++;
  pc++;
  pa++;
  printf("\n");
  printf("Pointers' memory addresses after adding 1 to each \n");
  printf("int: %lu \n",pi);
  printf("double: %lu \n",pd);
  printf("char: %lu \n",pc);
  printf("array: %lu",pa);

  printf("\n");

}
