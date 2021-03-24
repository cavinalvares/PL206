/*
Author: Jedidiah cavin alvares
Date: 27-02-2021
program: To read a file (an argument to your program) and copy the content to new file having 10 characters (ie a newline has to be added after the 10th character)
*/

#include<fcntl.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
	char data[1]; // to store one char
	int count = 0; 
	
	write(1, "This program is to read a file (an argument to your program) and copy the content to new file having 10 characters (ie a newline has to be added after the 10th character)\n", 171);

	int fd = open(argv[1], O_RDONLY); // open the file_name in read-only mode
	int fd2 = open("f3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0744); // open the file_name in write-only mode,if dosn't exist then create

	if(fd == -1) // checking for errors
		write(1, "\nThis program needs a filename as a command line argument\n", 58);
	else
	{
		while(read(fd, data, 1) == 1) // loop will work till there is no char to read
		{	
			if(count == 10) // if count is 10 than the new line character is added
			{
				write(fd2, "\n", 1);
				count = 0;
			}
			
			if(data[0] != 10) // if data[10] is not a new line char than that data is put in f3.txt through fd2
			{
				write(fd2, data, 1);	
				count++;
			}		
				
		}
		close(fd);
	}	
	return 0;

}
