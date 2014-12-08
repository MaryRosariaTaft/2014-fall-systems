typedef struct n{
  char name[256];
  char artist[256];
  struct n *next;
} Node;

//LINKED LIST FUNCTIONS
void print_list(Node *h);
int compareTo(Node *first, Node *second);
Node * insert_front(Node *h, char *name, char *artist);
Node * insert(Node *head, char *name, char *artist);
Node * free_list(Node *h);
Node * search_song(Node *h, char *name, char *artist);
Node * search_artist(Node *h, char *artist);
Node * delete_one(Node *h, char *name, char *artist);
int length(Node *h);
Node * random_song(Node *h);
