#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>

//发消息
void sendmag(int *sock,char argv[])
{
	struct stat buf;
	int fd;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit(-1);
	if (stat(argv, &buf) == -1)
		exit(-1);
	sendfile(*sock, fd, NULL, buf.st_size);
	close(fd);
}


int main(int argc,char *argv[])
{
	int sock,port;
	pthread_t thid1,thid2;
	struct sockaddr_in addr;
	//初始化socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock < 0)
	{
		perror("Socket Error");	return EXIT_FAILURE;
	}
	//设置IP
	addr.sin_family = AF_INET;	//IPv4
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(addr.sin_zero,0,sizeof(addr.sin_zero));	//连接
	if (connect(sock,(struct sockaddr *)&addr,sizeof(struct sockaddr_in)) == -1)
	{
		perror("Connect Error");	return EXIT_FAILURE;
	}
	//发送数据
	sendmag(&sock, argv[1]);
	
	close(sock);

	return EXIT_SUCCESS;
}
