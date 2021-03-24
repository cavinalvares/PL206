/*
program: To implement rmdir command
*/
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char * argv[])
{	
	if(argc == 2)
	{	
			int n = rmdir(argv[1]);

			if(n < 0)
				perror("Error");

		
	}
	else
	{
		printf("Invalid number of elements, put the file name as the second parameter\n");		
	}	
	
	return 0;
}
