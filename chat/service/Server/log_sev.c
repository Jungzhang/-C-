/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-08 14:15
 * Filename	 : log_sev.c
 * Description	 : 所有的日志写入接口
 * *****************************************************************************/
#include <stdio.h>
#include "../Common/common.h"
#include "log_sev.h"
#include "../Persistence/log_Per.h"

//添加错误日志
int add_errorlog_sev(char ifo[])
{
	char now_time[25];
	date_now(now_time);
	if (add_errorlog_Per(ifo, now_time) == 0){
		return 0;
	}

	return 1;
}

//添加系统日志
int add_syslog_sev(char ifo[])
{
	char now_time[25];
	date_now(now_time);
	if (add_syslog_Per(ifo, now_time) == 0){
		return 0;
	}

	return 1;
}

//添加登录 or 登出日志
int add_lognlog_sev(unsigned int userid, char ip[], char ifo[])
{
	char now_time[25];
	date_now(now_time);
	if (add_lognlog_Per(userid, ip, ifo, now_time) == 0){
		return 0;
	}

	return 1;
}
