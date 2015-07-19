/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-18 14:45
 * Filename	 : eg_7_1.c
 * Description	 : linux C用fork()创建一个进程
 * *****************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	pid = fork();
	switch (pid)
	{
		case 0 :	printf("处于子进程中!\n");	break;
		case -1:	printf("进程创建失败!\n");	break;
		default:	printf("父进程创建子进程成功!\n");	break;
	}

	return 0;
}
