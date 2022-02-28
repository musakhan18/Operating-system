#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

sem_t s1; 
sem_t s2;
sem_t s3; 

pthread_t r[3];

void *process1(void *a)
{
while(1)
{
    //sem_wait(&s2);
    sem_wait(&s3);
    printf("L");
    sem_post(&s2);
}
}
void *process2(void *a)
{
    while(1)
    {
        //sem_wait(&s3);
    sem_wait(&s1);
    printf("A");
    sem_post(&s3);
    }
}
void *process3(void*a)
{
    while(1)
    {
     //sem_wait(&s1);
    sem_wait(&s2);
    printf("H");
    sem_post(&s1);
    }
}
int main()
{
    
    sem_init(&s1,0,0);
    
  
    sem_init(&s2,0,1);
    sem_init(&s3,0,0);

    pthread_create(&r[0],NULL,process1,(void *)0);
    pthread_create(&r[1],NULL,process2,(void *)0);
    pthread_create(&r[2],NULL,process3,(void *)0);

     pthread_join(r[0],NULL);
    pthread_join(r[1],NULL);
    pthread_join(r[2],NULL);
}