#define _GNU_SOURCE 
#include <stdlib.h>
#include<sched.h> 
#include<stdio.h> 
#include <unistd.h> 
#include <sys/sysinfo.h>

int* CharToInt(int argc,char*argv[])
{
    int* arr=(int*)malloc(50*sizeof(int));
    for(int i=0;i<argc-1;i++)
    {
        char*  ptr=argv[i+1];
        int n=atoi(ptr);
        arr[i]=n;
    }
    return arr;
}

int sum_odd(int* arr, int size)
{
    int sum=0;
    for(int i=0;i<size;i++)
    {
        if(is_odd(arr[i]))
        {
            sum+=arr[i];
        }
    }
    return sum;
}

int is_odd(int num)
{
    if(num%2!=0)
    {
        return 1;
    }
    else
    { 
        return 0;
    }
}

int GetCpuInput()
{
    int nproc = get_nprocs_conf();
    int num;
    nproc--;
    printf("Cpu Available: 0-%d: ",nproc);
    printf("\nEnter cpu num: ");
    scanf("%d",&num);
    if(num<0||num>nproc)
    {
      while(num<0||num>nproc)
      {
          printf("\nError!");
          printf("\nInvalid Input!\n");
          printf("\nEnter cpu num: ");
          scanf("%d",&num);
      }
    }
  return num;
}

void SetAffinity()
{ 
	int num=GetCpuInput();
    cpu_set_t mask; 
	CPU_ZERO(&mask); 
    CPU_SET(num, &mask); 
    sched_setaffinity(0, sizeof(cpu_set_t), &mask); 
	printf("This  process  is  currently  running  on  processor# %d\n",sched_getcpu());
}

int main(int argc,char*argv[])
{
   SetAffinity();
   printf("\nArray\n");
   printf("------\n");
   int* arr=CharToInt(argc,argv);
   for(int i=0;i<argc-1;i++)
    {
       printf("%d ",arr[i]);
    }
    printf("\n\n");
    int sum= sum_odd(arr,argc);
    printf("sum of odd num: %d",sum);  
    printf("\n");
}
