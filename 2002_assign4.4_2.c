/*
program: Write a program to set the last access and modified time of a given file to that of another given file. (i.e enter two files, say f1 and f2. You need to set last access & modified time of f1 to that of f2)
*/
#include<stdio.h>
#include<sys/stat.h>
#include<errno.h>
#include<utime.h>

int main(int argc, char * argv[])
{
	struct stat buf;

	if(argc == 3)
	{
		if(lstat(argv[1], &buf) < 0)
			perror("lstat");
		else
		{
			struct utimbuf * time;
			time->actime = buf.st_atime;
			time->modtime = buf.st_mtime;

			if(utime(argv[2], time) < 0)
				perror("utime");
		}
	}
	else
		printf("Invalid number of arguments. Enter filenames as arguments");

}
