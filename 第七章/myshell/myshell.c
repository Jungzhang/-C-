/***************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-21 14:56
 * Filename	 : myshell.c
 * Description	 : 第七章总结,实现自己的shell--myshell程序(只支持带本文件夹路径的程序)
				   如:支持带./a.out这种路径的程序,不支持带/home/zhanggen/a.out这种路径的程序
 * ************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "list.h"

#define NORMAL		0	//普通命令
#define OUT_RED		1	//输出重定向
#define IN_RED		2	//输出重定向
#define PIPE		3	//含有管道

extern char **environ;

//输出shell前面的标识zhanggen@myshell$:
void print_prompt(void)
{
	printf("zhanggen@myshell$:");
}

//从键盘获取命令,以\n结束,长度不大于256
void get_input(char *buf)
{
	char temp;
	int len = 0;
	temp = getchar();

	while(temp != '\n')
	{
		if (len < 256)
			buf[len] = temp;
		len++;	temp = getchar();
	}
	buf[len] = '\0';
	if (len >= 256)
		printf("ERROR:输入命令长度太长,最大输入256个字符\n");

}

//将输入的命令从buf中解析成命令和参数的形式存入链表中并返回命令参数个数
int explain_input(char *buf, arglist_t *pHead)
{
	int count = 0,i = 0,j = 0;
	arglist_t *pNew;
	freelist(pHead);
	pNew = (arglist_t *)malloc(sizeof(arglist_t));
	while(buf[i] != '\0')
	{
		if (buf[i] != ' ')
		{
			pNew = (arglist_t *)malloc(sizeof(arglist_t));
			while ((buf[i] != ' ') && (buf[i] != '\0'))
			{
				pNew->arg[j] = buf[i];	i++;	j++;
			}
			pNew->arg[j] = '\0';	pNew->arg[j+1] = '#';	pNew->pNext = NULL;	add(pHead,pNew);	j = 0;	count++;
		}
		else
			i++;
	}
	
	return count;
}

//在./、/bin/、/usr/bin/ 文件夹下查找命令的可执行程序,如果找到则返回1否则返回0
int find_command(char *command)
{
	int i;
	DIR *dir;
	struct dirent *ptr;
	char *path[] = {"./","/bin/","/usr/bin/",NULL};

	if (strncmp("./",command,2) == 0)
		command += 2;

	for (i = 0; path[i] != NULL; i++)
	{
		if ((dir = opendir(path[i])) == NULL)
		{
			perror("PATHERROR");
			return 0;
		}
		else
		{
			while((ptr = readdir(dir)) != NULL)
			{
				if (strcmp(command,ptr->d_name) == 0)
				{
					closedir(dir);	return 1;
				}
			}
			closedir(dir);
		}
	}
	return 0;
}

//执行程序
int do_cmd(int argc, arglist_t *pHead)
{
	char *command[argc + 1],*commandnext[argc + 1],*file;
	int i = 0,how = 0,flag = 0,j = 0,background = 0;
	arglist_t *pTemp = pHead->pNext;
	int fp,fp1;
	pid_t pid,pid1;

	//将命令从链表中取出来存放在数组里边
	for (i = 0; i < argc; i++)
	{
		command[i] = pTemp->arg;	pTemp = pTemp->pNext;
	}
	command[i] = NULL;
	
	//判断是否含有后台运行符&
	i = 0;
	while(command[i] != NULL)
	{
		if (strncmp(command[i],"&",1) == 0)
		{
			if (i == argc - 1)
			{
				background = 1;
				command[argc - 1] = NULL;
			}
			else
			{
				printf("Wrong Command\n");	return -1;
			}
		}
		i++;
	}

	//检查是否含有重定向符号
	i = 0;
	while(command[i] != NULL)
	{
		//检查是否含有输出重定向
		if (strcmp(command[i],">") == 0)
		{
			if ((i == argc - 1) || flag > 1){
				printf("Wrong Command\n");
				return -1;
			}
			else{
				how = OUT_RED;	flag++;
			}
		}
		//检查是否含有输入重定向
		else if (strcmp(command[i],"<") == 0)
		{
			if ((i == argc - 1) || flag > 1){
				printf("Wrong Command\n");
				return -1;
			}
			else{
				how = IN_RED;	flag++;
			}
		}
		//检查是否含有管道符
		else if (strcmp(command[i],"|") == 0)
		{
			if ((i == argc - 1) || flag > 1){
				printf("Wrong Command\n");
				return -1;
			}
			else{
				how = PIPE;	flag++;
			}
		}
		i++;
	}

	i = 0;
	//如果含有输出重定向则将输出重定向文件名提出
	if (how == OUT_RED)
	{ 
		while(command[i] != NULL)
		{
			if (strcmp(command[i],">") == 0)
			{
				file = command[i+1];	command[i] = NULL;
			}
			i++;
		}
	}
	//如果含有输入重定向则将输入重定向文件名提出
	else if (how == IN_RED)
	{
		while(command[i] != NULL)
		{
			if (strcmp(command[i],"<") == 0)
			{
				file = command[i+1];	command[i] = NULL;
			}
			i++;
		}
	}
	//如果含有管道符就将管道符后边的命令存入commandnext中
	else if (how == PIPE)
	{
		while(command[i] != NULL)
		{
			if (strncmp(command[i],"|",1) == 0)
			{
				command[i] = NULL;	i++;
				while(command[i] != NULL)
				{
					commandnext[j] = command[i];	i++;	j++;
				}
				commandnext[j] = NULL;
				break;
			}
			i++;
		}
	}
	//创建一个进程,让子进程执行传进来的程序
	if ((pid = vfork()) != -1)
	{
		if (pid == 0)
		{
			switch(how)
			{
				case 0:
						if (find_command(command[0]) == 0){
							printf("命令未找到\n");	exit(-1);
						}
						if (execvp(command[0],command) == -1){
							perror("ExecError");	exit(-1);
						}
						exit(0);
				case 1:
						if (find_command(command[0]) == 0){
							printf("命令未找到\n");	exit(-1);
						}
						if ((fp = open(file,O_RDWR|O_CREAT|O_TRUNC,0664)) == -1){
							perror("OpenFileError");	exit(-1);
						}
						if (dup2(fp,1) == -1){
							perror("DupError");	exit(-1);
						}
						if (execvp(command[0],command) == -1){
							perror("ExecError");	exit(-1);
						}
						exit(0);
				case 2:
						if (find_command(command[0]) == 0){
							printf("命令未找到\n");	exit(-1);
						}
						if ((fp = open(file,O_RDONLY)) == -1){
							perror("OpenFileError");	exit(-1);
						}
						if (dup2(fp,0) == -1){
							perror("DupError");	exit(-1);
						}
						if (execvp(command[0],command) == -1){
							perror("ExecError");	exit(-1);
						}
						exit(0);
				case 3:
						if (find_command(command[0]) == 0){
							printf("命令未找到\n");	exit(-1);
						}
						if ((pid1 = vfork()) != -1){
							if (pid1 == 0){
								if ((fp1 = open("/tmp/myshell_temp",O_WRONLY|O_CREAT|O_TRUNC,0664)) == -1){
									perror("TempFileError");	exit(-1);
								}
								if (dup2(fp1,1) == -1){
									perror("Dup2Error");	exit(-1);
								}
								if (execvp(command[0],command) == -1){
									perror("ExecError");	exit(-1);
								}
								exit(0);
							}
							else{
								wait(NULL);
								if (find_command(commandnext[0]) == 0){
									printf("命令未找到\n");	exit(-1);
								}
								if ((fp1 = open("/tmp/myshell_temp",O_RDONLY)) == -1){
									perror("OpenTempFileError");	exit(-1);
								}
								if (dup2(fp1,0) == -1){
									perror("OpenTempFileError");	exit(-1);
								}
								if (execvp(commandnext[0],commandnext) == -1){
									perror("ExecError");	exit(-1);
								}
								exit(0);
							}
						}
						else{
							perror("VforkError");
						}
			}
		}
	}
	else
	{
		perror("VforkError");	return -1;
	}
	if (background == 1)
	{
		printf("[1]%d\n",pid);	return 0;
	}
	else
	{
		wait(NULL);	return 1;
	}
}

int main(void)
{
	char buf[256],a;
	arglist_t *pHead;
	int count;
	while(1)
	{
		loop:	print_prompt();
		get_input(buf);
		if (strcmp(buf,"\0") == 0)
			goto loop;
		if (strcmp(buf,"exit") == 0 || strcmp(buf,"logout") == 0)
			exit(0);
		creatlist(&pHead);
		count = explain_input(buf,pHead);
		if (do_cmd(count,pHead) == 0){
			wait(NULL);	getchar();	printf("[1]+\t已完成!\t\t%s\n",pHead->pNext->arg);
		}
		remove("/tmp/myshell_temp");
		destroy(pHead);
	}

	return 0;
}
