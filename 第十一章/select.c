#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

void display_time(const char *string)
{
	int seconds;
	seconds = time((time_t *)NULL);
	printf("%s%d\n",string,seconds);
}

int main(void)
{
	fd_set readfds;
	struct timeval timeout;
	int ret;


	timeout.tv_sec = 10;	//秒数为10秒
	timeout.tv_usec = 0;	//微秒数为0

	while(1)
	{
		FD_ZERO(&readfds);	//开始使用一个描述符集合前将其清空
		FD_SET(0,&readfds);
		display_time("select之前:");
		ret = select(1,&readfds,NULL,NULL,(struct timeval *)0);
		display_time("select之后：");

		switch(ret)
		{
			case 0:
				printf("没有数据\n");
		//		exit(0);
			case -1:
				perror("select error：");
				exit(-1);
			default:
		//		getchar();
				printf("有数据\n");
		}
		setbuf(stdin,NULL);
	}

	return EXIT_SUCCESS;
}
