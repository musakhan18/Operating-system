#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int c=0;
int size = 10000;
int *arr;
int end=0;
int start=0;
int Threads=0;
void * sort(void *obj);
int main(int argc,char * argv[])
{

   
   if(argc == 2)
   {
     Threads = atoi(argv[1]);
    
     arr = (int *)  calloc(size,size*sizeof(int));
    
     for(int i=0;i<size;i++)
     {
       arr[i] = rand()%30;
     }
     
  
     pthread_t *pid;
     pid = (pthread_t*)malloc(Threads*sizeof(pthread_t));
    
     end=size/Threads;
     for(int i=0;i<Threads-1;i++)
     {
       pthread_create(&pid[i],NULL,sort,(void*)&arr[start]);
        start=end;    
        end=end+size/Threads;   
     }
     for(int i=0;i<Threads-1;i++)
     {
       pthread_join(pid[i],NULL); 
     }
     pthread_create(&pid[Threads],NULL,sort,arr);
     pthread_join(pid[Threads],NULL); 
     for(int i=0;i<size;i++)
     {
        printf("%d ",arr[i]);
        
     }
     printf("\n");
     
   }
   else
   {
     printf("Error!!\n");
   }
   
   return 0;
}
void * sort(void* obj)
{   int w=c++;
  int temp =0;
  if (w==Threads-1)
  {
    for(int i=0;i<size;i++)
    {
      for(int j=i+1;j<size;j++)
      {
        if(arr[i] > arr[j])
        {
          temp = arr[i];
          arr[i] = arr[j];
          arr[j] = temp;
        }
      }
    }  
  }
  else{

    int* a=(int*)obj;
   for(int i=0;i<size/Threads;i++)
   {
     for(int j=i+1;j<size/Threads;j++)
     {
        if(a[i] > a[j])
        {
           temp = a[i];
           a[i] = a[j];
           a[j] = temp;
        }
     }
   
   }
  }
  
   pthread_exit(NULL);
  
}