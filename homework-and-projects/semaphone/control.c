#include "semaphone.h"

int main(int argc, char *argv[]){

  int shmd, semd, fd, SHM_KEY, SEM_KEY;

  SHM_KEY = ftok("makefile", 1);
  SEM_KEY = ftok("makefile", 2);

  if(argc != 2){
    printf("Please enter one valid flag.\nusage: \"./control --create\" or \"./control --remove\".\n");
    return -1;
  }

  if(!strcmp(argv[1], "--create")){

    //create shared memory, semaphore, and file
    shmd = shmget(SHM_KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
    semd = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    fd = open("story.txt", O_CREAT | O_EXCL | 0644);
    printf("fd is / open() returns %d\n\n", fd);
    close(fd);

    //use shared memory to hold size of last line in file
    set_shm(shmd, 0);
    /* print_shm(shmd); */

    //use semaphore as a binary semaphore; init to 1 so that it's available for writing
    sem_union.val = 1;
    semctl(semd, 0, SETVAL, sem_union);
    /* print_sem(semd); */

    printf("Created successfully!\n");

    return 0;

  }else if(!strcmp(argv[1], "--remove")){

    //remove shared memory
    shmd = shmget(SHM_KEY, sizeof(int), 0);
    shmctl(shmd, IPC_RMID, NULL);

    //remove semaphore
    semd = semget(SEM_KEY, 1, 0);
    semctl(semd, 0, IPC_RMID);

    //display contents of file, then remove file
    printf("Story:\n");
    system("cat story.txt");
    printf("\n");
    remove("story.txt");

    printf("\nRemoved shared memory, semaphore, and text file.\n");

    return 0;

  }else{
    printf("Please enter one valid flag.\nusage: \"./control --create\" or \"./control --remove\".\n");
    return -1;
  }

}
