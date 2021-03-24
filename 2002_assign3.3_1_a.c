/*
program: Write a program to implement Touch unix command 
*/
#include<fcntl.h>
#include<errno.h>
#include<stdio.h>

int main(int argc, char* argv[])
{
	if(argc >= 2)
	{

		for(int i = 1; i < argc; i++)
		{
			int n = creat(argv[i], 0744);
		
			if(n < 0)
				perror(argv[i]);
			else
				printf("File %s created successfully\n", argv[i]);
		}
	}
	else
		printf("Invalid number of arguments. Enter the file names as arguments\n");
	return 0;

}
