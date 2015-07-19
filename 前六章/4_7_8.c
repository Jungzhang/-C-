/*
	超大数的加减乘运算
*/

#include <stdio.h>
#include <string.h>

//两个数字以个位对齐,并空出最高位以便于进位或加正负号
int change(char *m,char *n,char *result)
{

	int lenm,lenn,max,i;
	max = lenm = strlen(m);	lenn = strlen(n);
	if (max < lenn)
		max = lenn;
	strcpy(result,m);
	result[max + 1] = '\0';
	for (i = 0; i < max; i++)
	{
		result[max - i] = result[lenm - 1 - i];
		n[max - i] = n[lenn - i - 1];
	}
	for (i = 0; i <= max - lenn; i++)
		n[i] = '0';
	for (i = 0; i <= max - lenm; i++)
		result[i] = '0';
	return max;
}

//加法运算
void add(char *m,char *n,char *result)
{
	int max,i,temp = 0;
	max = change(m,n,result);
	for (i = max; i >= 0; i--)
	{
		temp = result[i] + n[i] + temp - 96;
		result[i] = temp % 10 + 48;
		temp /= 10;
	}
}

//减法运算
void subtract(char *m,char *n,char *result)
{
	int flag = 1,temp,max,i,j,lenn = strlen(n);
	if (strcmp(m,n) == 0)
	{
		strcpy(result,"0");	return;
	}
	max = change(m,n,result);
	if (lenn == max)
	{
		flag = 0;
		for (i = max; i > 0; i--)
		{
			if (n[i] >= result[i])
			{
				temp = n[i] - result[i];	result[i] = temp + 48;
			}
			else
			{
				j = 1;
				while ((n[i - j] == '0') && (i - j > 0))
				{
					n[i - j] ='9';	j++;
				}
				if (i - j > 0)
					n[i - j] -= 1;
			}
		}
	}
	else
	{
		
		for (i = max; i > 0; i--)
		{
			if (result[i] >= n[i])
			{
				temp = result[i] - n[i];	result[i] = temp + 48;
			}
			else
			{
				j = 1;
				while ((result[i - j] == '0') && (i - j > 0))
				{
					result[i - j] ='9';	j++;
				}
				if (i - j > 0)
				{
					result[i - j] -= 1;
					temp = result[i] + 10 - n[i];	result[i] = temp + 48;
				}
			}
		}
	}
	if (!flag)
		result[0] = '-';
	else
		result[0] = '+';
}

int main(void)
{
	char m[100];
	char n[100];
	char result[100];
	printf("m = ");	gets(m);
	printf("n = ");	gets(n);
/*	add(m,n,result);
	puts("add:");
	if (result[0] == '0')
		puts(result + 1);
	else
		puts(result);*/
	subtract(m,n,result);
	puts("subtract:");
	if (result[0] == '+')
		puts(result + 1);
	else
		puts(result);

	return 0;
}
