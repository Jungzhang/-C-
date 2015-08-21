/************************************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-28 10:31
 * Filename	 : pthread_key.c
 * Description	 : 线程私有数据的相关练习,如果a行、c行、e行不注释b行、d行、f行注释时私有数据生效,此时得到的运行结果表明
                   fun1和fun2对全局变量a的修改互不影响,如果a、c、e行注释,b、d、f行不注释时为非私有数据,此时的运行结果表
				   明fun1对全局变量a的修改影响到了fun2中的a
 ***********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_key_t keyid;
int a = 0;
void func1(void)
{
	a = 6;
	pthread_t thid = pthread_self();
	pthread_setspecific(keyid,(void *)(a));
	printf("%d\n%d\n",keyid,a);
	printf("func1我的线程ID是:%lu,a = %d\n",thid,pthread_getspecific(keyid));	//a行
//	printf("func1我的线程ID是:%lu,a = %d\n",thid,a);		//b行
	pthread_exit(0);
}

void func2(void)
{
	int status;
	a = 10;
	pthread_t thid = pthread_self();
	pthread_t thid1;
//	pthread_setspecific(keyid,(void *)(a));
	printf("func2我的线程ID是:%lu,a = %d\n",thid,pthread_getspecific(keyid));	//c行 
//	printf("func2我的线程ID是:%lu,a = %d\n",thid,a);	//d行
	if (pthread_create(&thid1,NULL,(void *)func1,NULL))
		printf("创建线程2失败\n");
	sleep(1);
	printf("func2我的线程ID是:%lu,a = %d\n",thid,pthread_getspecific(keyid));	//e行
//	printf("func2我的线程ID是:%lu,a = %d\n",thid,a);		//f行
	pthread_exit(0);
}

int main(void)
{
	pthread_t thid1;
	int status;
	
	pthread_key_create(&keyid,NULL);
	
	if (pthread_create(&thid1,NULL,(void *)func2,NULL))
		printf("创建线程1失败\n");

	printf("主线程:%lu\n",pthread_self());
	pthread_join(thid1,(void *)&status);
	pthread_key_delete(keyid);

	return 0;
}
