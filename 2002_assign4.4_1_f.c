/*
program: To implement cd command
*/
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char * argv[])
{	
	if(argc == 2)
	{	
			char path[50];

			int n = chdir(argv[1]);
			getcwd(path, 50);

			if(n < 0)
				perror(argv[1]);
			else
				printf("%s\n", path);

		
	}
	else
	{
		printf("Invalid number of elements, put the file name as the second parameter\n");		
	}	
	
	return 0;
}
