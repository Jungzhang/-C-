/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-29 09:56
 * Filename	 : pthread_cond.c
 * Description	 : 条件变量使用
 * *****************************************************************************/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void func1(void)
{
	pthread_cleanup_push(pthread_mutex_unlock,&mutex);

	while(1){
		printf("处于func1线程函数中\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("func1线程函数结束\n");
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	pthread_cleanup_pop(0);
}

void func2(void)
{
	while(1){
		printf("处于func2函数线程中\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("func2线程函数结束\n");
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

int main(void)
{
	pthread_t thid1,thid2;
	int i;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_create(&thid1,NULL,(void *)func1,NULL);
	pthread_create(&thid2,NULL,(void *)func2,NULL);

	sleep(1);
	for (i = 0; i < 10; i++)
	{
		pthread_cond_signal(&cond);	sleep(1);
	}

	sleep(1);

	return 0;
}
