/*
program: Write a program to list out all the system call errors
*/
#include<stdio.h>
#include<errno.h>

extern int errno;
extern int sys_nerr;


int main()
{
	
	int limit = sys_nerr;

	for(errno=1; errno<=sys_nerr; errno++)
	{
		printf("\nError no: %d\n",errno);
		perror("Error message");
	}
	
	return 0;

}
