/*
Author: Jedidiah cavin alvares
Date: 27-02-2021
program: To copy first 10 characters of f1.txt into f2.txt
*/

#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main()
{
	char data[10]; 
	
	int fd; // stores the file descriptor

	write(1, "This program is to copy first 10 characters of f1.txt into f2.txt\n", 67);

	fd = open("f1.txt",O_RDONLY); // open f1.txt in read-only mode

	if(fd == -1) // checking for errors
		perror("f1.txt");
	else
	{
		read(fd, data, 10); // reading first 10 characters of f1.txt through fd to data	
		close(fd);	

		fd = open("f2.txt",O_WRONLY | O_CREAT | O_TRUNC, 0744); // open f2.txt in write-only mode, create if file doesn't exist
	
		write(fd,data, 10); // writing 10 characters of data to f2.txt through fd
		close(fd);	
	}

	return 0;
}
