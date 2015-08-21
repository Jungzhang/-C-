#include <stdio.h>

char *strdel(char *src,char tar)
{
	char *temp = src;
	while((*temp != tar) && (*temp != '\0'))
		temp++;
	if(*temp == '\0')
	{
		printf("Delete Error!\n");	return NULL;
	}
	else
	{
		while(*temp != '\0')
		{
			*temp = *(temp + 1);	temp++;
		}
	}

	return src;
}

//int main(void)
//{

//	return 0;
//}
