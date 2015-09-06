/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-08 14:32
 * Filename	 : log_Per.c
 * Description	 : 日志相关的写入文件操作
 * *****************************************************************************/
#include <stdio.h>
#include "../Common/common.h"
#include "log_Per.h"

static const char ERROR_FILE[] = "errno.log";
static const char SYSLOG_FILE[] = "system.log";
static const char LOGNLOG_FILE[] = "logn.log";

//添加错误日志到文件
int add_errorlog_Per(char ifo[], char time[])
{
	FILE *fp;
	char *path = get_pwd();
	if (chdir("/var/log/") == -1)
		return 0;
	if (chdir("chat") == -1){
		system("mkdir chat");
		if (chdir("chat") == -1){
			chdir(path);
			return 0;
		}
	}
	fp = fopen(ERROR_FILE, "a+");
	if (fp == NULL){
		chdir(path);
		return 0;
	}
	fprintf(fp,"%s  %s\n",ifo,time);
	fclose(fp);
	chdir(path);
	return 1;
}

//添加系统日志到文件
int add_syslog_Per(char ifo[], char time[])
{
	FILE *fp;
	char *path = get_pwd();
	
	if (chdir("/var/log/") == -1)
		return 0;
	if (chdir("chat") == -1){
		system("mkdir chat");
		if (chdir("chat") == -1){
			chdir(path);
			return 0;
		}
	}
	fp = fopen(SYSLOG_FILE, "a+");
	if (fp == NULL){
		chdir(path);
		return 0;
	}
	fprintf(fp,"%s  %s\n",ifo,time);
	fclose(fp);
	chdir(path);
	
	return 1;
}

//添加登录 or 登出日志到文件
int add_lognlog_Per(unsigned int userid, char ip[], char ifo[], char time[])
{
	FILE *fp;
	char *path = get_pwd();
	
	if (chdir("/var/log/") == -1)
		return 0;
	if (chdir("chat") == -1){
		system("mkdir chat");
		if (chdir("chat") == -1){
			chdir(path);
			return 0;
		}
	}
	fp = fopen(LOGNLOG_FILE, "a+");
	if (fp == NULL){
		chdir(path);
		return 0;
	}
	fprintf(fp,"%u  %s  %s  %s\n",userid, ifo, ip, time);
	fclose(fp);
	chdir(path);
	
	return 1;
	
}
