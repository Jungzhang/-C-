/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-11 17:26
 * Filename	 : message.c
 * Description	 : 数据包的解析及执行相关命令
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "message.h"
#include "../Common/common.h"
#include "../Common/list.h"
#include "../Server/group_sev.h"
#include "../Server/id_sev.h"
#include "../Server/logn_sev.h"
#include "../Server/log_sev.h"
#include "../Server/user_sev.h"

//数据包的解析,并执行相应的命令,传给客户端
int analyzedatapack(datapack *buf, int sock, char ip[], onlinelist *pHead, onlinelist *pNode)
{
	if ((buf->source_id == 0) && (buf->target_id == 0)){
		//源ID和目标如果为都0,flag为sign up时表示注册用户
		if (strcmp(buf->flag, "sign up") == 0){
			int i = 0,j = 0;
			char name[16];
			char passwd[32];
			unsigned int userid;
			for (i = 0; buf->data[i] != '\n'; i++){
				name[i] = buf->data[i];
			}
			name[i] = '\0';
			i++;
			while(buf->data[i] != '\0'){
				passwd[j] = buf->data[i] - 1;
				i++;	j++;
			}
			passwd[j] = '\0';
			if ((userid = signup_sev(name, passwd)) > 0){
				strcpy(buf->flag, "sign up yes");
				strcpy(buf->data,"恭喜您注册成功,您的账号为:");
				sprintf(name, "%u", userid);
				strcat(buf->data, name);
				strcat(buf->data, "\n请您牢记您的账号和密码(打死也不要将密码告诉别人呦~~)\n");
			}
			else{
				strcpy(buf->data, "亲~~现在系统繁忙,请您稍后重试~~\n");
			}
		}
		//登录
		else if (strcmp(buf->flag, "logn in") == 0){
			int i = 0,j = 0;
			char user[16];
			char passwd[32];
			unsigned int userid;
			for (i = 0; buf->data[i] != '\n'; i++){
				user[i] = buf->data[i];
			}
			user[i] = '\0';
			i++;
			while(buf->data[i] != '\0'){
				passwd[j] = buf->data[i] - 1;
				j++;	i++;
			}
			passwd[j] = '\0';
			userid = atoi(user);
			if (userlognin_sev(userid, passwd, ip) <= 0){
				strcpy(buf->data, "亲~~您的账号或者密码错了呦~~\n");
			}
			else{
				pNode->id = userid;
				buf->source_id = userid;
				strcpy(buf->flag, "logn in yes");
				strcpy(buf->data, "登陆成功,正在努力跳转~~\n");
			}
		}
	}
	else if ((buf->source_id > 0) && (buf->target_id > 0)){
		//私聊
		if (strcmp(buf->flag, "user") == 0){
			int flag = 0;
			userlist my_friend;
			onlinelist *pTemp = pHead->pNext->pNext;
			//检查对方是否为好友
			if (finduser_sev(buf->source_id, buf->target_id, 0, &my_friend) == 0){
				strcpy(buf->data, "您输入的用户暂时还不是您的好友哦~~\n");
				strcpy(buf->name,"\0");
				strcpy(buf->flag, "no");
			}
			else{
				//在对方列表中查找发消息人的备注
				if (finduser_sev(buf->target_id, buf->source_id, 0, &my_friend)){
					strcpy(buf->name, my_friend.name);
				}
				while(pTemp != NULL){
					if (pTemp->id == buf->target_id){
						sock = pTemp->sock;
						flag = 1;
					}
					pTemp = pTemp->pNext;
				}
			
				//不在线则发送失败
				if (flag == 0){
					strcpy(buf->data, "您发送的用户不在线,请您稍后重试~~\n");
					strcpy(buf->name,"\0");
					strcpy(buf->flag, "no");
				}
				else{
					strcpy(buf->flag,"useryes");
				}
			}
		}	//群聊
		else if (strcmp(buf->flag, "group") == 0){
			userlist my_friend,newuser;
			onlinelist *pTemp = pHead->pNext->pNext;
			//检查是否加群
			if (finduser_sev(buf->source_id, buf->target_id, 1, &my_friend) <= 0){
				strcpy(buf->flag, "no");
				strcpy(buf->data, "您暂时还未加此群哦~~\n");
				send(sock, buf, sizeof(datapack), 0);
				return 0;
			}
			else{
				//在消息中打上标签(来自哪个群的×××)
				strcpy(buf->name, "群:");
				strcat(buf->name, my_friend.name);
				if (finduser_sev(buf->target_id, buf->source_id, 0, &my_friend)){
					strcat(buf->name, "  成员:");
					strcat(buf->name, my_friend.name);
				}
				//在在线用户列表里找寻是否在群里,如果在则发送
				while(pTemp != NULL){
					if (finduser_sev(pTemp->id, buf->target_id, 1, &newuser) == 1){
						send(pTemp->sock, buf, sizeof(datapack), 0);
					}
					pTemp = pTemp->pNext;
				}
			}
			return 1;
		}	//加好友
		else if (strcmp(buf->flag, "addfriend") == 0){
			int result;
			result = add_friend_sev(buf->source_id, buf->target_id);
			if (result == 1){
				strcpy(buf->data,"添加成功,现在可以和对方聊天了~~\n");
			}
			else if(result == 0){
				strcpy(buf->data, "未找到用户,请查证后再来~~\n");
			}
			else if (result == -1){
				strcpy(buf->data, "系统繁忙,请稍后再来~~\n");
			}
			else if (result == 2){
				strcpy(buf->data, "好友已存在\n");
			}
		}	//加群
		else if (strcmp(buf->flag, "addgroup") == 0){
			int result;
			result = joingroup_sev(buf->source_id,buf->target_id);
			if (result == 1){
				strcpy(buf->data,"添加成功,现在进入群组聊天了~~\n");
			}
			else if(result == 0){
				strcpy(buf->data, "未找到群组,请查证后再来~~\n");
			}
			else if (result == -1){
				strcpy(buf->data, "系统繁忙,请稍后再来~~\n");
			}
			else if (result == 2){
				strcpy(buf->data, "已加该群\n");
			}
		}	//退群
		else if (strcmp(buf->flag, "quitgroup") == 0){
			int result = quitgroup_sev(buf->source_id, buf->target_id);
			if (result == 0){
				strcpy(buf->data, "您还没有加该群,无法退出~~\n");
			}
			else if (result == -1){
				strcpy(buf->data, "系统繁忙,请稍后重试=、=\n");
			}
			else if (result == 1){
				strcpy(buf->data, "退群成功~~\n");
			}
		}	//建群
		else if (strcmp(buf->flag, "bulidgroup") == 0){
			char num[12];
			unsigned int result = buildgroup_sev(buf->source_id, buf->data);
			if (result == 0){
				strcpy(buf->data, "系统繁忙,请稍后重试=、=\n");
			}
			else{
				strcpy(buf->data, "创建成功,群号码为:");
				sprintf(num, "%d", result);
				strcat(buf->data, num);
			}
		}	//解散群
		else if (strcmp(buf->flag, "delgroup") == 0){
			int result = delgroup_sev(buf->target_id, buf->source_id);
			if (result == -1){
				strcpy(buf->data, "系统繁忙,解散群失败,请稍后重试=、=\n");
			}
			else if (result == 0){
				strcpy(buf->data, "该群不存在\n");
			}
			else if (result == 2){
				strcpy(buf->data, "您不是该群群主，没有解散该群的权限\n");			
			}
			else{
				strcpy(buf->data, "解散群成功\n");
			}
		}	//删除好友
		else if (strcmp(buf->flag, "delfriend") == 0){
			int result = del_friend_sev(buf->target_id, buf->source_id);
			if (result == 0){
				strcpy(buf->data, "您删除的用户还不是您的好友或用户不存在\n");
			}
			else if (result == -1){
				strcpy(buf->data, "系统繁忙,请稍后重试=、=\n");
			}
			else if (result == 1){
				strcpy(buf->data, "删除成功\n");
			}
		}	//获取群成员列表
		else if (strcmp(buf->flag, "selectgroup") == 0){
			char temp[64];
			int result = glancelist_sev(buf->source_id, buf->target_id, sock);
			if (result == -1){
				strcpy(temp, "系统繁忙,请稍后重试=、=\n");
				send(sock, temp, strlen(temp), 0);
				return -1;
			}
			else if (result == 0){
				strcpy(temp, "您还没有加入此群,无法查看群成员\n");
				send(sock, temp, strlen(temp), 0);
				return 0;
			}
			else{
				return 1;
			}
		}	//获取好友列表
		else if (strcmp(buf->flag, "selcetfriend") == 0){
			char temp[32];
			int result = glancelist_sev(buf->source_id, 0, sock);
			if (result == -1){
				strcpy(temp, "系统繁忙,请稍后重试=、=\n");
			}
			else if (result == 0){
				strcpy(temp, "您还没有任何好友~~\n");
			}
			else{
				return 1;
			}
			send(sock, temp, strlen(temp), 0);
			return 0;
		}	//获取在线好友列表
		else if (strcmp(buf->flag, "onlinefriend") == 0){
			userlist dat;
			char num[16];
			onlinelist *pTemp = pHead->pNext->pNext;
			while(pTemp != NULL){
				if (finduser_sev(buf->source_id, pTemp->id, 0, &dat) == 1){
					strcpy(buf->data, dat.name);
					sprintf(num, "%d", dat.id);
					strcat(buf->data, "    ");
					strcat(buf->data, num);
					send(sock, buf, sizeof(datapack), 0);
				}
				pTemp = pTemp->pNext;
			}
			buf->target_id = 0;
			send(sock, buf, sizeof(datapack), 0);
			return 1;
			
		}	//修改好友备注
		else if (strcmp(buf->flag, "renamefriend") == 0){
			if (update_friend_sev(buf->source_id, buf->target_id, buf->data) == 1){
				strcpy(buf->data, "修改成功\n");
			}
			else{
				strcpy(buf->data, "修改失败,可能是该好友不存在~~\n");
			}
		}	//修改群备注
		else if (strcmp(buf->flag, "renamegroup") == 0){
			if (update_groupname_sev(buf->target_id, buf->source_id, buf->data) == 1){
				strcpy(buf->data, "修改成功\n");
			}
			else{
				strcpy(buf->data, "修改失败,可能您还没有加入该群~~\n");
			}
		}
	}
	
	send(sock, buf, sizeof(datapack), 0);
}
