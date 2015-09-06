/****************************************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-10 09:53
 * Filename	 : user_sev.c
 * Description	 : 用户的注册、加好友、删除好友、修改好友备注、修改群名片、查看好友列表和群列表
 ***************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "../Persistence/user_Per.h"
#include "log_sev.h"

//在userid文件中寻找friendid并存入data
inline int finduser_sev(unsigned int userid, unsigned int friendid, int type, userlist *data)
{
	int result;
	char *ifo;
	result = finduser_Per(userid, friendid, type, data);
	if (result == -1){
		ifo = "The file can not open!";
		add_errorlog_sev(ifo);
	}

	return result;
}

//注册账号
unsigned int signup_sev(char name[], char passwd[])
{
	userifo user;
	char info[80];
	char a[20];
	unsigned int userid = sev_distri_userid();
	if (userid == 0){
		strcpy(info, "The new user can not distribution user id");
		add_errorlog_sev(info);
		return 0;
	}
	//将传进来的昵称和密码存进结构体并保存进文件
	user.id = userid;
	strcpy(user.name, name);
	strcpy(user.passwd, passwd);
	if (save_userifo_Per(&user) == 0){
		strcpy(info, "The new user can not save info");
		add_errorlog_sev(info);
		return 0;
	}
	strcpy(info, "The new user sign up   ");
	sprintf(a, "%d", userid);
	strcat(info, a);
	add_syslog_sev(info);
	return userid;
}

//添加好友,出错返回-1,已存在返回2,成功返回1,未找到返回0
int add_friend_sev(unsigned int userid, unsigned int friendid)
{
	userifo user;
	userlist newfriend;
	char *ifo;
	int result = selectuserid_Per(friendid, &user);
	
	//自己列表中添加好友
	if (result == -1){
		ifo = "Can not open the user.dat";
		add_errorlog_sev(ifo);
		return -1;
	}
	if (result == 0){
		return 0;
	}
	if (finduser_sev(userid, friendid, 0, &newfriend) == 1){
		return 2;
	}
	strcpy(newfriend.name, user.name);
	newfriend.type = 0;	//表示为好友
	newfriend.id = friendid;
	if (add_friend_Per(userid, &newfriend) == 0){
		ifo = "Can not save the info of friend";
		add_errorlog_sev(ifo);
		return -1;
	}
	//被添加用户列表中添加自己
	result = selectuserid_Per(userid, &user);
	if (result == -1){
		ifo = "Can not open the data";
		add_errorlog_sev(ifo);
		return -1;
	}
	if (result == 0){
		return 0;
	}
	strcpy(newfriend.name, user.name);
	newfriend.type = 0;	//表示为好友
	newfriend.id = userid;
	if (add_friend_Per(friendid, &newfriend) == 0){
		ifo = "Can not save the info of friend";
		add_errorlog_sev(ifo);
		return -1;
	}

	return 1;
}

//删除好友,成功返回1,出错返回-1,好友不存在返回0
int del_friend_sev(unsigned int friendid, unsigned int userid)
{
	char *ifo;
	int result;
	//自己列表中删除好友
	result = del_friend_Per(friendid, userid);
	if (result == -1){
		ifo = "Can not open the file of user_list.dat";
		return -1;
	}
	if (result == 0){
		return 0;
	}
	//好友列表中删除自己
	result = del_friend_Per(userid, friendid);
	if (result == -1){
		ifo = "Can not open the file of user_list.dat";
		return -1;
	}
	if (result == 0){
		return 0;
	}

	return 1;
}

//修改好友备注
int update_friend_sev(unsigned int userid, unsigned int friendid, char name[])
{
	char *ifo;
	int result = update_friend_Per(userid, friendid, name, 0);
	
	if (result == -1){
		ifo = "Can not open the file of user_list.dat";
		add_errorlog_sev(ifo);
		return -1;
	}
	if (result == 0){
		return 0;
	}

	return 1;
}

//修改群名片
int update_groupname_sev(unsigned int groupid, unsigned int userid, char name[])
{
	char *ifo;
	int result = update_friend_Per(groupid, userid, name, 0);

	if (result == -1){
		ifo = "Can not open the file of group_list.dat";
		add_errorlog_sev(ifo);
		return -1;
	}
	else if (result == 0){
		return 0;
	}

	return 1;
}

//查看好友列表和群列表,查看好友列表时第二个参数为0
inline int glancelist_sev(unsigned int userid, unsigned int groupid, int sock)
{
	return glancelist_Per(userid, groupid, sock);
}
