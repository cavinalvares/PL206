/*
program: Write a Program to demonstrate that errno retains the last system call error code even after a successful call is made
*/
#include<errno.h>
#include<stdio.h>

extern int errno;

int main()
{
	
	FILE *fp;

	fp = fopen("a.txt", "r");// create error	
	
	printf("errno: %d\n", errno); // display errno

	fp = fopen("f0.txt", "r"); // no error
	int a = 1;	// no error
		
	printf("errno: %d\n", errno); // display errno

	fprintf(fp, "%d", a); // create error

	printf("errno: %d\n", errno); // display errno

	fclose(fp);


	return 0;

}
