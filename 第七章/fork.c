/****************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-22 08:51
 * Filename	 : fork.c
 * Description	 : 第21行和第22行运行结果不一致
 				   fork()复制缓存区,fork()前世界只有一个,fork后世界一分为二,一切照旧,
                   两个世界被fork部分完全相同(程序、缓存区、变量、环境变量等)
				   因为标准输出是个行缓存,所以加\n时会清除缓存,不加\n时不会清除缓存
 * *************************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i;
	for (i  = 0; i < 2; i++)
	{
		fork();
		printf("-");
	//	printf("-\n");
	}
	wait(NULL);
	wait(NULL);

	return 0;
}
