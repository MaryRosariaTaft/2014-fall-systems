#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(){

  int semid;
  semid = semget(ftok("makefile", 0), 1, IPC_CREAT | 0664);

  return 0;
 
}

/*

---
The first railway semaphore signal was erected by Charles Hutton Gregory on the London and Croydon Railway (later the London Brighton and South Coast Railway) at New Cross, southeast London, about 1842 on the newly enlarged layout also accommodating the South Eastern Railway. According to J.T. Howard Turner, John Urpeth Rastrick proposed the idea to Gregory.

The semaphore was afterwards rapidly adopted as a fixed signal throughout Britain, superseding all other types in most uses by 1870. Such signals were widely adopted in the U.S. after 1908.
---
   from Wikipedia's page, "Railway semaphore signal"

purpose of semaphores: to communicate information regarding a shared resource

Programming semaphores were developed by Edsgar Dijkstra

a semaphore is a counter that represents how many processes can access a resource at any given time
   if a semaphore has a value of 0, then it is unavailable
   if it has a value of 3, then it can (can, not necessarily _does_) have 3 active users

most semaphore operations are "atomic" - they will not be split up into multiple processor instructions (prevents concurrency issues)

semaphore operations
- create
- set an initial value
- Up(S) / V(S)
   release the semaphore to signal that you are done with its associated resource (S++)
- Down(S) / P(S)
   attempt to take the semaphore (therefore it must _wait_ for the semaphore to become available if S==0)
     while(S==0)
        wait
     S--

semget(key, amount, flags) <sys/types.h> <sys/ipc.h> <sys/sem.h>
- create/get access to a semaphore (NOT the same as Up(S) --> the semaphore is not modified by semget())
- returns either a semaphore descriptor or -1
- params:
   - key: unique semaphore identifier (use ftok()!)
   - amount: the number of semaphores to create/get (note: semaphores are usually created as sets, as they are stored as sets; if you set amount > 1, you'll get an array of semaphores)
   - flags: signal whether to create; include permissions (combined with bitwise or)
      IPC_CREAT
      IPC_EXCL
       ^same as shared memory flags
 */
