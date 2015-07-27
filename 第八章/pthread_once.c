/*************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-27 10:41
 * Filename	 : pthread_once.c
 * Description	 : pthread_once(pthread_once_t *once_control,void(*init_routine)(void))函数练习
                   pthread_once()函数用来调用第二个参数指向的函数,如果第一个参数为0则表示线程之
				   间只调用一次该函数,如果为1则表示所有线程等待其中一个线程发出已完成的信号,如果
				   为2表示已完成一次调用下一个线程再次调用时不再执行
 * **********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void func(void)
{
	printf("新线程,线程ID是:%lu\n",pthread_self());
}

void func1(void)
{
	printf("func1中\n");
	printf("once = %d\n",once);
	pthread_once(&once,func);
	printf("func1结束\n");
}

void func2(void)
{
	printf("func2中\n");
	printf("once = %d\n",once);
	pthread_once(&once,func);
	printf("func2结束\n");
}

int main(void)
{
	pthread_t thid;
	int err;
	printf("主线程,ID:%lu\n",pthread_self());
	if ((err = pthread_create(&thid,NULL,(void *)func1,NULL) != 0)){
		printf("CreatError:%d\n",err);
	}
	sleep(1);

	if ((err = pthread_create(&thid,NULL,(void *)func2,NULL) != 0)){
		printf("CreatError:%d\n",err);
	}
	sleep(1);
	printf("main中\n");
	pthread_once(&once,func);
	printf("main结束\n");

	return 0;
}
