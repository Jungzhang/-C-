/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-11 14:27
 * Filename	 : server_main.c
 * Description	 : 服务器端程序主文件
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "./View/message.h"
#include "./Common/common.h"
#include "./Common/list.h"
#include "./Server/log_sev.h"

int main(void)
{
	int sev_fd,cli_fd,cli_addr_len;			//客户端、服务器端描述符,客户端地址长度
	char *ifo;								//错误提示
	struct sockaddr_in cli_addr,sev_addr;	//客户端、服务器地址结构
	fd_set readfds,testfds;					//监控集合
	int cli_count = 0,recv_count,result;	//连接数目、收到字节数目、发生时间数目
	onlinelist *pHead, *pNew, *pTemp, *pTar;		//链表操作
	datapack buf;							//数据包

	//开启服务,添加系统日志
	ifo = "The server is strart";
	add_syslog_sev(ifo);

	//初始化socket
	sev_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sev_fd < 0){
		ifo = strerror(errno);
		add_errorlog_sev(ifo);
		return EXIT_FAILURE;
	}
	int on = 1;
	if (setsockopt(sev_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1){
		ifo = strerror(errno);
		add_errorlog_sev(ifo);
		return EXIT_FAILURE;
	}
	//初始化server端IP;
	sev_addr.sin_family = AF_INET;
	sev_addr.sin_port = htons(2489);
	sev_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//绑定端口
	if (bind(sev_fd,(struct sockaddr *)&sev_addr,sizeof(sev_addr)) == -1){
		ifo = strerror(errno);
		add_errorlog_sev(ifo);
		return EXIT_FAILURE;
	}
	//监听
	if (listen(sev_fd,40) == -1){
		ifo = strerror(errno);
		add_errorlog_sev(ifo);
		return EXIT_FAILURE;
	}

	//创建一条链表用于存储连接上的用户套接字描述符
	list_creat(pHead,onlinelist);

	FD_ZERO(&readfds);
	FD_SET(sev_fd,&readfds);
	pNew = (onlinelist *)malloc(sizeof(onlinelist));
	pNew->sock = sev_fd;
	add_tial(pHead, pNew, onlinelist);
	cli_count++;

	while(1){
		testfds = readfds;
		result = select(100,&testfds,NULL,NULL,NULL);
		if (result == -1){
			ifo = strerror(errno);
			add_errorlog_sev(ifo);
			return EXIT_FAILURE;
		}
		if (result > 0){
			pTemp = pHead->pNext;
			while(pTemp != NULL){
				if (FD_ISSET(pTemp->sock,&testfds)){
					if (pTemp->sock == sev_fd){
						//接受连接
						cli_addr_len = sizeof(cli_addr);
						cli_fd = accept(sev_fd,(struct sockaddr *)&cli_addr,&cli_addr_len);
						if (cli_fd < 0){
							ifo = strerror(errno);
							add_errorlog_sev(ifo);
							return EXIT_FAILURE;
						}
						FD_SET(cli_fd, &readfds);
						pNew = (onlinelist *)malloc(sizeof(onlinelist));
						pNew->sock = cli_fd;
						strcpy(pNew->ip, inet_ntoa(cli_addr.sin_addr));
						add_tial(pHead, pNew, onlinelist);
						cli_count++;
					}
					else{
						memset(&buf,0,sizeof(buf));
						recv_count = recv(pTemp->sock, &buf, sizeof(buf),0);
						if (recv_count == 0){
							cli_count--;
							close(pTemp->sock);
							FD_CLR(pTemp->sock,&readfds);
							userlogout_sev(pTemp->id, pTemp->ip);
							pTar = pTemp;	pTemp = pTemp->pNext;
							del_node(pHead, pTar, onlinelist);
							if (pTemp == NULL)
								break;
						}
						else{
							analyzedatapack(&buf, pTemp->sock, pTemp->ip, pHead, pTemp);
						}
					}
				}
				pTemp = pTemp->pNext;
			}
		}
	}

	close(sev_fd);

	//关闭服务,添加系统日志
	ifo = "The server is close";
	add_syslog_sev(ifo);

	return EXIT_SUCCESS;
}
