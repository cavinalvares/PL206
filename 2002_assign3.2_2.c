/*
program: Write a program to find the size of the given file
*/
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int to_char(char num[], int sum)
{

	if(sum/10 != 0)
	{
		int count  = to_char(num, sum/10);
		num[count] = sum%10 + 48;
		return count + 1;
	}	
	else
	{
		num[0] = sum + 48;
		return 1;
	}

}

int main()
{
	char file_name[20];	

	// getting the file name
	write(1, "Enter the file name: ", 21);
	int size = read(0, file_name, 20);
	file_name[size-1] = '\0';

	int fd = open(file_name, O_RDONLY);

	if(fd < 0)
		perror("open");
	else
	{
		int n = lseek(fd, 0, SEEK_END); // gives location of offset + size_of_file ie 0 + SEEK_END 

		size = to_char(file_name, n); // converting integer to string

		write(1, file_name, size);
		write(1, "\n", 1);

		close(fd);
	}
	return 0;
}
