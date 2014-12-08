//shuffle() sometimes but rarely gets stuck in an almost-infinite loop ('almost' because it exits it as one second passes)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "music.h"
#include "music_library.h"

Node *table; 
//global variable
//each of the pointers begins with a blank Node, so all of the print functions begin with the second Node in the list; search and add functions work the same though, since a blank Node would never turn up in a search

int main(){
  //set up table
  table = (Node *)calloc(26, sizeof(Node));
  printf("Adding songs to table: \n");
  add_song("Andreas", "Andreas");
  add_song("Beta", "Andreas");
  add_song("c", "c");
  add_song("l", "l");
  add_song("m", "m");
  add_song("n", "n");
  add_song("o", "o");
  add_song("Liebestraum", "Liszt");
  add_song("p", "p");
  add_song("r", "r");
  add_song("w", "w");
  add_song("x", "x");
  add_song("z", "z");
  //searching tests
  printf("\n");
  print_table();
  printf("Searching for \"Andreas\" by Andreas: %p\n\n", 
	 search_song_table("Andreas", "Andreas"));
  printf("Searching for \"Andreas\" by Paul: %p\n\n", 
	 search_song_table("Andreas", "Paul"));
  printf("Searching for the artist Andreas: %p\n\n", 
	 search_artist_table("Andreas"));
  printf("Searching for the artist Paul: %p\n\n", 
	 search_artist_table("Paul"));
  //playlist test
  Node *playlist = shuffle(4);
  printf("Shuffled playlist: ");
  print_list(playlist);
  free_list(playlist);
  //printing tests
  printf("\nPrinting songs by the artist Andreas: ");
  print_artist("Andreas");
  printf("\nPrinting songs whose artists begin with the letter 'a': ");
  print_letter('A');
  //freeing/deleting tests
  delete_one_table("Andreas", "Andreas");
  printf("\nDeleted the song \"Andreas\" by Andreas.  Updated table: \n\n");
  print_table();
  free_table();
  printf("Table deleted.  Updated table: \n\n");
  print_table();
  //free table entirely (including the blank Nodes) before exiting
  free_list(table);
}

//TABLE FUNCTIONS
//note:
//ASCII 'A' = 65
//ASCII 'a' = 97
void add_song(char *name, char *artist){
  char i;
  for (i = 65; i < 91; i++) {
    if (*artist == i || *artist == i + 32) {
      insert(table + i - 65, name, artist);
    }
  }
}
Node * search_song_table(char *name, char *artist){
  Node *s;
  int i;
  for (i = 0; i < 26; i++) {
    if (s = search_song(table + i, name, artist)) {
      return s;
    }
  }
  return 0;
}
Node * search_artist_table(char *artist){
  Node *s;
  int i;
  for (i = 0; i < 26; i++) {
    if (s = search_artist(table + i, artist)) {
      return s;
    }
  }
  return 0;  
}
void print_letter(char a){
  print_list((table + a - 65)->next);
}
void print_artist(char *artist){
  Node *song = search_artist_table(artist);
  printf("[");
  if (song) {
    printf("\"%s\" by %s", song->name, song->artist);
    while(song->next && !strcmp(artist,song->artist)) {
      song = song->next;
      printf(", \"%s\" by %s", song->name, song->artist);
    }
  }
  printf("]\n");
}
void print_table(){
  int i=0;
  char f = 65;
  Node *p = table;
  for (i = 0; i < 26; i++) {
    printf("%c: ", f);
    print_list(table[i].next);
    //printf("\n");
    f++;
  }
}
Node * shuffle(int num_songs){
  Node *playlist=0;
  srand(time(NULL));
  int r = rand()%26;
  int prev = 0;
  int prev2 = 0;
  //printf("about to enter while loop\n");//comment out
  while(num_songs){
    Node *temp = random_song((table+r)->next);
    //loop will no longer return duplicates
    if(temp && temp->name && !search_song(playlist, temp->name, temp->artist)){
      playlist=insert(playlist,temp->name,temp->artist);
      num_songs--;
    }
    r = (time(NULL)+r+num_songs)%26;
    //this greatly lowers the chance that it will infinite loop
    if (r == prev) {
      r = (r+1) %26;
    }
    else if (r == prev2) {
      r = (r+1) %26;
    }
    prev2 = prev;
    prev = r;
    // printf("r: %d\n",r);//comment out
  }
  // printf("\n");//comment out
  return playlist;
}
void delete_one_table(char *name, char *artist){
  delete_one(table+ *artist -65,name,artist);
}
void free_table(){
  int i=0;
  //Leaving the first node in each letter unfreed to preserve the table
  for (i = 0; i < 26; i++) {
    table[i].next = free_list(table[i].next);
  } 
}
