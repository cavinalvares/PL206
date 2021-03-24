/*
program: Write a program to implement Cat unix command 
*/
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>

int get_file_size(char file_name[])
{

	int fd = open(file_name, O_RDONLY);

	int n = lseek(fd, 0, SEEK_END);

	return n;
}

int main(int argc, char* argv[])
{

	if(argc >= 2)
	{

		for(int i = 1; i < argc; i++)
		{
			int fd = open(argv[i], O_RDONLY);

			printf("---------------%s----------------\n", argv[i]);
	
			if(fd < 0)
				perror(argv[i]);
			else
			{
				int len = get_file_size(argv[i]);
			
				char data[len];
		
				read(fd, data, len);
				write(1, data, len);		
	
			}

			printf("\n\n");

			close(fd);
	
		}
	}
	else
		printf("Invalid number of arguments. Enter the file names as arguments\n");
		

	return 0;

}
