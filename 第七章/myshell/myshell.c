/***************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-21 14:56
 * Filename	 : myshell.c
 * Description	 : 第七章总结,实现自己的shell--myshell程序(只支持带本文件夹路径的程序)
				   如:支持带./a.out这种路径的程序,不支持带/home/zhanggen/a.out这种路径的程序
 * ************************************************************************************************/
#include <stdio.h>
#include <dirent.h>
#include <string.h>
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
			*buf[len] = temp;
		len++;	temp = getchar();
	}

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
				pNew->arg[j] = buf[i];	pNew->pNext = NULL;	i++;	j++;
			}
			pNew->arg[j] = '\0';	add(pHead,pNew);	j = 0;	count++;
		}
		i++;
	}
	
	return count;
}

//在./、/bin/、/usr/bin/ 文件夹下查找命令的可执行程序
int find_command(char *command)
{
	int i;
	DIR *dir;
	struct dirent *ptr;
	char *path = {"./","/bin/","/usr/bin/",NULL};

	if (strncmp("./",command,2) == 0)
		command += 2;

	for (i = 0; path[i] != NULL; i++)
	{
		if ((dir = opendir(path)) == NULL)
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
void do_cmd(int argc, arglist *pHead)
{
	char *command[argc + 1],*commandnext[argc + 1],*file;
	int i = 0,how = 0,flag = 0,j = 0;
	arglist_t *pTemp = pHead->pNext;

	//将命令从链表中取出来存放在数组里边
	for (i = 0; i < argc; i++)
	{
		command[i] = pTemp->arg;
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
				printf("Wrong Command\n");	return ;
			}
		}
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
				return ;
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
				return ;
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
				return ;
			}
			else{
				how = PIPE;	flag++;
			}
		}
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
	if (how == IN_RED)
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
	if (how == PIPE)
	{
		while(command[i] != NULL)
		{
			if (strcmp(command[i],"|") == 0)
			{
				command[i] = NULL;	i++;
				while(command[i] != NULL)
				{
					commandnext[j] = command[i];	i++;	j++;
				}
				commandnext[j] = NULL;
			}
			i++;
		}
	}
}
