#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

char judgetype(int mode)
{
	char type;
	if (S_ISREG(mode))
		type = '-';
	else if (S_ISDIR(mode))
		type = 'd';
	else if (S_ISBLK(mode))
		type = 'b';

	return type;
}

void displayifo(int st_mode)
{
	int mode[3],i;
	char type;
	mode[0] = st_mode / 100;
	mode[1] = (st_mode % 100) / 10;
	mode[2] = st_mode % 10;
	type = judgetype(st_mode);
	printf("%c",type);
	for (i = 0; i < 3; i++)
	{
		switch (mode[i])
		{
			case 0: printf("---");	break;
			case 1: printf("--x");	break;
			case 2: printf("-w-");	break;
			case 3: printf("-wx");	break;
			case 4: printf("r--");	break;
			case 5: printf("r-x");	break;
			case 6: printf("rw-");	break;
			case 7: printf("rwx");	break;
		}
	}
	printf("\n");
}

int main(int argv,char *argc[])
{
	struct stat buf;
	if (argv != 2)
	{
		printf("参数有误\n");	exit(0);
	}
	if (stat(argc[1],&buf) == -1)
	{
		perror("Error:");	exit(-1);
	}
	buf.st_mode = (int)buf.st_mode;
	displayifo(buf.st_mode);
	printf("+=%d,V=%o\n",buf.st_mode,buf.st_mode);

	return 0;
}
