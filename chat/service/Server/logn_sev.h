/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-08 17:01
 * Filename	 : logn_sev.h
 * Description	 : 用户登录、退出函数和数据结构
 * *****************************************************************************/
#ifndef LOGN_SEV_H_
#define LOGN_SEV_H_

//登录接口,验证成功返回1,密码错误返回2,错误返回-1,id不存在返回0
int userlognin_sev(unsigned int userid, char passwd[], char ip[]);

//账号登出
inline int userlogout_sev(unsigned int userid, char ip[]);

#endif
