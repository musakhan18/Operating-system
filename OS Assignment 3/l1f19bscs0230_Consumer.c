#include<stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include<semaphore.h>

int main()
{
    sem_t Pro_lock;
    sem_t Con_lock;

    sem_init(&Con_lock,1,1);

    while(1)
    {
    int get1 = shmget(69, 27, IPC_CREAT | 0777);
    int get2 = shmget(99, 27, IPC_CREAT | 0777);

    sem_t*ptr1=shmat(get1,NULL,0777);
    sem_t*ptr=shmat(get2,NULL,0777);

     Pro_lock = ptr[0];     //Reading the aquired lock of producer  
       
        sem_wait(&Con_lock); //aquireing the lock of consumer
        ptr[0]=Con_lock;     //writing the consumer lock on shared memory
       
        sem_post(&Pro_lock); //releasing the producer lock 
    }
}