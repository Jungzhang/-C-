/*****************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-27 15:25
 * Filename	 : pthread_join.c
 * Description	 : pthread_join()函数练习
 				   如果注释掉27行的pthread_join()函数的调用则打印出来的结果是不确定的是很诡异的
				   如果不注释则打印出func()内的内容和退出码为func函数中的退出码打印顺序是确定的
 * ***************************************************************************************************/
#include <stdio.h>
#include <pthread.h>

void func(void)
{
	printf("子线程中,线程ID是:%lu\n",pthread_self());
	pthread_exit(0);
}

int main(void)
{
	pthread_t thid;
	int status = -99999,err;

	if (pthread_create(&thid,NULL,(void *)func,NULL) != 0)
		printf("CreatError\n");
	pthread_join(thid,(void *)&status);   //等待子线程结束
	printf("退出码:%d\n",status);
	return 0;
}
