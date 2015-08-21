#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
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
        scanf("%s",mag);
        if (send(*sock,mag,strlen(mag),0) < 0)
        {   
            perror("Send Error");   return;
        }
    }
	pthread_exit(0);
}

//收消息
void recvmag(struct arg *arg)
{
	char mag[256];
	int len;
	while(1)
	{
	    memset(mag,0,sizeof(mag));
		len = recv(*(arg->sock),mag,sizeof(mag),0);
	    if (len < 0)
	    {
	         perror("Recv Error");   return;
	    }
		if (len == 0)
		{
			pthread_cancel(*(arg->thid));	break;
		}
	   	printf("%s\n",mag);
	}
	pthread_exit(0);
}
																						

int main(int argc,char *argv[])
{
	int cli_fd,sev_fd,port,sev_addr_len;
	struct sockaddr_in cli_addr,sev_addr;
	pthread_t thid1,thid2;
	struct arg arg;
	pid_t pid;
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
	sev_addr.sin_port = htons(8080);
	sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//绑定端口
	if (bind(sev_fd,(struct sockaddr *)&sev_addr,sizeof(sev_addr)) == -1)
	{
		perror("Bind Error");	return EXIT_FAILURE;
	}
	while(1)
	{
		//监听
		if (listen(sev_fd,20) == -1)
		{
			perror("Listen Error");	return EXIT_FAILURE;
		}
		//接受连接
		sev_addr_len = sizeof(sev_addr);
		cli_fd = accept(sev_fd,(struct sockaddr *)&sev_addr,&sev_addr_len);
		if (cli_fd < 0)
		{
			perror("Accept Error");	return EXIT_FAILURE;
		}
		arg.thid = &thid1;
		arg.sock = &cli_fd;
		//接收数据
		if ((pid = fork()) == -1)
			perror("FORKERROR");
		if (pid == 0)
		{
			pthread_create(&thid1,NULL,(void *)sendmag,&cli_fd);
			pthread_create(&thid2,NULL,(void *)recvmag,&arg);
			pthread_join(thid1,NULL);
			pthread_join(thid2,NULL);
			close(cli_fd);
		}
		else{
			close(cli_fd);
		}
	}
	close(sev_fd);
}
