#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
pthread_mutex_t StudentLock;
pthread_mutex_t TeacherLock;
pthread_mutex_t Vacc_Area;
sem_t TeacherNum;
sem_t StudentNum;
int TeacherCount=0;
int StudentCount=0;
// pthread_t* Student_Thread;
// pthread_t* Teacher_Thread;


void* Teacher(void*a)
{
    sem_wait(&TeacherNum);
    pthread_mutex_lock(&TeacherLock);
    TeacherCount++;
    if (TeacherCount==1)
    {
        pthread_mutex_lock(&Vacc_Area); 
    }
    pthread_mutex_unlock(&TeacherLock);
    printf("Teacher\n");

    pthread_mutex_lock(&TeacherLock);
    TeacherCount--; 
    if(TeacherCount==0)
    {
        //printf("\n---------T--------\n");
        pthread_mutex_unlock(&Vacc_Area);
    }
        pthread_mutex_unlock(&TeacherLock);

    sem_post(&TeacherNum);
    //sched_yield();
    pthread_exit(NULL);
}
void* Student(void*a)
{
   // printf("X\n");
    sem_wait(&StudentNum);
    
    pthread_mutex_lock(&StudentLock);
    StudentCount++;
     if(StudentCount==1)
    {
       pthread_mutex_lock(&Vacc_Area);
    }
    pthread_mutex_unlock(&StudentLock);

    printf("Student\n");
    pthread_mutex_lock(&StudentLock);
    StudentCount--;
    if(StudentCount==0)
    {   
       //printf("\n---------S--------\n");
       pthread_mutex_unlock(&Vacc_Area); 
    }
        pthread_mutex_unlock(&StudentLock);    
    
    sem_post(&StudentNum);
    
    // pthread_mutex_lock(&StudentLock);
    // printf("Right\n");
    // pthread_mutex_unlock(&TeacherLock);
    // pthread_mutex_unlock(&StudentLock);
    pthread_exit(NULL);
}
int main()
{
    sem_init(&TeacherNum,0,3);
    sem_init(&StudentNum,0,3);
    int size=10;
    pthread_t Student_Thread[10],Teacher_Thread[10];
    // Student_Thread=(pthread_t*) malloc(size*sizeof(int)+1);
    // Teacher_Thread=(pthread_t*) malloc(size*sizeof(int)+1);
    
    for(int i=0;i<size;i++)
    {
        pthread_create(&Student_Thread[i],NULL,Teacher,NULL);
      // pthread_create(&right_c[i],NULL,Student,(void*)(long)i);
    }
    for(int i=0;i<size;i++)
    {
        pthread_create(&Teacher_Thread[i],NULL,Student,NULL);
    }
     for(int i=0;i<size;i++)
    {
        pthread_join(Teacher_Thread[i],NULL);
    }
    for(int i=0;i<size;i++)
    {
        pthread_join(Student_Thread[i],NULL);
    }
   
    pthread_exit(NULL);
    
}