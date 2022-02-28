#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<sys/shm.h>
#include <string.h>

int main(int argc,char*argv[])
{
    char* arr=(char*)calloc(2,2*sizeof(char));
    int i=shmget(1561,32,IPC_CREAT|0777);
    char * ptr = shmat(i,NULL,0777);
    sprintf(ptr,"%s",argv[1]);
    ptr+=strlen(argv[1]);
    sprintf(ptr," ");
    ptr=ptr+1;
    sprintf(ptr,"%s",argv[2]);
    ptr+=strlen(argv[2]);
    sprintf(ptr," ");
    ptr=ptr+1;

    while(1);
}
