#include <stdio.h>
#include <stdlib.h>

//node->element returns the value inside element
//same as (*node).element

typedef struct temp{
  char data;
  struct temp *next;
} node;

int print_list(node *);
node *make_terminating_node(char);
node *make_node(char, node *);
node *insert_front(node *,node);
node *free_list(node *);

int main(){

  printf("\n");

  node a,b,c;

  printf("Testing node initialization and print_list: \n");

  a=*make_node('a',&b);
  b=*make_node('b',&c);
  c=*make_terminating_node('c');
  printf("Data in a: %c",a.data);
  printf("\n");
  printf("Linked list beginning with a: ");
  print_list(&a);

  printf("\n\n");


  node x,y,z;

  printf("Testing insert_front: \n");

  z=*insert_front(&a,*make_terminating_node('z'));

  printf("Linked list beginning with z: ");
  print_list(&z);
  printf("\n");

  y=*insert_front(&z,*make_terminating_node('y'));

  printf("Linked list beginning with y: ");
  print_list(&y);
  printf("\n");

  x=*insert_front(&y,*make_terminating_node('x'));

  printf("Linked list beginning with x: ");
  print_list(&x);
  printf("\n");

  printf("\n");

  printf("--re: free_list-- \n--I suppose I did something wrong.  Probably in allocating memory in the first place (in my make_node function, which I now doubt is even necessary).  Temporarily, please enjoy the following error.-- \n\n");

  free_list(&x);

  printf("\n");

}

int print_list(node *list_element){
  printf("[");
  while(list_element->next){
    printf("%c", list_element->data);
    list_element=list_element->next;
  }
  printf("%c",list_element->data);
  printf("]");
  return 0;
}

node *make_node(char d, node *n){
  node *new_node;
  new_node=(node *)malloc(sizeof(char)+sizeof(void *));
  new_node->data=d;
  new_node->next=n;
  return new_node;
}

node *make_terminating_node(char d){
  return make_node(d,0);
}

node *insert_front(node *first_element, node new_element){
  return make_node(new_element.data, first_element);
}

node *free_list(node *list_element){
  node *start=list_element;
  /* printf("Freeing list beginning with %c: \n",list_element->data); */

  //what I actually wanted to write (fails)
  /* while(list_element->next){ */
  /*   node *temp=list_element->next; */
  /*   printf("%c\n",list_element->data); */
  /*   free(list_element); */
  /*   list_element=temp; */
  /* } */
  /* printf("%c\n",list_element->data); */
  /* free(list_element); */
  /* printf("Freed!"); */

  //test to see if anything works at all (still fails)
  while(list_element->next){
    free(list_element);
  }

  return start;
}
