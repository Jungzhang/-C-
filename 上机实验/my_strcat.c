#include <stdio.h>

char *my_strcat(char *str1,const char *str2)
{
	if((str1 == NULL) || (str2 == NULL))
		return NULL;
	else
	{
		while(*str1 != '\0')	str1++;
		while(*str2 != '\0')
		{	*str1 = *str2;	str1++;	str2++;	}
		*str1 = '\0';
	}

	return str1;
}

int main(void)
{
	char str1[100];
	char str2[100];
	gets(str1);	gets(str2);
	my_strcat(str1,str2);
	puts(str1);
	

	return 0;
}
