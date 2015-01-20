#include "semaphone.h"


void print(char buff[], int size);

int main(){

  int shmd, semd, fd, SHM_KEY, SEM_KEY;

  SHM_KEY = ftok("makefile", 1);
  SEM_KEY = ftok("makefile", 2);

  shmd = shmget(SHM_KEY, sizeof(int), 0644);
  semd = semget(SEM_KEY, 1, 0644);

  //frankly, I don't know if the semaphore is serving / could potentially serve any purpose based on the way I wrote this
  //really should get around to testing that
  if(!down(semd)){

    //get size of last line
    int size = get_shm(shmd);
    char buffer[size+1];

    printf("==================\n\n");//
    
    printf("size of buffer: %lu bytes\n\n",sizeof(buffer));

    printf("buffer at creation: ");//
    print(buffer,size);//

    buffer[size] = '\0';

    printf("buffer after terminating null added: ");//
    print(buffer,size);//

    //display the last line added to the file
    int i;
    fd = open("story.txt", O_RDWR);
    i = fd;//
    printf("open returns %d\n",i);//
    i = lseek(fd, (-1)*size, SEEK_END);//
    printf("lseek returns %d\n",i);//
    i = read(fd, buffer, size);//keep this one
    printf("read returns %d\n",i);//

    printf("buffer after attempting to read: ");//
    print(buffer,size);//

    if(i == -1){

      printf("read error: %s\n", strerror(errno));

    }else{

      printf("==================\n");//
      printf("The story so far:\n");
      printf("%s ...\n\n", buffer);
      //printf("Cannot figure out why the above won't print out as a char array.  In any case, running \"./control --remove\" will correctly print out all the contents of the file.  But this is kind of driving me crazy.\n\n");

      //prompt the user to add another line (max 256 characters)
      printf("Add a new line (max 256 characters): ");
      char new_line[256];
      fgets(new_line, sizeof(new_line), stdin);
      new_line[strlen(new_line) - 1] = ' ';
      new_line[strlen(new_line)] = '\0';
      size = strlen(new_line);
      /* printf("new size (including space character): %d\n", size); */

      //append the new line to the file
      lseek(fd, 0, SEEK_END); //shouldn't be necessary, but read() isn't working up above so this is necessary
      write(fd, new_line, size);

    }
    close(fd);

    //update shared memory
    set_shm(shmd, size);
    /* print_shm(shmd); */

    //release the semaphore
    up(semd);

    return 0;

  }else{
    printf("semaphore error: %s (make sure you've already run \"./control --create\")\n", strerror(errno));
    return -1;
  }
  
}

//for testing purposes only
void print(char buff[], int size){
  int i;
  for(i=0;i<size;i++){
    printf("char %d is %c; ",i,buff[i]);
  }
  printf("\n\n");
}
