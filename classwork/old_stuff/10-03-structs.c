#include <stdio.h>
#include <stdlib.h>

typedef struct temp_name{
  int i;
  temp_name* p;
  //can't call the above pointer "node" type until "node" has been made; therefore give it a name in the above declaration
} node;

int main(){

  node a, b;

  a.i=44;
  a.p=&b;

  b.i=70;
  b.p=0;
  //above assignment: sets the value inside b.p to 0
  //that will be read as a "null pointer" and not a reference to memory address 0
  //(or if it does, it'll just register as "null" anyway)
  //(ah I'll work that out later)

  //each node has a value and a pointer to another node

}
