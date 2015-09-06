/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-07 13:54
 * Filename	 : id.c
 * Description	 : ID相关操作,负责注册账号和新建群时的分配ID
 * *****************************************************************************/
#include "id_sev.h"
#include "../Persistence/id_Per.h"
#include <stdio.h>
#include "log_sev.h"

//返回当前最大用户ID,若不存在则返回0
inline int sev_find_userid(void)
{
	return Per_find_userid();
}

//分配一个用户ID
int sev_distri_userid(void)
{
	unsigned int new_id = sev_find_userid();
	char ifo[32] = {"The User ID can not write file"};
	if (new_id != 0){
		new_id++;
	}
	else{
		new_id = 10000;
	}
	if (Per_add_userid(new_id) == 0){
		add_errorlog_sev(ifo);
		return 0;
	}

	return new_id;
}

//返回当前最大群ID,若不存在则返回0
inline int sev_find_groupid(void)
{
	return Per_find_groupid();
}

//分配一个群ID
int sev_distri_groupid(void)
{
	unsigned int new_id = sev_find_groupid();
	char ifo[32] = {"The Group ID can not write file"};
	if (new_id != 0){
		new_id++;
	}
	else{
		new_id = 50000;
	}
	if (Per_add_groupid(new_id) == 0)
		add_errorlog_sev(ifo);

	return new_id;
}
