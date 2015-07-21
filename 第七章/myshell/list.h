/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-21 15:26
 * Filename	 : list.h
 * Description	 : myshell程序所用到的存储命令行参数的数据结构及其操作
 * *****************************************************************************/

#include <stdlib.h>

//存储命令行参数的数据结构
typedef struct arglist_node{

	char arg[256];
	struct arglist_t *pNext;

}arglist_t;

//创建链表
#define creat(pHead) 									\
{														\
	pHead = (arglist_t *)malloc(sizeof(arglist_t));		\
	pHead->pNext = NULL;								\
}														

//释放链表
#define freelist(pHead)									\
{														\
	arglist_t *pTemp1,*pTemp2;							\
	pTemp1 = pTemp2 = pHead->pNext;						\
	while(pTemp2 != NULL)								\
	{													\
		pTemp2 = pTemp1->pNext;							\
		free(pTemp1);									\
		pTemp1 = pTemp2;								\
	}													\
	pHead->pNext = NULL;								\
}

//销毁链表
#define destroy(pHead)									\
{														\
	freelist(pHead);									\
	free(pHead);										\
}														\

//尾插节点
#define add(pHead,pNew)									\
{														\
	arglist_t *pTail = pHead;							\
	while(pTail->pNext != NULL)							\
		pTail = pTail->pNext;							\
	pTail->pNext = pNew;								\
	pNew->pNext = NULL;									\
}														\
