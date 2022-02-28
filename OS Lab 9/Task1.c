#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<pthread.h>

int size;
void *is_Even(void*arr);
void *is_Odd(void*arr);

int main(int argc,char*argv[])
{
    size=argc-1;
    int*arr=(int*)calloc(size,sizeof(int));
   
    for(int i=0;i<size;i++)
    {
        arr[i]=atoi(argv[i+1]);
    }
  

    pthread_t pid1;
    pthread_t pid2;

    pthread_create(&pid1,NULL,&is_Even,(void*)arr);
    pthread_create(&pid2,NULL,&is_Odd,(void*)arr);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);

    pthread_exit(NULL);
}

void *is_Even(void*arr)
{
    int*arr1=(int*)arr;
    printf("\nEven Numbers:\n");
    for(int i=0;i<size;i++)
    {
        if(arr1[i]%2==0)
        {
            printf("%d\n",arr1[i]);
        }
    }
    pthread_exit(NULL);
}

void*is_Odd(void*arr)
{
    int*arr1=(int*)arr;
    printf("\nOdd Numbers:\n");
    for(int i=0;i<size;i++)
    {
        if(arr1[i]%2!=0)
        {
            printf("%d\n",arr1[i]);
        }
    }
    pthread_exit(NULL);
}