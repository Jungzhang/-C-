/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-10 09:50
 * Filename	 : group_Per.h
 * Description	 : 群相关文件操作的函数声明
 * *****************************************************************************/
#ifndef GROUP_PER_H_
#define GROUP_PER_H_
#include "../Server/group_sev.h"

//保存新创建群进文件,并创建群列表文件
int  save_groupifo_Per(groupifo *group);

//解散群
int delgroup_Per(unsigned int groupid, unsigned int master);

#endif
