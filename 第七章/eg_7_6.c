/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-20 08:45
 * Filename	 : eg_7_6.c
 * Description	 : 通过系统预定义全局变量environ显示各个环境变量的值
 * *****************************************************************************/
#include <stdio.h>

int main(void)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n",environ[i]);
	
	return 0;
}
