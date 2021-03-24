/*
program: Write a program to display size of the given file using stat system call.
*/
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<stdio.h>

int main(int argc, char * argv[])
{
	if(argc == 2)
	{
		struct stat file;

		if(lstat(argv[1], &file) < 0)
			perror("Error");
		else
		{
			printf("%ld\n", file.st_size);

		}
	}
	else
		printf("Invalid number of arguments. Enter filename as the second argument\n");

	return 0;

}
