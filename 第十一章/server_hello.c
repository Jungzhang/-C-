#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(void)
{
	int sev_fd,cli_fd,cli_addr_len;
	struct sockaddr_in sev_addr,cli_addr;
	char buf[1048576];
	int count;

	memset(buf,0,sizeof(buf));
	memset(&cli_addr,0,sizeof(cli_addr));
	//初始化套接字和设置IP
	sev_fd = socket(AF_INET,SOCK_STREAM,0);
	if (sev_fd == -1)
	{
		perror("Socket Error");	return EXIT_FAILURE;
	}
	sev_addr.sin_family = AF_INET;
	sev_addr.sin_port = htons(8080);
	sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//绑定端口
	if (bind(sev_fd, (struct sockaddr *)&sev_addr, sizeof(struct sockaddr_in)) == -1)
	{
		perror("Bind Error");	return EXIT_FAILURE;
	}

	//服务器端监听
	if (listen(sev_fd,20))
	{
		perror("Listen Error");	return EXIT_FAILURE;
	}

	//服务器端接受连接
	cli_addr_len = sizeof(struct sockaddr_in);
	cli_fd = accept(sev_fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
	if (cli_fd == -1)
	{
		perror("Accept Error");	return EXIT_FAILURE;
	}
	while(1)
	{
		//服务器端接收数据
		if ((count = recv(cli_fd, buf, sizeof(buf), 0)) == -1)
		{
			perror("Recv Error");	return EXIT_FAILURE;
		}
		if (count == 0)
			break;
		printf("recv = %s\n",buf);
		bzero(&buf,sizeof(buf));
	}
	close(cli_fd);
	close(sev_fd);

	return EXIT_SUCCESS;
}
