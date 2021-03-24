/*
program: To implement mkdir command
*/
#include<stdio.h>
#include<errno.h>
#include<sys/stat.h>

int main(int argc, char * argv[])
{	
	if(argc == 2)
	{	
			int n = mkdir(argv[1], 0766);

			if(n < 0)
				perror("Error");

		
	}
	else
	{
		printf("Invalid number of elements, put the file name as the second parameter\n");		
	}	
	
	return 0;
}
