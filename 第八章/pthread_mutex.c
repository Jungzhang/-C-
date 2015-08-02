/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-29 09:19
 * Filename	 : pthread_mutex.c
 * Description	 : 线程互斥锁练习
 * *****************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t number_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t number_mutex1 = PTHREAD_MUTEX_INITIALIZER;
int a = 0;
int b = 10;

void write_globalnumber(void)
{
	pthread_mutex_lock(&number_mutex);
	a++;
	sleep(5);
	pthread_mutex_unlock(&number_mutex);
}

void read_globalnumber(void)
{
	printf("b = %d\n",b);
	pthread_mutex_lock(&number_mutex);
	printf("哈哈\n");
	printf("a = %d\n",a);
	pthread_mutex_unlock(&number_mutex);
}

int main(void)
{
	pthread_t thid1,thid2;
	if (pthread_create(&thid1,NULL,(void *)write_globalnumber,NULL) != 0)
		printf("线程1失败\n");
	sleep(1);
	if (pthread_create(&thid2,NULL,(void *)read_globalnumber,NULL) != 0)
		printf("线程2失败\n");
	pthread_join(thid1,NULL);
	pthread_join(thid2,NULL);
	return 0;
}
