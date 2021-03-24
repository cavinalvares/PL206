/*
program: To implement ls command
*/
#include<dirent.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char * argv[])
{
	DIR *d;
	struct dirent *data;	

	if(argc == 1)
	{
		char path[50];
		getcwd(path, 50);
		d = opendir(path);
	}
	else
		d = opendir(argv[1]);

	if(d == NULL)
		perror("Error: opendir");
	else
	{
		int count = 0;			
		
		while((data = readdir(d)) != NULL)
		{
			printf("%-35s", data->d_name);
		
			if(count == 3)
			{
				printf("\n");
				count = 0;
			}					
			else
				count++;
		
		}
		
		printf("\n");	
		closedir(d);
	}
	
	
	return 0;
}
