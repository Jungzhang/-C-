/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-10 10:04
 * Filename	 : user_sev.h
 * Description	 : 用户数据结构和函数声明
 * *****************************************************************************/
#ifndef USER_SEV_H_
#define USER_SEV_H_

//用户信息数据结构
typedef struct userifo{
	char name[16];		//用户昵称
	char passwd[32];	//用户密码
	unsigned int id;				//用户ID
}userifo;

//用户列表数据结构
typedef struct userlist{
	char name[16];
	int type;				//标识是好友还是群
	unsigned int id;
}userlist;

//注册账号
unsigned int signup_sev(char name[], char passwd[]);

//添加好友
int add_friend_sev(unsigned int userid, unsigned int friendid);

//删除好友,成功返回1,出错返回-1,好友不存在返回0
int del_friend_sev(unsigned int friendid, unsigned int userid);

//修改好友备注
int update_friend_sev(unsigned int friendid, unsigned int userid, char name[]);

//修改群名片
int update_groupname_sev(unsigned int groupid, unsigned int userid, char name[]);

//从列表文件中找寻friendid是否存在
inline int finduser_sev(unsigned int userid, unsigned int friendid, int type, userlist *data);

#endif
