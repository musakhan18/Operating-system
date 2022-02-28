#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

int size=10000; //size of array
int tCount=0; //counter for threads
int N=0; //number of threads
int* arr;

void* sort(void* ptr);

int main(int argc,char*argv[])
{
    arr=(int*)malloc(size*sizeof(int));
    N= atoi(argv[1]);
    srand(1);
    for(int i=0;i<size;i++)
    {
        arr[i]=(rand()%30)+1;
    }
//    for(int i=0;i<size;i++)
//     {
//         printf("%d ",arr[i]);
//     }
   
    pthread_t* thread=(pthread_t*)malloc(N*sizeof(pthread_t));

    for(int i=0;i<N-1;i++)
    {
       
        pthread_create(&thread[i],NULL,&sort,NULL); 
        
    }
    for(int i=0;i<N-1;i++)
    {
        pthread_join(thread[i],NULL);
    }
    pthread_create(&thread[N],NULL,&sort,NULL);
    pthread_join(thread[N],NULL);
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n\n");

    pthread_exit(NULL);
}

void* sort(void* ptr)
{
    int p=tCount++;
    // printf("Thread: %d\n", tCount);
   // printf("P: %d\n",p);
    if(p==N-1)
    {
        //printf("Start: %d, end: %d\n", 0,size);
       for(int i=0;i<size;i++)
        {
            for(int j=i+1;j<size;j++)
            {
                if(arr[i]>arr[j])
                {
                    int temp=arr[i];
                    arr[i]=arr[j];
                    arr[j]=temp;
                }
            }
        }
    }
    else{
    int s=p*(size/N);
    int e=(p+1)*(size/N);
    //printf("Start: %d, end: %d\n", s,e);
   
    for(int i=s;i<e;i++)
    {
        for(int j=i+1;j<e;j++)
        {
            if(arr[i]>arr[j])
            {
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    }
    //sorting(start,end);
    pthread_exit(NULL);
}


