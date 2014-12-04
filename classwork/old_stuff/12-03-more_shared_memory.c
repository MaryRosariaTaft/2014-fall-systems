#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(){

  int f, sd;
  char *p;

  sd = shmget(2354269, 1024, IPC_CREAT | 0644);

  f = fork();

  if(!f){

    p = (char *)shmat(sd, 0, 0); //type-casting is preferable but not necessary
    *p = 'X';
    printf("child: &p = %s\n", p);
    printf("child: p = %p\n", p);

  }else{

    wait(NULL);
    p = shmat(sd, 0, 0);
    printf("parent: &p = %s\n", p);
    printf("parent: p = %p\n", p);

  }

}

/*

shmat(descriptor, address, flags)
- descriptor: return value of shmget
- address: some memory address (if you enter 0, your OS will give you an address by default)
- flags: in most cases, either:
   - 0 (no flags)
   - SHM_RDONLY --> makes the memory read-only (hah couldn't've guessed)

   int sd = shmget(2354269, 1024, IPC_CREAT | 0644);
   char *p = shmat(sd,0,0);


ftok(char *path, int id) <sys/ipc.h>
- attempts to create a unique key suitable for use with shmget, given the path of an existing file and a user-selected I.D.
- better alternative to slamming the number pad with forehead
- the path must be accessible by the program running

   int sd = shmget(ftok("somedir/somesubdir/somefile", random_number), 1024, IPC_CREAT | 0644);
   char *p = shmat(sd,0,0);

 */
