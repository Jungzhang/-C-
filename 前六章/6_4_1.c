/*******************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-21 09:34
 * Filename	 : 6_4.c
 * Description	 : fcntl()函数文件读写属性练习,事先在程序的工作目录已经创建好了test.txt文件
 * ****************************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd,a,b;
	if ((fd = open("test.txt",O_RDWR)) < 0)	//F_SETFD表示设置close-on-exec标志
		perror("fopen");
	if (fcntl(fd,F_SETFD,1) < 0)
		perror("SETERROR");
	if ((a = fcntl(fd,F_GETFD)) < 0)		//F_GETFD表示获取文件描述符的close-on-exec标志,
		perror("GETFDERROR");			//该标志最后一位为0表示子进程使用exec()函数族后文件仍打开,非0表示文件已关闭

	printf("GETFD = %d\n",a);
	if ((b = fcntl(fd,F_GETFL,0)) < 0)		//F_GETTEL表示获取文件的打开方式,返回值含义和打开时的含义相同
		perror("GETFLERROR");
	b = b & O_ACCMODE;	//读写文件操作时取出flag的低两位
						//O_RRDONLY<00>:只读打开
						//O_WRONLY<01>:只写打开
						//O_RDWR<02>:读写打开
	printf("O_RDWR = %o\n",O_RDWR);
	printf("GETFL = %o\n",b);

	close(fd);
	
	return  0;
}
