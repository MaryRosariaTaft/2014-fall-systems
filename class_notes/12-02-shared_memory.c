#include <stdio.h>
#include <stdlib.h>

int main(){

  int f = fork();
  int status;

  if(!f){
    printf("child\n");
  }else{
    wait(&status);
    printf("parent\n");
  }

  return 0;

}

//the code above has nothing to do with the notes below

/*

Shared Memory (more IPC, inter-process communication)
- a segment of heap memory that can be accessed by multiple processes
- shared emmory is accessed via some key that is known by any process that needs to access it
- DOES NOT GET RELEASED WHEN A PROGRAM EXITS good for access by programs which are spawned in the future but gotta free gotta free
- worst-case scenario: since shared memory is stored in the RAM and not on disk space, a computer reboot will wipe the shared memory
- 5 key operations:
   - create the segment (occurs once ever)
   - access the segment (once per desired process) --> the process will in turn get a shared memory descriptor (comparable to a file descriptor)
   - attach the segment--its descriptor--to a variable (once per aforementioned process)
   - detach the segment (once per aforementioned process)
   - remove the segment (once ever)

shmget(key, size, flags) - <sys/shm.h>, <sys/ipc.h>
   Creates or accesses a shared memory segment
   Returns a shared memory descriptor, or -1 upon failure
   key - unique integer identifier for the allocated memory
   size - i dunno (in bytes)
   flags - signals whether to create the segment; includes permissions for the segment (combine with bitwise or)
      most common: IPC_CREAT (creates and fills with 0s) and IPC_EXCL (if the segment already exists, it fails)

 */
