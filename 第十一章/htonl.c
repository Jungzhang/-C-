/***********************************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-03 08:43
 * Filename	 : htonl.c
 * Description	 : htonl()函数练习,该函数将小端模式(高高低低)存储的数据转换成大端模式(高低低高)存储的数据
 * ********************************************************************************************************************/

#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
	int a = 10;	//10在计算机中是以小端模式存储
	int b = htonl(a);	//转换成大端模式存储仅b

	printf("a = %d\nb = %d\n",a,b);

	return 0;
}
