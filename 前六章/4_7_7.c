#include <stdio.h>

char *str_cat(char *str1,char *str2)
{
	char *temp = str1;
	if (NULL == str1 || NULL == str2)
	{
		printf("Error!\n");	return NULL;
	}
	while (*temp != '\0')	temp++;
	while (*str2 != '\0')
	{
		*temp = *str2;	temp++;	str2++;
	}
	*temp = '\0';

	return str1;
}

int main(void)
{
	char a[100] = {"1234567789"};
	char b[100] = {"asdfghhjkkll"};
	str_cat(a,b);
	puts(a);

	return 0;
}
