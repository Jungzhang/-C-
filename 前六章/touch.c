/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-06-04 19:49
 * Filename	 : touch.c
 * Description	 : touch命令的实现
 * *****************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argv,char *argc[])
{
	int fd;
	if (argv != 2){
		printf("参数个数有误\n");	exit(0);
	}
	fd = open((argc[1]),O_CREAT | O_EXCL,436);
	close(fd);

	return 0;
}
