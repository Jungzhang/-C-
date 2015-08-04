#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

//发消息
void sendmag(int *sock)
{
	char mag[256];
	while(1)
	{
		memset(mag,0,sizeof(mag));
		scanf("%s",mag);
		if (send(*sock,mag,strlen(mag),0) < 0)
		{
			perror("Send Error");	return;
		}
	}
}

//收消息
void recvmag(int *sock)
{
	char mag[256];
	while(1)
	{
		memset(mag,0,sizeof(mag));
		if (recv(*sock,mag,sizeof(mag),0) < 0)
		{
			perror("Recv Error");	return;
		}
		printf("%s\n",mag);
	}
}

int main(int argc,char *argv[])
{
	int sock,port;
	pthread_t thid1,thid2;
	struct sockaddr_in addr;
	if (argc != 3)
	{
		printf("参数有误!\n");	return EXIT_FAILURE;
	}
	//初始化socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock < 0)
	{
		perror("Socket Error");	return EXIT_FAILURE;
	}
	//设置IP
	port = atoi(argv[2]);
	addr.sin_family = AF_INET;	//IPv4
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	memset(addr.sin_zero,0,sizeof(addr.sin_zero));
	//连接
	if (connect(sock,(struct sockaddr *)&addr,sizeof(struct sockaddr_in)) == -1)
	{
		perror("Connect Error");	return EXIT_FAILURE;
	}
	//发送数据
	pthread_create(&thid1,NULL,(void *)sendmag,&sock);
	pthread_create(&thid2,NULL,(void *)sendmag,&sock);

	pthread_join(thid1,NULL);
	pthread_join(thid2,NULL);

	return EXIT_SUCCESS;
}
