#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
pthread_mutex_t rightlock;
pthread_mutex_t leftlock;
pthread_mutex_t Bridgelock;
sem_t LeftSide;
sem_t RightSide;
int leftcount=0;
int rightcount=0;
// pthread_t* L_car;
// pthread_t* R_car;


void* leftcar(void*a)
{
    sem_wait(&LeftSide);
    pthread_mutex_lock(&leftlock);
    leftcount++;
    if (leftcount==1)
    {
        pthread_mutex_lock(&Bridgelock); 
    }
    pthread_mutex_unlock(&leftlock);
    printf("Left\n");
    pthread_mutex_lock(&leftlock);
    leftcount--; 
    if(leftcount==0)
    {
       pthread_mutex_unlock(&Bridgelock);
    }
        pthread_mutex_unlock(&leftlock);

    sem_post(&LeftSide);
   
    pthread_exit(NULL);
}
void* rightcar(void*a)
{
    sem_wait(&RightSide);
    
    pthread_mutex_lock(&rightlock);
    rightcount++;
     if (rightcount==1)
    {
        pthread_mutex_lock(&Bridgelock); 
    }
    pthread_mutex_unlock(&rightlock);

    printf("Right\n");

    pthread_mutex_lock(&rightlock);
    rightcount--;
    if(rightcount==0)
    {
      pthread_mutex_unlock(&Bridgelock);
    }
   
        pthread_mutex_unlock(&rightlock);    
    
    sem_post(&RightSide);
    
    pthread_exit(NULL);
}

int main()
{
    sem_init(&LeftSide,0,3);
    sem_init(&RightSide,0,3);
    int size=33;
    pthread_t L_car[33],R_car[33];
  
    
    for(int i=0;i<size;i++)
    {
        pthread_create(&L_car[i],NULL,leftcar,NULL);
    }
    for(int i=0;i<size;i++)
    {
        pthread_create(&R_car[i],NULL,rightcar,NULL);
    }
     for(int i=0;i<size;i++)
    {
        pthread_join(R_car[i],NULL);
    }
    for(int i=0;i<size;i++)
    {
        pthread_join(L_car[i],NULL);
    }
   
    pthread_exit(NULL);
    
}