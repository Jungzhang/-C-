/**************************************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-18 16:43
 * Filename	 : eg_7_3.c
 * Description	 : 进程创建练习之孤儿进程,子进程第一次执行时进入sleep立刻切换到父进程,将父进程结束掉,这就让子进程成了一个
                   孤儿进程
 * ***********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	pid = fork();
	switch (pid)
	{
		case 0:
			while(1)
			{
				printf("我是子进程,我的ID是:%d,我的父进程ID是:%d\n",getpid(),getppid());
				sleep(1);
			}	break;
		case -1:
			perror("ERROR");	exit(-1);	break;
		default:
			printf("我是父进程,我的ID是%d\n",getpid());
			exit(0);
	}
	
	return 0;
}
