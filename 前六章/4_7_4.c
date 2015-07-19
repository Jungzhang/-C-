#include <stdio.h>

int f(n)
{
	if (1 == n)
		return 1;
	else if (2 == n)
		return 1;
	else
		return (f(n - 1) + f(n - 2));
}

int  main(void)
{
	int n;
	printf("n = ");	scanf("%d",&n);
	printf("%d\n",f(n));

	return 0;
}
