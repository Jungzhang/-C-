/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-08 15:07
 * Filename	 : log_sev.h
 * Description	 : 日志操作接口
 * *****************************************************************************/

#ifndef LOG_SEV_H_
#define LOG_SEV_H_

//添加错误日志
int add_errorlog_sev(char ifo[]);

//添加系统日志
int add_syslog_sev(char ifo[]);

//添加登录 or 登出日志
int add_lognlog_sev(unsigned int userid, char ip[], char ifo[]);

#endif
