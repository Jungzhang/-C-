/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-21 14:56
 * Filename	 : myshell.c
 * Description	 : 第七章总结,实现自己的shell--myshell程序
 * *****************************************************************************/
#include <stdio.h>
#include <list.h>

//输出shell前面的标识   myshell$
void print_prompt(void)
{
	printf("myshell $");
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
		printf("输入命令长度超出256的限定额!\n");

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
			pNew->arg[j] = '\0';	add(pHead,pNew);	j = 0;	count++;
		}
		i++;
	}
	
	return count;
}

//
