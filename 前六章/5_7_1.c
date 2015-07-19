/*
	140页习题练习,分别用带参数宏和函数找到三数字中的最大值
*/

#include <stdio.h>
#define MAX(a,b,c) ((a)>(b)?(a):(b))>(c)?((a)>(b)?(a):(b)):(c)

int max(int a,int b,int c)
{
	int maxnum = (a > b ? a : b) > c ? (a > b ? a : b) : c;

	return maxnum;
}

int main(void)
{
	int a = 1,b = 3,c = 2;
	printf("%d\n",max(a,b,c));
	printf("%d\n",MAX(a,b,c));

	return 0;
}
