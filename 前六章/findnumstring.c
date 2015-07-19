#include <stdio.h>

int findnumstring(char *outputstr,char *inputstr)
{
	int count = 0,max = 0;
	char *temp = inputstr,*final = NULL,*ftemp;
	while (*temp != '\0')
	{
		for (ftemp = temp; (('0' <= *temp) && (*temp <= '9')); temp++)
			count++;
		if (max < count)
		{
			max = count;	final = ftemp;
		}
		count = 0;	temp++;
	}
	while((*final >= '0') && (*final <= '9'))
	{
		*outputstr = *final;	outputstr++;	final++;
	}
	*outputstr = '\0';

	return max;
}

int main(void)
{
	char *src = "ab12121212121212121212121212cd12345eee125ss123456789";
	char out[100];
	int num;
	num = findnumstring(out,src);
	printf("num = %d\n",num);
	puts(out);

	return 0;
}
