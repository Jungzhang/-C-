/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-10 09:32
 * Filename	 : group_sev.c
 * Description	 : 创建群、查找群、加群、退群、解散群
 * *****************************************************************************/
#include <string.h>
#include "log_sev.h"
#include "../Persistence/group_Per.h"
#include "user_sev.h"
#include <stdio.h>
#include "group_sev.h"

//创建群
unsigned int buildgroup_sev(unsigned int userid, char name[])
{
	groupifo group;
	char *info;
	unsigned int groupid = sev_distri_groupid();
	if (groupid == 0){
		info = "The new group can not distribution group id";
		add_errorlog_sev(info);
		return 0;
	}
	//将传进来的群名称和所属者ID存进结构体并保存进文件
	group.userid = userid;
	group.groupid = groupid;
	strcpy(group.name, name);
	if (save_groupifo_Per(&group) == 0){
		info = "The new group can not save info";
		add_errorlog_sev(info);
		return 0;
	}
	if (joingroup_sev(userid, groupid) !=  1){
		info = "Can not add new friend to group";
		add_errorlog_sev(info);
		return 0;
	}

	return groupid;
}

//获取群信息
inline int selectgroup_sev(unsigned int groupid, groupifo *group)
{
	char *info;
	int result = selectgroup_Per(groupid, group);
	if (result == -1){
		info = "Can not select groupinfo";
		add_errorlog_sev(info);
	}
	
	return result;
}

//解散群
inline int delgroup_sev(unsigned int groupid, unsigned int master)
{
	char *ifo;
	int result;
	result = delgroup_Per(groupid, master);
	if (result == -1){
		ifo = "Can not del the group form grouplist.dat";
		add_errorlog_sev(ifo);
	}
	
	return result;
}

//加群,错误返回-1,成功返回1,失败返回0,已加过该群返回2
int joingroup_sev(unsigned int userid, unsigned int groupid)
{
	char *ifo;
	userlist newgroup,newuser;
	userifo user;
	groupifo group;
	int result = selectgroup_sev(groupid, &group);
	if (result == -1){
		return -1;
	}
	else if (result == 0){
		return 0;
	}
	if (finduser_sev(userid, groupid, 1, &newuser) == 1){
		return 2;
	}
	newgroup.id = group.groupid;
	strcpy(newgroup.name, group.name);
	newgroup.type = 1;
	//根据用户ID提取用户信息
	selectuserid_Per(userid, &user);
	newuser.id = user.id;
	strcpy(newuser.name, user.name);
	newuser.type = 0;
	//添加群进用户好友列表
	if (add_friend_Per(userid, &newgroup) != 1)
		return 0;
	//添加用户进群的用户列表
	if (add_friend_Per(groupid, &newuser) != 1)
		return 0;

	return 1;
}

//退群,成功返回1,错误返回-1,群不存在或未加群返回0
inline int quitgroup_sev(unsigned int userid, unsigned int groupid)
{
	return del_friend_sev(groupid, userid);
}

