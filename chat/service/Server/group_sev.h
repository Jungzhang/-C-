/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-10 09:37
 * Filename	 : group_sev.h
 * Description	 : 群操作所用的数据结构和函数声明
 * *****************************************************************************/
#ifndef GROUP_SEV_H_
#define GROUP_SEV_H_

//群组信息数据结构
typedef struct groupifo{
	char name[32];		//群组名称
	unsigned int userid;			//所属者ID
	unsigned int groupid;		//群组ID
}groupifo;


//创建群
unsigned int buildgroup_sev(unsigned int userid, char name[]);

//解散群
inline int delgroup_sev(unsigned int groupid, unsigned int master);

#endif
