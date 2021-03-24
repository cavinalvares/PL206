/*
program: Write a program to implement ls –l command. (use only system calls)
*/

#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include "my_lib.h"
#include<time.h>

int to_int(char num[])
{
	int val = 0;

	for(int i=0; num[i] != '\0'; i++)
		val = val * 10 + (num[i] - 48);

	return val; 
}

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


int get_file_size(char file_name[])
{

	int fd = open(file_name, O_RDONLY);

	int n = lseek(fd, 0, SEEK_END);

	return n;
}

void get_date(long int time)
{
	int year = 1970;
	int month = 1;
	int date = 1;
	int hour = 0;
	int min = 0;

	time += 19800; 

	while(1)
	{

		if(year%4 != 0)
		{
			if(time-31536000 > 0)
				time -= 31536000;
			else
				break;
		}		
		else
		{		
			if(time-31622400 > 0)
				time -= 31622400;
			else
				break;
		}
		
		year++;
	} 

	int flag = 1;
	while(1)
	{
		switch(month)
		{
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				if(time-2678400 > 0)
					time -= 2678400;
				else
					flag = 0;	
				break;

			case 2:
				if(year%4 != 0)
				{
					if(time-2419200 > 0)
						time -= 2419200;
					else
						flag = 0;
				}		
				else
				{		
					if(time-2505600 > 0)
						time -= 2505600;
					else
						flag = 0;
				}
				
				break;

			case 4: case 6: case 9: case 11:
				if(time-2592000 > 0)
					time -= 2592000;
				else
					flag = 0;					
									
				break;
			}

		if(flag)
			month++;
		else
			break;
	 }

	while(1)
	{
		if(time-86400 > 10)
		{
			time -= 86400;
			date++;
		}
		else
			break;
	}

	while(1)
	{
		if(time-3600 > 10)
		{
			time -= 3600;
			hour++;
		}
		else
			break;
	}

	while(1)
	{
		if(time-60 > 10)
		{
			time -= 60;
			min++;
		}
		else
			break;
	}
	
	switch(month)
	{
		case 1:
			write(1, "Jan", 3); break;
		case 2:
			write(1, "Feb", 3); break;
		case 3:
			write(1, "Mar", 3); break;
		case 4:
			write(1, "Apr", 3); break;
		case 5:
			write(1, "May", 3); break;
		case 6:
			write(1, "Jun", 3); break;
		case 7:
			write(1, "Jul", 3); break;
		case 8:
			write(1, "Aug", 3); break;
		case 9:
			write(1, "Sep", 3); break;
		case 10:
			write(1, "Oct", 3); break;
		case 11:
			write(1, "Nov", 3); break;
		case 12:
			write(1, "Dec", 3); break; 
	}

	write(1, " ", 1);

	char date_char[2];
	int date_len = to_char(date_char, date);
	write(1, date_char, date_len);
	write(1, " ",1);

	char hour_char[2];
	int hour_len = to_char(hour_char, hour);
	if(hour_len == 1)
	{
		hour_char[1] = hour_char[0];
		hour_char[0] = '0';
	}
	write(1, hour_char, 2);
	write(1, ":",1);

	char min_char[2];
	int min_len = to_char(min_char, min);
	if(min_len == 1)
	{
		min_char[1] = min_char[0];
		min_char[0] = '0';
	}
	write(1, min_char, 2);
	write(1, " ",1);
/*
	printf("\n%ld\n", time);
	printf("%d\n", year);
	printf("%d\n", month);
	printf("%d\n", date);
	printf("%d\n", hour);
	printf("%d\n", min);
*/
}

int get_name(int id, char name[], int pos)
{
	
	char ch[1];
	int i = 0;

	int fd = open("/etc/passwd", O_RDONLY);
	int len = get_file_size("/etc/passwd\0");	

	while(1)
	{
		int count = 0;
		int len = -1;
		char other_id[10];
	
		while(count <= pos)
		{
			int i = 0;

			do{
				read(fd, ch, 1);
				
				if(count == 0)
				{
					name[i++] = ch[0];
					len++;
				}

				if(count == pos)
					other_id[i++] = ch[0];
			
			}while(ch[0] != ':');
						
			if(count == 0)
				name[--i] = '\0';
			if(count == pos)
				other_id[--i] = '\0';
			count++;	
		}

		if(to_int(other_id) == id)
		{
			return len;
		}

		do{
			read(fd, ch, 1);
			}while(ch[0] != '\n');
	
	}

}

char get_file_type(int mode)
{
	if(S_ISREG(mode))
		return '-';

	if(S_ISDIR(mode))
		return 'd';

	if(S_ISCHR(mode))
		return 'c';

	if(S_ISBLK(mode))
		return 'b';

	if(S_ISFIFO(mode))
		return 'p';

	if(S_ISLNK(mode))
		return 'l';

	if(S_ISSOCK(mode))
		return 's';
}

void get_permissions(int mode, char per[])
{

	per[0] = (mode & S_IRUSR)? 'r' : '-';
	per[1] = (mode & S_IWUSR)? 'w' : '-';
	per[2] = (mode & S_IXUSR)? 'x' : '-';
	per[3] = (mode & S_IRGRP)? 'r' : '-';
	per[4] = (mode & S_IWGRP)? 'w' : '-';
	per[5] = (mode & S_IXGRP)? 'x' : '-';
	per[6] = (mode & S_IROTH)? 'r' : '-';
	per[7] = (mode & S_IWOTH)? 'w' : '-';
	per[8] = (mode & S_IXOTH)? 'x' : '-';
	per[9] = ' ';

}

int main(int argc, char * argv[])
{
	struct stat file;
	int i = 1;

	if(argc > 1)
	{
		while(i < argc)
		{
			if(lstat(argv[i], &file) < 0)
				perror(argv[i]);
			else
			{
				char mode[1];
				mode[0] = get_file_type(file.st_mode);

				write(1, mode, 1);

				char per[10];
				get_permissions(file.st_mode, per);

				write(1, per, 10);

				char nlink[4];
				int size = to_char(nlink, file.st_nlink);
				nlink[size] = ' ';		

				write(1, nlink, size+1);
		
				char user_name[20], group_name[20];
				int user_len = get_name(file.st_uid, user_name, 2);
				int group_len = get_name(file.st_uid, group_name, 3);
				write(1, user_name, user_len);
				write(1, " ", 1);
				write(1, group_name, group_len);
				write(1, " ", 1);

				char file_size[8];		
				int size_len = to_char(file_size, file.st_size);
				write(1, file_size, size_len);
				write(1, " ", 1);

				get_date(file.st_mtime);
				write(1, " ", 1);

				int len = 0;
				for(int j = 0; argv[i][j] != '\0'; j++)
					len++;

				write(1, argv[i], len);
				write(1, "\n", 1);
		
			}
		
			i++;
		}
		
	}
	else
		write(1, "To less arguments passed\nPass filename as arguments\n", 52);	
	
	return 0;

}
