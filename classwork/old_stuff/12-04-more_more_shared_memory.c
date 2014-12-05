#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){


  int f, sd;
  char *p;

  sd = shmget(2354269, 1024, IPC_CREAT | 0644);

  f = fork();

  if(!f){

    p = (char *)shmat(sd, 0, 0); //type-casting is preferable but not necessary
    *p = 'X';
    printf("child: p = %p\n", p);
    printf("child: *p = %c\n", *p);
    p = (char *)shmdt(p); //must set p to the return value of shmdt
    printf("child after detach: p = %p\n", p);
    printf("child after detach: *p = %c\n", *p);

  }else{

    wait(NULL);
    p = shmat(sd, 0, 0);
    printf("parent: p = %p\n", p);
    printf("parent: *p = %c\n", *p);
    struct shmid_ds d;
    shmctl(sd, IPC_RMID, &d);


  }

}

/*

bash command ipcs: prints information about shared memory

shmdt(void *pointer) <sys/shm.h> <sys/ipc.h>
- detaches a variable from a shared memory segment
- returns 0 upon success and -1 upon failure
- sets errno if it fails

shmctl(int descriptor, int command, struct shmid_ds *buffer) - shared memory control
- note: each shared memory segment has metadata that can be stored in a struct (struct shmid_ds)
   - examples of stored data: last access, size, pid of creator, pid of last modification
- used to perform operations on the shared memory segment
- parameters:
   - descriptor: return value of shmget
   - commands:
      IPC_STAT: populate teh buffer (shmid_ds) with information
      IPC_SET: set some of the info. for teh segment to the infor in the buffer
      IPC_RMID: remove a shared memroy segment
 */
