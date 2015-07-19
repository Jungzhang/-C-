#include <stdio.h>

int main(void)
{
	int flag,i,sum;
	char killer;
	for (i = 0; i < 4; i++)
	{
		sum = 0;	flag = 0;
		killer = 65 + i;
		sum = (killer != 'A') + (killer == 'C') + (killer == 'D') + (killer != 'D');
		if (3 == sum)
			printf("%c is killer!\n",killer);
		else if (0 == sum) 
			printf("Can't find killer!\n");
	}

	return 0;
}
