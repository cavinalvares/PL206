/*
program: Write a program to set file creation mask such that all future files are created with read-only permission
*/
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	umask(0333);
	creat("file10.txt", 0456);
	
	creat("file11.txt", 0265);
	

	return 0;

}

