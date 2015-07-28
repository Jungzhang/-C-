/**************************************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-18 15:49
 * Filename	 : eg_7_2.c
 * Description	 : 进程创建练习,让父子进程交替运行,父子进程等待1秒同时为了保证CPU效率会切换到子进程,
                   然后子进程也遇到了等待,导致它俩一起等待,出现的结果是父子进程交替运行
 *************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int k;	char *meg;
	pid = fork();
	switch (pid)
	{
		case 0 :	k = 5;	meg = "处于子进程中!";	break;
		case -1:	printf("进程创建失败!");			exit(-1);
		default:	k = 3;	meg = "处于父进程中!";	break;
	}

	while (k)
	{
		puts(meg);
		sleep(1);
		k--;
	}
	return 0;
}
