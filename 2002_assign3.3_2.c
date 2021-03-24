/*
program: Write a program to redirect the output of all the printf statement to a user file. Before terminating the program reset stdout to normal.
*/
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

int main()
{
	int fd = open("f.txt", O_WRONLY | O_CREAT | O_TRUNC, 0744);
	
	printf("Started in stdout\n");	

	int out = dup(1);
	
	dup2(fd, 1);
	
	close(fd);
	
	printf("This will be written to file f.txt\n");
	
	dup2(out, 1);
		
	printf("This will be written to std output\n");	
	
	close(out);
	
	return 0;
}
