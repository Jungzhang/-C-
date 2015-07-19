#include <stdio.h>

int main(void)
{
	int a,b,c,d,e;
	for (a = 1; a <= 5; a++)
	{
		for (b = 1; b <= 5; b++)
		{
			for (c = 1; c <= 5 ;c++)
			{
				for (d = 1; d <= 5; d++)
				{
					for (e = 1; e < 5; e++)
						if ((a + b + c + d + e == 15) && ((b == 1) + (a == 3) == 1) && ((b == 2) + (e == 4) == 1) && ((c == 1) + (d == 2) == 1) && ((c == 5) + (d == 3) == 1) && ((e == 4) + (a == 1) == 1))
							printf("%d\t%d\t%d\t%d\t%d\n",a,b,c,d,e);
				}
			}
		}
	}

	return 0;
}
