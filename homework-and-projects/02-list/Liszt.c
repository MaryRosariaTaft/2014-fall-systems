#include <stdio.h>
#include <stdlib.h>


typedef struct temp{
  char data;
  struct temp *next;
} node;

int print_list(node *);
node *insert_front(node *,char );
node *insert_after(node *,char);
node *free_list(node *);

int main(){

  printf("\n");
  
  node *head=0;

  head=insert_front(head,'c');
  head=insert_front(head,'b');
  head=insert_front(head,'a');

  print_list(head);

  printf("\n\n");

  head=free_list(head);//which is null

  printf("\n");

  return 0;

}

int print_list(node *n){
  printf("[");
  while(n->next){
    printf("%c",n->data);
    n=n->next;
  }
  printf("%c",n->data);
  printf("]");
  return 0;
}

node *insert_front(node *head, char c){
  node *new_node;
  new_node=(node *)malloc(sizeof(node));
  new_node->data=c;
  new_node->next=head;
  return new_node;
}

//test if this works
node *insert_after(node *n, char c){
  node *new_node;
  new_node=(node *)malloc(sizeof(node));
  new_node->data=c;
  node *temp=n->next;
  new_node->next=temp;
  n->next=new_node;
  return new_node;
}

//can be written recursively
node *free_list(node *head){
  node *temp;
  while(head){
    temp=head;
    head=head->next;
    printf("freeing: %c \n",temp->data);
    free(temp);
  }
  return head;
}
