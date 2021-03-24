/*
program: 
Write a program to perform the following sequence of operations.
a. Open the file in a write only mode. If the file doesn't exist then create it.
b. Display only the access mode details
c. Check whether the append mode is enabled or not.
d. If not then enable the append mode.
e. Display the proper message after each action.
*/
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

int main()
{


	int val;

	int fd = open("f0.txt", O_WRONLY | O_CREAT | O_TRUNC, 0744);
	printf("File is opened in write only mode\n");

	if((val = fcntl(fd, F_GETFL, 0)) < 0)
		perror("Error");
	else
	{
		switch( val & O_ACCMODE )
		{
			case O_RDONLY:
					printf("The access mode is read only mode\n");
					break;

			case O_WRONLY:
					printf("The access mode is write only mode\n");
					break;
 
			case O_RDWR:
					printf("The access mode is read and write mode\n");
					break;

			default:
					printf("Unknown access mode\n");
		}

		if(val & O_APPEND)
			printf("The append mode is enabled\n");
		else
		{
			printf("The append mode is not enabled\nEnabling append mode...\n");
				
			val = val | O_APPEND;

			if((val = fcntl(fd, F_SETFL, val)) < 0)
				perror("The append mode could not be enabled");
			else
			{
				if((val = fcntl(fd, F_GETFL, 0)) < 0)
					perror("The append mode could not be enabled");
				else
				{
					if(val & O_APPEND)
						printf("The append mode has been successfully enabled\n");
					else							
						printf("The append mode could not be enabled\n");
				}	
			}			
		}
			
				
			
	}

	close(fd);

	return 0;

}
