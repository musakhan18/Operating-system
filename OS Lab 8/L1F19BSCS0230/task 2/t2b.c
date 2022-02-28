#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<sys/shm.h>
int main()
{
    int i=shmget(1561,32,IPC_CREAT|0777);
    char * ptr = shmat(i,NULL,0777);
    int n1=0;
    int var;
    char var2 = (*ptr);
    while(var2!=32)
    {
        n1=n1*10;
        var=(*ptr)-48;
        n1 = var+n1;
        ptr=ptr+1;
        var2 = (*ptr);
    }
    int n2=0;
    ptr=ptr+1;
    var2 = (*ptr);
    while(var2!=32)
    {
        n2=n2*10;
        var=(*ptr)-48;
        n2 = var+n2;
        ptr=ptr+1;
        var2 = (*ptr);
    }

    printf("SUM OF TWO NUMBERS IS :: %d\n",n1+n2);
    

   
    
}
