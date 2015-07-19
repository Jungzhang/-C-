/*
	习题5.7_6,统计一个32位整型变量以二进制(补码)表示时1的个数
*/

#include <stdio.h>

//效率较高
int func(int num)
{
	int count;
	while (num)
	{
		count++;
		num = num & (num - 1);
	}

	return count;
}

//效率较低
int numcount(int n)
{
	int count = 0,i = 0;
	while (i < 32)
	{
		if (1 == (n & 1))
			count++;
		n = n >> 1;
		i++;
	}
	
	return count;
}

int main(void)
{
	int num;
	scanf("%d",&num);
	printf("n = %d\n",numcount(num));

	return 0;
}
