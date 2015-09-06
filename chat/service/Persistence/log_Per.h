/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-08 15:47
 * Filename	 : log_Per.h
 * Description	 : 日志写入文件的相关操作头文件
 * *****************************************************************************/
#ifndef LOG_PER_H_
#define LOG_PER_H_

//添加错误日志
int add_errorlog_Per(char ifo[], char time[]);

//添加系统日志到文件
int add_syslog_Per(char ifo[], char time[]);

#endif
