#include <stdio.h>

int main(void)
{
	extern strdel(char *src,char tar);
	char src[100],tar;
	gets(src);
	scanf("%c",&tar);
	strdel(src,tar);
	puts(src);

	return 0;
}
