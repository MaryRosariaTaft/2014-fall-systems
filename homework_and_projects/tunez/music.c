#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "music.h"

/* int main() { */
/*   Node *h = 0; */
/*   h=insert(h,"1","aa"); */
/*   h=insert(h,"1","ab"); */
/*   h=insert(h,"1","ac"); */
/*   h=insert(h,"1","ad"); */
/*   h=insert(h,"2","ad"); */
/*   print_list(h); */
/*   printf("%p\n", search_song(h, "1", "aa")); */
/*   printf("%p\n", search_artist(h, "ab")); */
/*   h = delete_one(h, "1", "ab"); */
/*   print_list(h); */
/*   printf("%p\n", search_artist(h, "ab")); */
/*   printf("%s\n", random_song(h)->name); */
/*   free_list(h); */
/*   h=0; */
/*   printf("%d\n",length(h)); */
/*   printf("%lu\n",random_song(h)); */
/* } */

//LINKED LIST FUNCTIONS
void print_list(Node *h) {
  printf("[");
  if (h) {
    printf("\"%s\" by %s", h->name, h->artist);
    while(h->next) {
      h = h->next;
      printf(", \"%s\" by %s", h->name, h->artist);
    }
  }
  printf("]\n");
}
int compareTo(Node *first, Node *second){
  //a null pointer is larger than everything else
  //since the null pointer indicates the end of the list
  if (!first) {
    return 1;
  }
  else if (!second) {
    return -1;
  }
  else if (!strcmp(first->artist, second->artist)){
    return strcmp(first->name, second->name);
  }
  else {
    return strcmp(first->artist,second->artist);
  }
}
Node * insert_front(Node *h, char *name, char *artist){
  Node *z = (Node *) malloc(sizeof(Node));
  strcpy(z->name, name);
  strcpy(z->artist, artist);
  z->next = h;
  return z;
}
Node * insert(Node *h, char *name, char *artist) {
  Node *head = h;
  Node *z = (Node *) malloc(sizeof(Node));
  strcpy(z->name, name);
  strcpy(z->artist, artist);
  if (compareTo(z, h) < 0) {
    free(z);
    return insert_front(h,name,artist);
  }
  else {
    while (compareTo(z, h->next) >= 0){
      h = h->next;
    }
    Node *temp=h->next;
    h->next = z;
    z->next=temp;
    return head;
  }
}
Node * free_list(Node *h){
  Node *tmp;
  while(h) {
    tmp = h->next;
    //printf("Freeing node: %d\n", h->x);
    free(h);
    h = tmp;
  }
  return h;
}
Node * search_song(Node *h, char *name, char *artist){
  Node s;
  strcpy(s.name, name);
  strcpy(s.artist, artist);
  Node *g = &s;
  while (h) {
    if (!compareTo(g, h)) {
      return h;
    }
    h = h->next;
  }
  return 0;
}
Node * search_artist(Node *h, char *artist){
  while (h) {
    if (!strcmp(artist,h->artist)) {
      return h;
    }
    h = h->next;
  }
  return 0;
}
Node * delete_one(Node *h, char *name, char *artist) {
  Node s;
  strcpy(s.name, name);
  strcpy(s.artist, artist);
  Node *g = &s;
  if(!h){
    return 0;
  }
  else if (!compareTo(g, h)){
    Node *out = h->next;
    free(h);
    return out;
  }
  else {
    Node *head = h;
    while (h->next) {
      if (!compareTo(g,h->next)){
	h->next = h->next->next;
	return head;
      }

    }
    return head;
  }
}
int length(Node *h){
  int i=0;
  while(h){
    i++;
    h=h->next;
  }
  return i;
}
Node * random_song(Node *h){
  if(!length(h)){
    return 0;
  }
  srand(time(NULL));
  int r = rand() % length(h);
  while(r){
    h=h->next;
    r--;
  }
  return h;
}
