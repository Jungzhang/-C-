/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-22 09:32
 * Filename	 : list.h
 * Description	 : 存储命令行参数的数据结构
 * *****************************************************************************/

typedef struct arglist_node{

	char arg[256];
	struct arglist_node *pNext;

}arglist_t;
