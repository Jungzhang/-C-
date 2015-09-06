/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-08 16:22
 * Filename	 : logn_sev.c
 * Description	 : 用户登录和登出
 * *****************************************************************************/
#include "log_sev.h"
#include "user_sev.h"
#include <string.h>
#include "logn_sev.h"
#include "../Persistence/user_Per.h"

//登录接口,验证成功返回1,密码错误返回0,错误返回-1,id不存在返回0
int userlognin_sev(unsigned int userid, char passwd[], char ip[])
{
	userifo user;
	char *ifo;
	int result = selectuserid_Per(userid, &user);
	if (result == 0){
		return 0;
	}
	else if (result == -1){
		ifo = "The userlist.dat can not open";
		add_errorlog_sev(ifo);
		return -1;
	}
	if ((user.id == userid) && (strcmp(passwd, user.passwd) == 0)){
		ifo = "Lon in";
		if (add_lognlog_sev(userid, ip, ifo) == 0){
			ifo = "Can not add lognlog of Log In";
			add_errorlog_sev(ifo);
			return -1;
		}
		return 1;
	}
	else{
		return 0;
	}

	return -1;
}

//账号登出
inline int userlogout_sev(unsigned int userid, char ip[])
{
	char *ifo = "Log out";

	if (add_lognlog_sev(userid, ip, ifo) == 0){
		ifo = "Can not add lognlog of Log Out";
		add_errorlog_sev(ifo);

		return -1;
	}
	
	return 1;
}
