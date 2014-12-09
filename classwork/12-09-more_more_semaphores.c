


/*

semop(descriptor, operation buffer, amount)
- perform semaphore operations (like Up/Down)
- all operations performed via semop are atmoic
-params:
   - descriptor: return value of semget / i.d. of the semaphore
   - operation buffer pointer to a struct sembuf value (see below)
   - amount: number of semaphores on which you want to perform operations
      - in semctl, you give the index of the semaphore you're controlling; in semop, you give the _number_

struct sembuf{
   short sem_op; //(see below)
   short sem_num; //index of the semaphore you want to work on
   short sem_flag;
};

sem_op
   -1: Down(S)
   1: Up(S)
   any other short -/+ number: you'll request or release that value from the semaphore
   0: wait until the semaphore reaches 0

   **issue** If you write a program that Down(S)s until the semaphore hits 0 and then it crashes, you're in trouble (see below)

sem_flag
   provide further options useful for crashed programs!)
   - SEM_UNDO: allows the OS to undo the given operation; use if (when) a program exits before a semaphore was released
   - IPC_NOWAIT: instead of waiting for the semaphore to be available, return an errorx

note: using sem_op will take care of a wait loop and all the other not-so-elegant things which you'd otherwise have to write yourself

THE DINING PHILOSOPHERS PROBLEM - about resource management
- you have a circular table of philosophers
- all they do are think and eat
- they don't need resources to think
- if they are eating (noodles, that is), they need resources (2 chopsticks, that is)
- for some reason, each person only brought 1 chopstick
- (engineerings would break their chopsticks in half, but these are philosophers!)
- 1 chopstick is put between each two philosophers
- can be modeled using semaphores
- there's a "special" chopstick that rotates
- ah just Google the rest


 */
