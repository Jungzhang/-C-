#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

struct arg{
	pthread_t *thid;
	int *sock;
};
//发消息
void sendmag(int *sock)
{
	char mag[256];
	while(1)
	{
		memset(mag,0,sizeof(mag));
		fgets(mag,sizeof(mag),stdin);
		if (send(*sock,mag,strlen(mag),0) < 0)
		{
			perror("Send Error");	return;
		}
	}
	pthread_exit(0);
}

//收消息
void recvmag(struct arg *arg1)
{
	char mag[256];
	int len;
	while(1)
	{
		memset(mag,0,sizeof(mag));
		len = recv(*(arg1->sock),mag,sizeof(mag),0);
		if (len < 0)
		{
			perror("Recv Error");	return;
		}
		if (len == 0)
		{
			pthread_cancel(*(arg1->thid));
			break;
		}
		printf("%s",mag);
	}
	pthread_exit(0);
}

int main(int argc,char *argv[])
{
	int sock,port;
	pthread_t thid1,thid2;
	struct sockaddr_in addr;
	struct arg arg;
//	if (argc != 3)
//	{
//		printf("参数有误!\n");	return EXIT_FAILURE;
//	}
	//初始化socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock < 0)
	{
		perror("Socket Error");	return EXIT_FAILURE;
	}
	//设置IP
//	port = atoi(argv[2]);
	addr.sin_family = AF_INET;	//IPv4
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("45.78.13.104");
	memset(addr.sin_zero,0,sizeof(addr.sin_zero));	//连接
	if (connect(sock,(struct sockaddr *)&addr,sizeof(struct sockaddr_in)) == -1)
	{
		perror("Connect Error");	return EXIT_FAILURE;
	}
	//发送数据
	arg.thid = &thid1;
	arg.sock = &sock;
	pthread_create(&thid1,NULL,(void *)sendmag,&sock);
	pthread_create(&thid2,NULL,(void *)recvmag,&arg);

	pthread_join(thid1,NULL);
	pthread_join(thid2,NULL);
	close(sock);

	return EXIT_SUCCESS;
}
