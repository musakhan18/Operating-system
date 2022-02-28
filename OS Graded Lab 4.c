#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
#include<sys/shm.h>
#include<pthread.h>

int start=0;
int end=0;
int size=0;
int arr[100];

void* sum(void* ptr);
void* avg(void* ptr);
void* med(void* ptr);

int main(int argc,char*argv[])
{
    size=argc-1;
    end=size/3;

    for(int i=0;i<size;i++)
    {
        arr[i]=atoi(argv[i+1]);
    }

    pthread_t thread[3];
    
    pthread_create(&thread[0],NULL,&sum,NULL);
    pthread_join(thread[0],NULL);
    start=end+1;
    end=end+size/3;
    pthread_create(&thread[1],NULL,&avg,NULL);
    pthread_join(thread[1],NULL);
    start=end+1;
    end=size; //end+size/3;
    pthread_create(&thread[2],NULL,&med,NULL);
    pthread_join(thread[2],NULL);



    pthread_exit(NULL);
}

void* sum(void* ptr)
{
    int s=0;
    for(int i=start;i<end;i++)
    {
        s=s+arr[i];
    }
    printf("Sum: %d\n",s);
    pthread_exit(NULL);
}

void* avg(void* ptr)
{
    int s=0;
    int n=end-start;
    for(int i=start;i<end;i++)
    {
        s=s+arr[i];
    }
    int a=s/n;
    printf("Avg: %d\n",a);
    pthread_exit(NULL);
}

void* med(void* ptr)
{
    int n=end-start;
    int a[20];
    int median=0;
    for(int i=0,j=start;i<n,j<end;i++,j++)
    {
        a[i]=arr[j];
    }
    if (n % 2 == 0)
    {
        median = (a[(n - 1) / 2] + a[n / 2]) / 2.0;
    }
    else
    {
        median = a[n / 2];
    }
    printf("Med: %d\n",median);
    pthread_exit(NULL);
}