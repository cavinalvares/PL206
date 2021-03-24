/*
program: Write a program to read the standard input from a user file. Before terminating the program reset stdin to normal.
*/
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

int main()
{
	int fd = open("f1.txt", O_RDONLY);
	
	char data[10];

	write(1, "Enter a string: ", 16);

	int size = read(0, data, 10);
	data[size-1] = '\0';

	printf("read '%s' from stdin\n\n", data);	

	int in = dup(0);

	dup2(fd, 0);
	
	close(fd);

	size = read(0, data, 10);
	data[size-1] = '\0';
	printf("read '%s' from f1.txt\n\n", data);
	
	dup2(in, 0);

	write(1, "Enter: ", 7);
	
	size = read(0, data, 10);
	data[size-1] = '\0';
	printf("read '%s' from stdin\n", data);

	close(in);
	
}
