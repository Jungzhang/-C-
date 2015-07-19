/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-06-04 19:49
 * Filename	 : chmod.c
 * Description	 : chmod命令的实现
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc,char *argv[])
{
	int mode; // 权限
	int mode_u; //所有者的权限
	int mode_g; //所属组的权限
	int mode_o; //其他用户权限

	if (argc < 3)
	{
		printf("参数个数有误！\n");	exit(0);
	}

	mode = atoi(argv[1]);
	if (mode > 777 || mode < 0)
	{
		printf("权限参数有误！\n");	exit(0);
	}

	mode_u = mode / 100;	mode_g = (mode % 100) / 10;	mode_o = mode % 10;
	mode = mode_u * 8 * 8 + mode_g * 8 + mode_o;
	if (chmod(argv[2],mode) == -1)
	{
		perror("Error:");	exit(1);
	}

	return 0;
}
