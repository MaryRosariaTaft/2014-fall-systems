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

 */
