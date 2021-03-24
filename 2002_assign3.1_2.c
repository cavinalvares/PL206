/*
Author: Jedidiah cavin alvares
Date: 27-02-2021
program: To print first 10 characters of a given file (user inputs the file name) to the standard output
*/

#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main()
{
	char file_name[20]; // stores file name
	char data[10];
		
	write(1, "\nThis program is to print first 10 characters of a given file (user inputs the file name) to the standard output\n\n", 114);

	write(1, "Enter the file name: ", 22);
	int size = read(0, file_name, 20); // the size includes new line character

	file_name[size-1] = '\0'; // inputing the null character for the string

	int fd = open(file_name, O_RDONLY); // open the file_name in read-only mode

	if(fd == -1) // checking for errors
		perror("Error");
	else
	{		
		read(fd, data, 10); // reading from fd of file_name to data
		write(1, data, 10); // displaying data to standard output
		write(1, "\n", 1); // displaying new line character
		close(fd);
	}

	return 0;
}
