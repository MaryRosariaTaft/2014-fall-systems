#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef struct{
  char* name;
  int year;
} composer;

void print_composer(composer c){
  printf("\n");
  printf("Name: %s \n",c.name);
  printf("Year of Birth: %d \n",c.year);
}

int main(){

  //write 10 instances of struct to a file
  //then read them and print them
  //ask user to enter number of an entry (terminal input), then print that entry out (e.g. '2' --> print out 2nd struct)
  //ask user to enter # again, but this time: (a) modify that entry [arbitrarily] then (b) print out the *whole* file

  int fd; //file descriptor
  int b; //# of bytes read/written
  composer list[10]; //buffer
  int i=0; //counter for loops
  int input;

  fd = open("test",O_RDWR);

  //CLEAR CONTENTS OF TEST.TXT

  /* b = read(fd, list, 10*sizeof(composer)); */
  /* printf("file descriptor: %d \n", fd); */
  /* printf("# of bytes read: %d \n", b); */

  list[0].name="Liszt";
  list[0].year=1811;
  list[1].name="Chopin";
  list[1].year=1810;
  list[2].name="Rachmaninoff";
  list[2].year=1837;
  list[3].name="Bach";
  list[3].year=1685;
  list[4].name="Beethoven";
  list[4].year=1770;
  list[5].name="Brahms";
  list[5].year=1833;
  list[6].name="Mendelssohn";
  list[6].year=1809;
  list[7].name="Schumann";
  list[7].year=1810;
  list[8].name="Schubert";
  list[8].year=1797;
  list[9].name="Strauss"; //Johann Strauss II
  list[9].year=1825;

  /* printf("printing list after initiating \n"); */
  /* i=0; */
  /* while(i<10){ */
  /*   print_composer(list[i]); */
  /*   i++; */
  /* } */

  /* b = write(fd, list, 10*sizeof(composer)); */
  /* printf("# of bytes in composer struct: %lu \n", sizeof(composer)); */
  /* printf("wrote %d bytes \n",b); */
  /* lseek(fd,0,SEEK_SET); */
  /* printf("moved back to beginning of file \n"); */
  /* b = read(fd, &list, sizeof(composer)); */
  /* printf("read %d bytes \n",b); */
  /* close(fd); */

  printf("\n");

  //write list to test
  b = write(fd, list, 10*sizeof(composer));
  printf("Wrote %d bytes of information to test. \n\n", b);

  //move back to beginning of test
  lseek(fd,0,SEEK_SET);

  //(for testing purposes) clear list and print to check
  i=0;
  while(i<10){
    list[i].name="";
    list[i].year=0;
    i++;
  }
  /* printf("printing list after clearing \n"); */
  /* i=0; */
  /* while(i<10){ */
  /*   print_composer(list[i]); */
  /*   i++; */
  /* } */

  //read contents of test - block
  /* read(fd, list, 10*sizeof(composer)); */
  /* printf("Printing list after reading: \n"); */
  /* i=0; */
  /* while(i<10){ */
  /*   print_composer(list[i]); */
  /*   i++; */
  /* } */

  //alternate: read contents of test - one by one
  printf("Printing list after reading: \n");
  i=0;
  while(i<10){
    read(fd, list+i, sizeof(composer));
    print_composer(list[i]);
    i++;
  }

  //find and print user-indicated location
  printf("\nEnter a number in the range [0,10): ");
  scanf("%d", &input);
  if(input>=0&&input<10){
    printf("\nYou chose this composer:");
    //go to requested location
    lseek(fd,input*sizeof(composer),SEEK_SET);
    //make temporary variable for the purpose of printing selection
    composer temp;
    read(fd, &temp, sizeof(composer));
    print_composer(temp);
  }else{
    printf("nope");
  }
  printf("\n");

  //check to see if above result matches correct result
  /* print_composer(list[input]); */

  //edit value at user-indicated location
  printf("Enter a number in the range [0,10) (yes, again): ");
  scanf("%d", &input);
  if(input>=0&&input<10){
    printf("\nSurprise--you chose to replace this composer with someone else--the thrill is beyond words:");
    //go to requested location and print out current values (as above)
    lseek(fd,input*sizeof(composer),SEEK_SET);
    composer temp;
    read(fd, &temp, sizeof(composer));
    print_composer(temp);
    //change values
    printf("\nAnd here's your updated list of composers:");
    //go to location again (since reading above moved it)
    lseek(fd,input*sizeof(composer),SEEK_SET);
    //edit the value in the list
    list[input].name="Haydn";
    list[input].year=1732;
    //write it to the file, replacing the old value
    write(fd, list+input, sizeof(composer));
    //(this is very inefficient and probably--not probably, definitely--not a good way to test this) read file contents and write them to list again
    lseek(fd,0,SEEK_SET);
    write(fd,list,10*sizeof(composer));
    //and then print out the whole list
    i=0;
    while(i<10){
      print_composer(list[i]);
      i++;
    }
  }else{
    printf("nope");
  }
  printf("\n");

  return 0;

}
