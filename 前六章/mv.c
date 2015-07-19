/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-06-04 19:48
 * Filename	 : mv.c
 * Description	 : mv命令的实现
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argv,char *argc[])
{
	if (argv != 3)
	{
		printf("参数有误!\n");	exit(0);
	}
	if (rename(argc[1],argc[2]) == -1)
		perror("ERROR");

	return 0;
}
