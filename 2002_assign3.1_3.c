/*
Author: Jedidiah cavin alvares
Date: 27-02-2021
program: To read a file (an argument to your program) and displays the file with lines to standard output having 1 character (ie a newline has to be added after each character)
*/

#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char* argv[])
{
	char data[1]; // to store one char
	
	write(1, "\nThis program is to read a file (an argument to your program) and displays the file with lines to standard output having 1 character (ie a newline has to be added after each character)\n\n", 187);

	int fd = open(argv[1], O_RDONLY); // open the file_name in read-only mode

	if(fd == -1) // checking for errors
		perror("Error");
	else
	{
		while(read(fd, data, 1) == 1) // loop will work till there is no char to read
		{	
			write(1, data, 1); // display data to std output

			if(data[0] != 10) // if the char in not a new line char than new line char is added
				write(1, "\n", 1);
		}
		close(fd);
	}	
	return 0;

}
