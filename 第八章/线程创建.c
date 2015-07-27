/*************************************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-27 08:51
 * Filename	 : 线程创建.c
 * Description : int pthread_creat(pthread_t *thread,pthread_attr_t *attr,void *(*start_routine),void *arg)线程的创建练习
 				 注意编译时要链接上libpthread.a这个库
 ************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void func(void)
{
	pthread_t newthid = pthread_self();
	printf("新线程中,线程ID是:%lu\n",newthid);
}

int main(void)
{
	pthread_t thid;

	printf("主线程中,线程ID是:%lu\n",pthread_self());   //pthread_t 类型实际上等价于 (typedef unsigned long int pthread_t)

	if (pthread_create(&thid,NULL,(void *)func,NULL) != 0) //参数列表:(参数指针,线程属性(NULL表默认),函数指针(执行的函数),要传给函数的参数)
	{
		perror("CreatError");
		exit(-1);
	}
	sleep(1);		//主线程暂停1秒,切换到新线程,否则程序运行不会打印函数func中的内容

	return 0;
}
