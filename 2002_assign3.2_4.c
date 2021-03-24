/*
program: Write a C program that splits the given file into two new files. Read the split location and new file names using read system call.
	For eg. If the input file f.txt contains 50 bytes of data and if the split location is 20 byte, then your program should store first 		20 bytes of data into f1.txt and remaining bytes into f2.txt. Here f1.txt and f2.txt are the new file names. Your program should read 		these file names from the user.
*/
#include<fcntl.h>
#include<unistd.h>

int to_int(char num[])
{
	int val = 0;

	for(int i=0; num[i] != '\0'; i++)
		val = val * 10 + (num[i] - 48);

	return val; 
}

int get_file_size(char file_name[])
{

	int fd = open(file_name, O_RDONLY);

	int n = lseek(fd, 0, SEEK_END);

	return n;
}

int main()
{
	char file_name1[20], file_name2[20];
	char num[4];	
	int size;
	
	// geting the first file
	write(1, "Enter the first file name: ", 27);
	size = read(0, file_name1, 20);
	file_name1[size-1] = '\0';
	
	// geting the second file
	write(1, "Enter the second file name: ", 28);
	size = read(0, file_name2, 20);
	file_name2[size-1] = '\0';

	// getting the splitting number
	write(1, "Enter the the split location: ", 30);
	size = read(0, num, 4);
	num[size-1] = '\0';

	int val = to_int(num); // convert string to int

	// opening the files
	int fd = open("f1.txt", O_RDONLY);
	int fd1 = open(file_name1, O_WRONLY | O_CREAT | O_TRUNC, 0766);
	int fd2 = open(file_name2, O_WRONLY | O_CREAT | O_TRUNC, 0766);

	char data[val];
	int n = get_file_size("f1.txt\0"); // getting the size of f1.txt
	read(fd, data, val);

	if(val <= 0 || val > n) // if split value >= 0 or greater than the size_of_file
		write(1,"The file could not be split with that split value\n", 50);	
	else
	{
		write(fd1, data, val);

		if(val < n)
			val = n - val;
		else
			val = val - n;

		char data1[val];
		read(fd, data1, val);
		write(fd2, data1, val);
	}

	return 0;
}
