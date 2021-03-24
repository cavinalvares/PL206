/*
program: Write a program that prints the n​ th​ character of a file. Pass the input filename and value of n as command line arguments to your program.
*/
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int to_int(char num[])
{
	int val = 0;

	for(int i=0; num[i] != '\0'; i++)
		val = val * 10 + (num[i] - 48);

	return val; 
}


int main(int argc, char* argv[])
{	
	char data[1];
	
	if(argc == 3)
	{		

		int fd = open(argv[1], O_RDONLY); // reading file

		if(fd < 0)
			perror("open");
		else
		{
			int pos = to_int(argv[2]); // convert string to int

			lseek(fd, pos, SEEK_SET); // putting the offset to position pos

			int n = read(fd, data, 1); // reading from the position pos

			if(n == 0) // if reading was done at offset more than the size_of_file 
				write(1,"The character at that location dosn't exist", 43);	
			else
				write(1, data, 1);

			write(1,"\n", 1);
	
			close(fd);
		}
	}
	else
		write(1,"Three arguments should have been passed\n", 40);

	return 0;
}
