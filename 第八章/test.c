#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void func(void)
{
		printf("Helloworld!\n");
		pthread_exit(0);
}

int main(void)
{
	int a = 10;
	double status;
	pthread_t pth;
	printf("a = %d\n",a);
	if (pthread_create(&pth,NULL,(void *)func,NULL) != 0)
		printf("创建失败!\n");
	pthread_join(pth,(void *)&status);
	printf("status = %lf\n",status);
	printf("a = %d\n",a);
								
return 0;
}
