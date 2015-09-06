/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-14 19:46
 * Filename	 : main.c
 * Description	 : 客户端主文件
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include "uppack.h"
#include "menu.h"

int main(void)
{
	int sock;
	int key,key1; //选项
	datapack buf; //数据包
	struct sockaddr_in addr;

	sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock < 0){
		perror("Socket Error");	return EXIT_FAILURE;
	}
	//初始化网络IP
	addr.sin_family = AF_INET;	//IPv4
	addr.sin_port = htons(2489);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(addr.sin_zero,0,sizeof(addr.sin_zero));
	//连接
	if (connect(sock,(struct sockaddr *)&addr,sizeof(struct sockaddr_in)) == -1){
		perror("Connect Error");	return EXIT_FAILURE;
	}

loop:	//开始菜单选择
	printf("\033c");
	start_menu();
	setbuf(stdin,NULL);
	scanf("%d",&key);
	switch (key){
		case 1:  	//登录
			buf.source_id = lognin_sev(sock);
			sleep(1);	break;
		case 2:		//注册
			signup_sev(sock);
			sleep(2);
			goto loop;
		case 0:		//退出
			exit(0);
		default:	//选择有误
			printf("您的选择有误,请重新选择\n");
			sleep(1);
			goto loop;
	}
loop1:	//主菜单选择
	printf("\033c");
	main_menu();
	setbuf(stdin,NULL);
	scanf("%d",&key);
	switch(key){
		case 1:		//聊天
		loop2:printf("\033c");	
			chat_menu();
			setbuf(stdin, NULL);
			scanf("%d",&key1);
			switch(key1){
				case 1:		//私聊
					chatuser(&buf, sock);
					goto loop2;
					break;
				case 2:		//群聊
					chatgroup(&buf, sock);
					goto loop2;
					break;
				case 0:		//退出
					exit(0);
				case 9:		//返回
					goto loop1;
				default:
					goto loop2;
			}
			break;
		case 2:		//管理
		loop3:printf("\033c");
			manage_menu();
			setbuf(stdin, NULL);
			scanf("%d", &key1);
			switch(key1){
				case 1:		//加群
					joingroup(&buf, sock);	break;
				case 2:		//退群
					quitgroup(&buf, sock);	break;
				case 3:		//改群备注
					renamgroup(&buf, sock);	break;
				case 4:		//建群
					bulidgroup(&buf, sock);	break;
				case 5:		//解散群
					delgroup(&buf, sock);	break;
				case 6:		//加好友
					addnewfriend(&buf, sock);	break;
				case 7:		//删除好友
					delfriend(&buf, sock);	break;
				case 8:		//改好友备注
					renamefriend(&buf, sock);	break;
				case 9:		//返回
					goto loop1;
				case 0:		//退出
					exit(0);
				default:
					goto loop3;
			}
			printf("输入Enter键继续。。。");
			setbuf(stdin, NULL);
			getchar();
			goto loop3;
		case 3:		//获取
		loop4:printf("\033c");
			select_menu();
			setbuf(stdin, NULL);
			scanf("%d", &key1);
			switch(key1){
				case 1:		//所有好友列表
					selcetfriend(&buf, sock);	break;
				case 2:		//在线好友列表
					selcetonlie(&buf, sock);	break;
				case 3:		//群成员列表
					selcetgroup(&buf, sock);	break;
				case 4:		//获取聊天记录
					selecthistory(buf.source_id);	break;
				case 9:		//返回
					goto loop1;
				case 0:		//退出
					exit(0);
				default:
					goto loop4;
			}
			printf("输入Enter键继续。。。");
			setbuf(stdin,NULL);
			getchar();
			goto loop4;
		case 0:		//退出
			exit(0);
		default:	//其他
			goto loop1;
	}
	return EXIT_SUCCESS;
}
