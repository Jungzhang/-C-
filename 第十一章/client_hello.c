/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-03 16:30
 * Filename	 : client_hello.c
 * Description	 : hello客户端
 * *****************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(void)
{
	int sock,i = -1;
	struct sockaddr_in addr;
	char buf[256];

	//创建套接字
	if ((sock = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("Socket Error");	return EXIT_FAILURE;
	}
	//设置IP和端口
	addr.sin_family = AF_INET;		//设置地址类型为IP
	addr.sin_port = htons(8080);	//设置端口
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//设置IP地址
	memset(addr.sin_zero,0,sizeof(addr.sin_zero));	//清空填充字节

	//客户端连接服务器
	if (connect(sock,(struct sockaddr *)&addr,sizeof(struct sockaddr_in)) == -1)
	{
		perror("Connect Error");	return EXIT_FAILURE;
	}
	
	while(1)
	{
		//设置待发送内容
		memset(buf,0,sizeof(buf));
		scanf("%s",buf);

		//向服务器发送数据
		if (send(sock, buf, strlen(buf),0) == -1)
		{
			perror("Send Error");	return EXIT_FAILURE;
		}
	}
	close(sock);
	
	return EXIT_SUCCESS;
}
