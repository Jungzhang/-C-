/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-19 15:30
 * Filename	 : eg_4_7_5.c
 * Description	 : 创建一个守护进程
 * *****************************************************************************/

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdlib.h>

int init_daemon(void)
{
	pid_t pid;
	int i;

	signal(SIGTTOU,SIG_IGN);	//忽略程序写终端
	signal(SIGTTIN,SIG_IGN);	//忽略程序读终端
	signal(SIGTSTP,SIG_IGN);	//忽略Ctrl+Z(挂起进程)
	
	pid = fork();
	if (pid > 0)
		exit(0);
	else if (pid < 0)
		return -1;
	
	pid = setsid();
	if (pid < 0)
		perror("setsid ERROR");

	chdir("/");

	umask(0);

	for (i = 0; i <= NOFILE; i++)
		close(i);

	signal(SIGCHLD,SIG_IGN);

	return 0;
}

int main(void)
{
	time_t now;
	init_daemon();
	syslog(LOG_USER|LOG_INFO,"测试守护进程 \n");
	while(1)
	{
		sleep(10);
		time(&now);
		syslog(LOG_USER|LOG_INFO,"系统时间: \t%s\t\t\n",ctime(&now));
	}
	
	return 0;
}
