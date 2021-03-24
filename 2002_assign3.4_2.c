/*
program:
Write a program to perform the following sequence of operations.
a. Open a file in an append mode.
b. Insert some text.
c. Disable the append mode
d. Display the proper message after each action.
*/
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>

int main()
{


	int val;

	int fd = open("f1.txt", O_WRONLY | O_APPEND);

	if((val = fcntl(fd, F_GETFL, 0)) < 0)
		perror("Error");
	else
	{
			if(val & O_APPEND)
			{
				printf("The file is opened in append mode\n");
				int n = write(fd, "\nThis message will be appended in file f0.txt\n", 46);
			
				if(n > 0)
					printf("The message has been appended \n");

				val = val & ~O_APPEND;

				if((val = fcntl(fd, F_SETFL, val)) < 0)
					perror("The append mode could not be disabled");
				else
				{
					if((val = fcntl(fd, F_GETFL, 0)) < 0)
						perror("The append mode could not be disabled");
					else
					{
						if(val & O_APPEND)
							printf("The append mode could not be disabled\n");
						else							
							printf("The append mode was disabled\n");
					}
				}	
		
			}				
			else
				printf("The file did not open in append mode\n");
			
				
			
	}

	close(fd);

	return 0;

}
