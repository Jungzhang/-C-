/*
	Linux C 编程实战之习题4.7.5
*/

#include <stdio.h>

int max(int a[],int n)
{
	int num1,num2;
	if (n == 1)
		return a[0];
	num2 = a[0];
	num1 = max(a + 1,n - 1);
	return (num1 > num2 ? num1 : num2);
}

int main(void)
{
	int a[3] = {1,2,3};
	printf("%d\n",max(a,3));

	return 0;
}
