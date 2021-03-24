/*
program: To implement mv command
*/
#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char * argv[])
{

	if(argc == 3)
	{
		struct stat buf;
		if(lstat(argv[1], &buf) < 0)
			perror("Error");
		else
		{
			if(S_ISREG(buf.st_mode))
			{
				int fd = open(argv[1], O_RDONLY);
				if(fd < 0)
					perror("open");
				else
				{
					
					while(lstat(argv[2], &buf) < 0)
					{
						creat(argv[2], 0744);
					}
	
					
					if(S_ISREG(buf.st_mode))
					{
						int n = rename(argv[1], argv[2]);

						if(n < 0)
							perror("rename");
					}
					else
					{
						char new_name[50];
						int c = 0;

						for(int i = 2; i > 0; i--)
						{
							for(int j = 0; argv[i][j] != '\0'; j++)
								new_name[c++] = argv[i][j];

							if(i == 2)
								new_name[c++] = '/';
							else
								new_name[c] = '\0';
						}

						int n = rename(argv[1], new_name);

						if(n < 0)
							perror("rename");		
					}				
			
								
				}
			}
/*
			else
			{
				while(lstat(argv[2], &buf) < 0)
				{
					mkdir(argv[2], 0744);
				}
				
				if(S_ISREG(buf.st_mode))
				{
					printf("Error: overwriting a directory file to a regular file is not possible\n");
				}
				else
				{
								
				}
			}
*/				
			
		}		
	

	}
	else
		printf("Invalid number of elements, put the file name as the second and third parameter\n");
		
			

	return 0;
}
