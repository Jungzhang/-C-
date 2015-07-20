/******************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-20 09:24
 * Filename	 : eg_7_7_1.c
 * Description	 : execl()函数练习
                   注意:需要父进程等待子进程结束,否则会让子进程成为孤儿进程
 * ***************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	pid = vfork();
	int a;

	switch(pid)
	{
		case 0:
//			printf("哈哈!\n");
			if (execl("/bin/ls","ls","-l",NULL) == -1)
				printf("未执行!\n");
	//		exit(0);
		case -1:
			perror("vfork error");	break;
		default:
			wait(&a);	//父进程等待子进程运行结束
			printf("父进程中!\n");
	}

	return 0;
}
