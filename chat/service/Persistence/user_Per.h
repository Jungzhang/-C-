/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-10 10:25
 * Filename	 : user_Per.h
 * Description	 : 用户相关文件操作的函数声明
 * *****************************************************************************/
#include "../Server/user_sev.h"

#ifndef USER_PER_H_
#define USER_PER_H_

//将新注册用户的信息保存进文件,并建立该账号的列表文件
int  save_userifo_Per(userifo *user);

//从文件里通过ID获取账号信息
int selectuserid_Per(unsigned int userid, userifo *user);

//向userid所指的列表文件中添加好友或群组
int add_friend_Per(unsigned int userid, userlist *newfriend);

//删除userid列表文件中的friendid好友或群组
int del_friend_Per(unsigned int friendid, unsigned int userid);

//修改好友备注
int update_friend_Per(unsigned int userid, unsigned int friendid, char name[], int type);

//寻找friendid是否在列表中
int finduser_Per(unsigned int userid, unsigned int friendid, int type, userlist *data);

#endif
