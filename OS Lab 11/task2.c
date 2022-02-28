#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

sem_t rcnt; 
sem_t rdwr; 

void *consumer(void *);
void *producer(void *);

int shared_var = 10;  
pthread_t r[20],w[5];
void *consumer(void *i)
{

    int b=(int)i;
    

    printf("consumer:%d is in the ENTRY_SECTION\n",b);
    sem_wait(&rcnt);
    r_counter++;
    if(r_counter==1)
        sem_wait(&rdwr); 
    
    sem_post(&rcnt);
  
    

    printf("consumer-%d is reading the value = %d\n",b,shared_var);

   
    
    sem_wait(&rcnt);
    r_counter--;
    if(r_counter==0)
        sem_post(&rdwr);

    sem_post(&rcnt);

}


void *producer(void *i)
{

    int b=(int)i;
    

    printf("producer:%d is in the ENTRY_SECTION\n",b);

    
    sem_wait(&rdwr);

    

    shared_var +=15;
    printf("producer-%d is writing value= %d \n",b,shared_var);


    sem_post(&rdwr);
   
}


int main(){
   
    sem_init(&rcnt,0,1);
    sem_init(&rdwr,0,1);


    
    pthread_create(&r[0],NULL,consumer,(void *)0);
    pthread_create(&r[1],NULL,consumer,(void *)1);
    pthread_create(&r[2],NULL,consumer,(void *)2);
    pthread_create(&r[3],NULL,consumer,(void *)3);
    pthread_create(&w[0],NULL,producer,(void *)0);
    pthread_create(&r[4],NULL,consumer,(void *)4);
    pthread_create(&w[1],NULL,producer,(void *)1);
    pthread_create(&r[5],NULL,consumer,(void *)5);
    pthread_create(&w[2],NULL,producer,(void *)2);
    pthread_create(&r[6],NULL,consumer,(void *)6);
   
   
    pthread_join(r[0],NULL);
    pthread_join(r[1],NULL);
    pthread_join(r[2],NULL);
    pthread_join(r[3],NULL);
    pthread_join(w[0],NULL);
    pthread_join(r[4],NULL);
    pthread_join(w[1],NULL);
    pthread_join(r[5],NULL);
    pthread_join(w[2],NULL);   
    pthread_join(r[6],NULL);
    
    
    

return 0;
}