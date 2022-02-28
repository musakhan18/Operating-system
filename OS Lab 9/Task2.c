#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<sys/shm.h>
#include<pthread.h>

void* n_Fact(void* x);
void* p_Fact(void* x);
void* n_p_Fact(void* x);

int main(int argc,char*argv[])
{
    int n=5;
    int p=3;
    int x=n-p;
    void* nFact;
    void* pFact;
    void* n_p;
    
    pthread_t pid1;
    pthread_t pid2;
    pthread_t pid3;

    pthread_create(&pid1,NULL,&n_Fact,(void*)n);
    pthread_create(&pid2,NULL,&p_Fact,(void*)p);
    pthread_create(&pid3,NULL,&n_p_Fact,(void*)x);
    pthread_join(pid1,&nFact);
    pthread_join(pid2,&pFact);
    pthread_join(pid3,&n_p);

    int numb=*((int*)(n_p))*(*((int*)pFact));
    int num=*((int*)nFact)/numb;
    printf("C(n,p) = %d\n", num);
    pthread_exit(NULL);
}

void* n_Fact(void* x)
{
    int *nFact=(int*)malloc(sizeof(int));
    *nFact=1;

    int n=(int)x;
    for (int i = 1; i <= n; ++i)
    {
        *nFact *= i;
    }
    
    return (void*)nFact;
    pthread_exit(NULL);
}

void* p_Fact(void* x)
{
    int *pFact=(int*)malloc(sizeof(int));
    *pFact=1;
    int p=(int)x;
    for (int i = 1; i <= p; ++i) 
    {
        *pFact *= i;
    }
    return (void*)pFact;
    pthread_exit(NULL);
}

void* n_p_Fact(void* x)
{
    int *n_p=(int*)malloc(sizeof(int));
    *n_p=1;
    int num=(int)x;
    // *n_p=1;
    for (int i = 1; i <= num; ++i) 
    {
        *n_p *= i;
    }
    return (void*)n_p;
    pthread_exit(NULL);
}