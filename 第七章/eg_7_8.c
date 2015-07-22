/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-20 16:54
 * Filename	 : eg_7_8.c
 * Description	 : 通过nice()函数更改进程优先级的练习
 * *****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
	pid_t pid;
	int a,oldpri,newpri;

	pid = fork();

	switch(pid)
	{
		case 0:
			printf("子进程中!\n");
			oldpri = getpriority(PRIO_PROCESS,getpid());	//读取子进程的优先级
			printf("进程旧优先级:%d\n",oldpri);
			if ((newpri = nice(2)) == -1)								//改变子进程的优先级
	//		if ((newpri = setpriority(PRIO_PROCESS,getpid(),2)) == -1)	//设置成功返回0失败返回-1
				printf("设置失败\n");
			printf("进程新优先级:%d\n",newpri);
			newpri = getpriority(PRIO_PROCESS,getpid());
			printf("进程新优先级:%d\n",newpri);
			exit(0);
		case -1:
			printf("进程创建失败!\n");
			exit(-1);
		default:
			wait(&a);		//等待子进程运行结束
			printf("父进程中!\n");
	}
	
	return 0;
}
