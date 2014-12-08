/*

semctl(descriptor, index, operation, buffer) <sys/types.h> <sys/ipc.h>
- used to control the semaphore, including:
   - set the semaphore value
   - remove the semaphore
   - get current value
   - get information about the semaphore
   - et al
- parameters:
   - descriptor: the return value of semget
   - index: the index of the semaphore yhou want to control in the semaphore identified by the descriptor (for a single semaphore set, 0)
   - operation: one of the following constants:
      IPC_RMID: remove the semaphore
      SETVAL: set the value (requires using a buffer)
      GETVAL: return the value
   - buffer

~~~~~~~~~~~~~~~~~~~~~~~~

unions (as opposed to structs) - all its members share the same memory

struct foo{
   int x; //size == 4 bytes
   char y; //size == 1 byte
}; //total size == 5 bytes (the size of the sum of its members)

union bar{
   int x; //size == 4 bytes
   char y; //size == 1 byte
}; //total size == 4 bytes (the size of its largest member)

can be used to iterate through each byte of a multi-byte data type (e.g. an int) (note: unions aren't necessary to do this, but they make the process pretty elegant--see below)

union trickster{
   int x; //size == 4 bytes
   char y[4]; //size == 4 bytes
};

union trickster test_union;
test_union.x = 765;
int i=0;
while(i<4){
   printf("%d\n",test_union.y[i]);
   i++;
}

 */
