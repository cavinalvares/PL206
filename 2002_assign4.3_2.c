/*
program: Write a program to display the directory files in the given directory
*/
#include<dirent.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
	DIR *d;
	struct dirent *data;	

	if(argc == 2)
	{
		d = opendir(argv[1]);

		if(d == NULL)
			perror("Error: opendir");
		else
		{
			while((data = readdir(d)) != NULL)
			{
				if(data->d_type == DT_DIR)
					printf("%s\n", data->d_name);
			}
/*
		printf("DT_REG: %d", DT_REG);
		printf("DT_DIR: %d", DT_DIR);
*/		
			closedir(d);
		}
	}
	else
	{
		printf("Enter the full path of the directory as the second parameter\n");
	}	
	
	return 0;
}
