/*************************************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-18 19:23
 * Filename	 : eg_7_4.c
 * Description	 : vfork()和fork()创建进程的区别
                   注意:vfork必须使用exit()退出进程,如果直接return的话会将父进程的栈释放掉
				        导致程序出错
 * **********************************************************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int globvar = 5;

int main(void)
{
	pid_t pid;
	int var = 1,i;

//	pid = fork();
	pid  = vfork();
	switch (pid)
	{
		case 0 :
			i = 3;
			while (i-- > 0)
			{
				printf("子进程正在运行!\n");
				globvar++;
				var++;
				sleep(1);
			}
			printf("子进程的globvar = %d,var = %d\n",globvar,var);	exit(0);
		case -1 :	perror("ERROR");	break;
		default :
			i = 5;
			while (i-- > 0)
			{
				printf("父进程正在运行!\n");
				globvar++;
				var++;
				sleep(1);
			}
			printf("父进程的globvar = %d,var = %d\n",globvar,var);
			break;
	}

	return 0;
}
