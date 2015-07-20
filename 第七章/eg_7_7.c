/******************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-20 09:24
 * Filename	 : eg_7_7_1.c
 * Description	 : exec函数族练习
                   注意:需要父进程等待子进程结束,否则会让子进程成为孤儿进程
 * ***************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int a;
	char *envp[] = {"ls","-l",NULL};
	extern char **environ;
	pid = vfork();

	switch(pid)
	{
		case 0:
	//		printf("哈哈!\n");
			if (execl("/bin/ls","ls","-l",NULL) == -1)  //execl()函数练习,第一个参数为路径,其余为程序参数
	//		if (execlp("ls","ls","-la",NULL))			//execlp()函数练习,会在PATH中寻找第一个参数为名称的程序,其余为被调程序的参数
	//		if (execv("/bin/ls",envp) == -1)			//execv()函数练习,第一个参数为路径,其余为被调程序的参数
	//		if (execve("/bin/ls",envp,environ) == -1)	//execve()函数练习,第一个参数为路径,第二个为完整参数列表,第三个为新环境变量
	//		if (execle("/bin/ls","ls","-l",NULL,environ) == -1)	//execle()函数练习,第一个参数为路径,第一个NULL之前为程序参数列表,其后的为新环境变量
	//		if (execvp("ls",envp) == -1)				//execvp()函数练习,会在PATH中寻找第一个参数为名称的程序,第二个为被调函数的参数列表
				perror("ERROR");
			exit(0);
		case -1:
			perror("vfork error");	break;
		default:
	//		waitpid(pid,&a,0);	//父进程等待子进程运行结束,第一个参数为等待的子进程ID,第二个存放错误码,第三个标识父进程的动作
			wait(&a);	//父进程等待子进程运行结束,参数中存放子进程结束后的错误码(main函数中的返回值或者exit()函数的参数)
			printf("父进程中!\n");
	}

	return 0;
}
