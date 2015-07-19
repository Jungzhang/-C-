#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	DIR *dir;
	struct dirent *ptr;
	if (argc != 2)
	{
		printf("参数个数有误!\n");
		exit(0);
	}
	if ((dir = opendir(argv[1])) == NULL)
	{
		perror("ERROR");
		exit(-1);
	}
	while ((ptr = readdir(dir)) != NULL)
	{
		printf("%s\t",ptr->d_name);
	}
	closedir(dir);
	printf("\n");

	return 0;
}
