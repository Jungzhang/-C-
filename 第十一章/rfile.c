#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

//收消息
void recvmag(int sock)
{
	int fd,len;

	sleep(2);
	fd = open("bbbbbbb", O_WRONLY | O_CREAT, 0664);
	if (fd < 0){
		return;
	}
	else{
		int pipefd[2];
		pipe(pipefd);
		while(1){
			len = splice(sock, NULL, pipefd[1], NULL, 32768, SPLICE_F_MOVE | SPLICE_F_MORE);
			len = splice(pipefd[0], NULL, fd, NULL, 32768, SPLICE_F_MOVE | SPLICE_F_MORE);
			if (len < 0){
				break;
			}
		}
	}
	close(fd);
	printf("接收完成");
}

int main(int argc,char *argv[])
{
	int cli_fd,sev_fd,port,sev_addr_len;
	struct sockaddr_in cli_addr,sev_addr;
	int result,recv_count;
	int i,j;
	
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
	sev_addr.sin_family = AF_INET;
	sev_addr.sin_port = htons(8080);
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
	sev_addr_len = sizeof(sev_addr);
	cli_fd = accept(sev_fd,(struct sockaddr *)&sev_addr,&sev_addr_len);

	recvmag(cli_fd);
	
	return EXIT_SUCCESS;
}
