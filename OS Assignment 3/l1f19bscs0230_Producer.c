#include<stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include<semaphore.h>

int main()
{
    sem_t Pro_lock;
    sem_t Con_lock;

    sem_init(&Pro_lock,1,1);
    
    while(1)
    {
	int s1 = shmget(69, 27, IPC_CREAT | 0777);
    int s2 = shmget(99,27,IPC_CREAT | 0777);

    sem_t*ptr1=shmat(s1,NULL,0777);
    sem_t*ptr=shmat(s2,NULL,0777);

    
        sem_wait(&Pro_lock); //aquireing the lock of producer
        ptr[0]=Pro_lock;     //writing the producer lock on shared memory
        Con_lock=ptr1[0];    //Reading the aquired lock of consumer  
        sem_post(&Con_lock); //releasing the consumer lock 
    }
}