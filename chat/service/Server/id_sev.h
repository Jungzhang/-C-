/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-07 13:53
 * Filename	 : id.h
 * Description	 : 定义ID数据类型和ID相关操作的函数声明
 * *****************************************************************************/
#ifndef ID_SEV_H_
#define ID_SEV_H_

//ID类型
typedef struct id{
	char type[16];
	unsigned int id;
}ID;

//ID结点类型
typedef struct id_node{
	ID id;
	struct id_node *pNext;
}ID_NODE;

#endif
