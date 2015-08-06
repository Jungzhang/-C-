/***********************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-06 16:44
 * Filename	 : server_chat1.c
 * Description	 : 多客户的服务器端程序,服务器将收到的信息转发给所有连接上来的用户
 * *********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	int cli_fd,sev_fd,port,sev_addr_len;
	struct sockaddr_in cli_addr,sev_addr;
	int result,recv_count;
	fd_set readfds,testfds;
	int cli_count = 0,fd[20];
	char buf[256];
	int i,j;

	memset(fd,0,sizeof(fd));

	if (argc != 2)
	{
		printf("参数有误!\n");	return EXIT_FAILURE;
	} 
	//初始化sever端socket
	sev_fd = socket(AF_INET,SOCK_STREAM,0);
	if (sev_fd < 0)
	{
		perror("Socket Error");	return EXIT_FAILURE;
	}
	int on = 1;
	if (setsockopt(sev_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
	{
		perror("Setsockopt Error");
		return EXIT_FAILURE;
	}
	//初始化sever端IP
	port = atoi(argv[1]);
	sev_addr.sin_family = AF_INET;
	sev_addr.sin_port = htons(port);
	sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//绑定端口
	if (bind(sev_fd,(struct sockaddr *)&sev_addr,sizeof(sev_addr)) == -1)
	{
		perror("Bind Error");	return EXIT_FAILURE;
	}
	//监听
	if (listen(sev_fd,20) == -1)
	{
		perror("Listen Error");	return EXIT_FAILURE;
	}
	
	FD_ZERO(&readfds);
	FD_SET(sev_fd,&readfds);
	fd[cli_count] = sev_fd;
	cli_count++;

	while(1)
	{
		testfds = readfds;
		result = select(20,&testfds,NULL,NULL,NULL);
		if (result == -1)
		{
			perror("Select Error");
			return EXIT_FAILURE;
		}
		if (result > 0)
		{
			for (i = 0; i < cli_count; i++)
			{
				if (FD_ISSET(fd[i],&testfds))
				{
					if (fd[i] == sev_fd)
					{
					//接受连接
						sev_addr_len = sizeof(sev_addr);
						cli_fd = accept(sev_fd,(struct sockaddr *)&sev_addr,&sev_addr_len);
						if (cli_fd < 0)
						{
							perror("Accept Error");	return EXIT_FAILURE;
						}
						FD_SET(cli_fd, &readfds);
						fd[cli_count] = cli_fd;
						cli_count++;
					}
					else
					{
						memset(buf,0,sizeof(buf));
						recv_count = recv(fd[i], buf, sizeof(buf),0);
						if (recv_count == 0)
						{
							cli_count--;
							close(fd[i]);
							FD_CLR(fd[i],&readfds);
							for (j = i; j < cli_count; j++)
								fd[j] = fd[j + 1];
						}
						else
						{
							for (j = 1; j < cli_count; j++)
							{
								if (fd[j] == fd[i])
									continue;
								send(fd[j],buf,strlen(buf),0);
							}
						}
					}
				}
			}
		}
	}
	close(sev_fd);
}
