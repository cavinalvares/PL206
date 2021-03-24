/*
program: To implement cp command
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int strcmp(char str1[], char str2[])
{
	int i;

	for(i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
	{	
		if(str1[i] != str2[i])
			return 0;
				
	}
	
	if(str1[i] != '\0' || str2[i] != '\0')
		return 0;

	return 1;

}

int main(int argc, char * argv[])
{
	if(argc == 3)
	{
		int fd1 = open(argv[1], O_RDONLY);

		if(fd1 < 0)
			perror(argv[1]);
		else
		{
			if(!strcmp(argv[1], argv[2]))
			{			

				int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0766);

				char c[1];
				int n;		

				while(1)
				{
					n = read(fd1, c, 1);

					if(n)
						write(fd2, c, 1);
					else
						break;
				}
			}
			else
				printf("Error: The files are the same\n");
 			
		}

		
	}
	else
		printf("Invalid number of elements, put file names as the second and third parameter\n");

	return 0;
}
