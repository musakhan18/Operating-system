#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<sys/shm.h>
int main()
{
	int i=shmget(1234,32,IPC_CREAT|0777);
	char * ptr = shmat(i,NULL,0777);
	sprintf(ptr,"Welcome to OS ");
	while(1);
}
