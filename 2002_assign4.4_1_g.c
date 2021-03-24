/*
program: To implement tree command
*/
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

int dir_no = 0;
int file_no = 0;

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

void display(DIR * d, char tabs[], int pos)
{
	struct dirent * data;

	while((data = readdir(d)) != NULL)
	{
		if(data->d_type == DT_DIR)
		{
			if(strcmp(data->d_name, ".\0") || strcmp(data->d_name, "..\0"))
				continue;	
			else
			{
				dir_no++;

				chdir(data->d_name);

				char path[50];
				getcwd(path, 50);	
		
				printf("%s%s\n", tabs, data->d_name);
				tabs[--pos] = ' ';
				tabs[++pos] = '|';
				tabs[++pos] = '-';
				tabs[++pos] = '\0';

				display(opendir(path), tabs, pos);			
				chdir("..\0");

				pos-= 3;
				tabs[pos++] = '-';
				tabs[pos] = '\0';
			
			}
		}
		else
		{
			file_no++;
			printf("%s%s\n", tabs, data->d_name);
		}
	}

	return;
		
}


int main(int argc, char * argv[])
{	
	DIR * d;
	char tabs[20];
	char path[50];

	tabs[0] = '|';
	tabs[1] = '-';
	tabs[2] = '\0';
	int pos = 2;

	if(argc == 2)
	{
		d = opendir(argv[1]);
		chdir(argv[1]);
	}	
	else
	{
		getcwd(path, 50);
		d = opendir(path);
	}

	if(d == NULL)
		perror("opendir");
	else
	{
		
		printf(".\n");

		display(d, tabs, pos);
	
		printf("\n%d directories, %d files\n", dir_no, file_no);
	}
	return 0;
}

