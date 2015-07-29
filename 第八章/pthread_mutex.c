/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-29 09:19
 * Filename	 : pthread_mutex.c
 * Description	 : 线程互斥锁练习
 * *****************************************************************************/
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t number_mutex = PTHREAD_MUTEX_INITIALIZER;
int globalnumber = 0;

void write_globalnumber(void)
{
	pthread_mutex_lock(&number_mutex);
	globalnumber++;
	//sleep(2);
	pthread_mutex_unlock(&number_mutex);
}

void read_globalnumber(int *temp)
{
	pthread_mutex_lock(&number_mutex);
	*temp = globalnumber;
	pthread_mutex_unlock(&number_mutex);
}

int main(void)
{
	pthread_t thid1,thid2;
	int num = -99;
	if (pthread_create(&thid1,NULL,(void *)write_globalnumber,NULL) != 0)
		printf("线程1失败\n");
//	sleep(1);
	if (pthread_create(&thid2,NULL,(void *)read_globalnumber,&num) != 0)
		printf("线程2失败\n");
	sleep(1);
	printf("num = %d\n",num);
	return 0;
}
