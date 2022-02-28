#include<stdio.h>
#include<stdlib.h>
int main()
{
    int size=10000;
    int* arr=(int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++)
    {
        arr[i]=1+rand()%30;
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