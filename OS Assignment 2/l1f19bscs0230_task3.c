#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<time.h>
#include<sys/shm.h>
#include<pthread.h>

int main(int argc,char**argv)
{
    if(argc==2)
    {
    int size=10000;
    int N=atoi(argv[1]);
    int*arr=(int*)malloc(size*sizeof(int));
    int**fd=(int**)malloc(N*sizeof(int*));
    int**fd1=(int**)malloc(N*sizeof(int*));
    int c=getpid();
    int pid;
    int num=0;
    int div=size/N;
    int num1=0;
    int start=0;
    int end=size/N;

    for(int i=0;i<N;i++)
    {
        fd[i]=(int*)malloc(2*sizeof(int));
    }

    for(int i=0;i<N;i++)
    {
        fd1[i]=(int*)malloc(2*sizeof(int));
    }

    for(int i=0;i<N;i++)
    {
        pipe(fd[i]);
    }

    for(int i=0;i<N;i++)
    {
        pipe(fd1[i]);
    }

    for(int i=0;i<size;i++)
    {
        arr[i]=1+rand()%30;
    }
    
    // for(int i=0;i<size;i++)
    // {
    //     printf("%d ",arr[i]);
    // }  
    printf("\n\n");
    

        for(int i=0;i<N;i++)
        {
            // if(getpid()==c)
            // {
                pid=fork();
                if(pid==0)
                {
                    int*arr2=(int*)malloc(div*sizeof(int)+1);
                    read(fd1[i][0],arr2,div*sizeof(int)+1);
                    //int e=arr2[0];
                    for(int i=0;i<div;i++)
                    {
                        for(int j=i+1;j<div;j++)
                        {
                            if(arr2[i]>arr2[j])
                            {
                                int temp=arr2[i];
                                arr2[i]=arr2[j];
                                arr2[j]=temp;
                            }
                        }
                    }
                    write(fd[i][1],arr2,(div*sizeof(int))+1);
                    exit(0);
                }
                else if(pid>0)
                {
                    int*arr1=(int*)malloc(div*sizeof(int));
                    int p=num++;
                   
                        start=p*(size/N);
                        end=(p+1)*(size/N);
                       for(int i=0,j=start;j<end;i++,j++)
                        {
                         arr1[i]=arr[j];
                        }
                    close(fd1[i][0]);
                    write(fd1[i][1],arr1,(div*sizeof(int))+1);
                    close(fd1[i][1]);
                }
                else
                {
                    printf("fork() failed!!\n");
                }
            
        } 
       for(int i=0;i<N;i++)
        {
            int pp=num1++;
            start=pp*(size/N);
            end=(pp+1)*(size/N);
            int*arr3=(int*)malloc(size*sizeof(int)+1);
            close(fd[i][1]);
            read(fd[i][0],arr3,size*sizeof(int)+1);
            close(fd[i][0]);
            int j=start;
            for(int i=0;i<div;i++)
            {
                arr[j]=arr3[i];
                j++;     
            }  
        }

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
        for(int i=0;i<size;i++)
        {
            printf("%d ",arr[i]);     
        }  
        printf("\n\n"); 
    }
    else{
        printf("Error!!\n");
        printf("Invalid Arrguments\n\n");
    }            
}
