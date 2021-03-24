/*
program: Write a program to read two numbers and display their sum (without using any library functions).
*/
#include<unistd.h>

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


int to_int(char num[])
{
	int val = 0;

	for(int i=0; num[i] != '\0'; i++)
		val = val * 10 + (num[i] - 48);

	return val; 
}

int main()
{
	char num1[8], num2[8];

	// getting the first number 
	write(1, "Enter first number: ", 20);
	int num1_size = read(0, num1, 8);
	num1[num1_size-1] = '\0';

	// getting the second number
	write(1, "Enter second number: ", 21);
	int num2_size = read(0, num2, 8);
	num2[num2_size-1] = '\0';

	// converting the string to integer using to_int()
	int val1 = to_int(num1);
	int val2 = to_int(num2);

	int sum = val1 + val2;

	// converting integer to string so that it can be displayed through write()
	num1_size = to_char(num1, sum);

	write(1, "The sum is: ", 12);
	write(1, num1, num1_size);
	write(1, "\n", 1);

	return 0;
}
