/*
program: Write a program to implement chmod command. Enter the file name and the file permissions through the command line arguments.
*/
#include<stdio.h>
#include<sys/stat.h>

int to_int(char num[])
{
	int val = 0;

	for(int i=0; num[i] != '\0'; i++)
		val = val * 10 + (num[i] - 48);

	return val; 
}


long int get_val(int perm, char val)
{

	switch(perm){
		case 0:
			if(val == 'r')
				return S_IRUSR | S_IRGRP | S_IROTH;
			if(val == 'w')
				return S_IWUSR | S_IWGRP | S_IWOTH;
			if(val == 'x')
				return S_IXUSR | S_IXGRP | S_IXOTH;
			return 0;
		case 1:// User
			if(val == 'r')
				return S_IRUSR;
			if(val == 'w')
				return S_IWUSR;
			if(val == 'x')
				return S_IXUSR;

		case 2:// grp
			if(val == 'r')
				return S_IRGRP;
			if(val == 'w')
				return S_IWGRP;
			if(val == 'x')
				return S_IXGRP;

		case 3:// oth 
			if(val == 'r')
				return S_IROTH;
			if(val == 'w')
				return S_IWOTH;
			if(val == 'x')
				return S_IXOTH;
		
		
	}
}

int pwr(int num, int i)
{
	if(i != 0)
		return num * pwr(num, --i);
	else
		return 1;
}

int to_dec(int oct_num)
{
	int i = 0;
	int dec = 0;
	
	while(oct_num != 0)
	{
		dec += oct_num%10 * pwr(8, i++);
		oct_num = oct_num/10;
	}
	
	return dec;
}
/*
int to_bin(int dec_num, int bin_num[])
{
	if(dec_num != 1)
	{		
		int i = to_bin(dec_num/2, bin_num);
		bin_num[i] = dec_num%2;
		return i-1;
	}
	else
	{
		bin_num[9] = 1;
		return 8;
	}
}
*/
int main(int argc, char * argv[])
{


	if(argc == 3)
	{
		int i = 0;
		struct stat file;

		if(stat(argv[2], &file) < 0)
		{
			perror(argv[2]);
			return 0;	
		}
	
		if(argv[1][i] >= 48 && argv[1][i] <= 55)
		{
			if(argv[1][i] <= 55 && argv[1][i+1] <= 55 && argv[1][i+2] <= 55 && argv[1][i+3] == '\0')
			{	
				int oct_num = to_int(argv[1]);	
				int dec = to_dec(oct_num);
				chmod(argv[2], dec);
			}
			else
				printf("Only octal three-digit numbers are allowed\n");			
			
			return 0;
		}

		
		int perm_val = 0;
		long int val = 0;
		char sign;
		int u_flag = 1, g_flag = 1, o_flag = 1, a_flag = 1;

		while(argv[1][i] != '+' && argv[1][i] != '-' && argv[1][i] != '=' && i<3)
		{

			switch(argv[1][i])
			{
				case 'u':
					if(u_flag)
						perm_val = perm_val * 10 + 1;
					u_flag = 0;
					i++;
					break;		
				
				case 'g':
					if(g_flag)
						perm_val = perm_val * 10 + 2;
					g_flag = 0;					
					i++;
					break;		
						
				case 'o':
					if(o_flag)
						perm_val = perm_val * 10 + 3; 
					o_flag = 0;					
					i++;
					break;		
						
				case 'a':
					if(a_flag)
						perm_val = 123; 
					a_flag = 0;					
					i++;
					break;
		
				default:
					printf("The permssion passed is invalid\n");
					return 0;
			}
		}

		//printf("perm_val: %d\n", perm_val);

		if(argv[1][i] == '+' || argv[1][i] == '-' || argv[1][i] == '=')		
			sign = argv[1][i++];
		else
		{
			printf("Invalid permission passed\n");
			return 0;
		}	
		//printf("sign: %c\n", sign);
		int val2 = 0;

		do
		{
			int temp = i;			

			while(argv[1][temp] != '\0')
			{
				if((val |= get_val(0 + perm_val%10, argv[1][temp])) != 0)
					temp++;
				//printf("val: %ld\n", val);
			}

			if(sign == '=')
			{
				if(perm_val%10 == 1)
					val2 += S_IRWXU;

				if(perm_val%10 == 2)
					val2 += S_IRWXG;

				if(perm_val%10 == 3)
					val2 += S_IRWXO;					
						
				//printf("val: %ld\nval2: %d\n", val, val2);
			}	

			perm_val = perm_val/10;
				
			
		}while(perm_val != 0);
		

		if(sign == '+' || sign == '=')
		{
			if(chmod(argv[2], (file.st_mode | val)) < 0)
				printf("Error\n");
		}		
			
		
		if(sign == '-' || sign == '=')
		{
			if(sign == '=')
			{
				stat(argv[2], &file);
				val = val2 - val;
			}
			if(chmod(argv[2], (file.st_mode & ~val)) < 0)
				printf("Error\n");
		}
		
		

/*
		printf("~S_IRUSR :%d\n", ~S_IRUSR);
		printf("~S_IWUSR :%d\n", ~S_IWUSR);
		printf("S_IXUSR :%d\n", S_IXUSR);
		printf("S_IRWXU :%d\n", S_IRWXU);
		printf("~S_IRUSR | ~S_IWUSR :%d\n", ~S_IRUSR | ~S_IWUSR);
*/
		
		
	}
	
	return 0;
}
