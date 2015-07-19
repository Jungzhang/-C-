/************************************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-18 15:30
 * Filename	 : eg_7_1_1.c
 * Description	 : 进程创建练习
                   当第23行的语句被注释时运行会打印出六行语句,当第23行的语句没有注释掉时运行会打印出四行语句
				   原因是注释掉时第二次运行存在父进程和第一次创建的子进程,它也可以创建
 ************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		pid_t fpid = fork();
		if (fpid == 0)
		{
			printf("循环编号:%d  处于子进程中  父进程ID:%4d   本进程ID:%4d   fork返回值:%4d\n",i,getppid(),getpid(),fpid);
			exit(0);
		}
		else if (fpid == -1)
		{
			printf("创建失败!\n");	exit(-1);
		}
		else
			printf("循环编号:%d  处于父进程中  父进程ID:%4d   本进程ID:%4d   fork返回值:%4d\n",i,getppid(),getpid(),fpid);
	}
	
	return 0;
}
