#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>

struct shmid_ds shm_buf;
struct sembuf sem_buf;
union semun {
  int val; /* Value for SETVAL */
  struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
  unsigned short *array; /* Array for GETALL, SETALL */
  struct seminfo *__buf; /* Buffer for IPC_INFO */
} sem_union;


//SHARED MEMORY FUNCTIONS

void set_shm(int shmd, int val){
  int *data;
  data = (int *)shmat(shmd, 0, 0);
  *data = val;
  shmdt(data);
  data = NULL;
}

int get_shm(int shmd){
  int *shmp, data;
  shmp = (int *)shmat(shmd, 0, 0);
  data = *shmp;
  shmdt(shmp);
  shmp = NULL;
  return data;
}

void print_shm(int shmd){
  printf("shm value: %d\n", get_shm(shmd));
}


//SEMAPHORE FUNCTIONS

int get_sem(int semd){
  return semctl(semd, 0, GETVAL);
}

//attempts to get the semaphore
//returns 0 if successful, -1 otherwise
int down(int semd){
  sem_buf.sem_op = -1;
  sem_buf.sem_num = 0;
  sem_buf.sem_flg = SEM_UNDO;
  return semop(semd, &sem_buf, 1);
}

//attempts to release the semaphore
//returns 0 if successful, -1 otherwise
int up(int semd){
  if(get_sem(semd) < 1){ //forced binary
    sem_buf.sem_op = 1;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = SEM_UNDO;
  }
  return semop(semd, &sem_buf, 1);
}

void print_sem(int semd){
  printf("sem value: %d\n", semctl(semd, 0, GETVAL));
}
