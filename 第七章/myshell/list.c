/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-07-21 15:26
 * Filename	 : list.c
 * Description	 : myshell程序所用到的存储命令行参数的相关链表操作
 * *****************************************************************************/

#include <stdlib.h>
#include "list.h"

//创建链表
void creat(arglist_t *pHead) 									
{														
	pHead = (arglist_t *)malloc(sizeof(arglist_t));		
	pHead->pNext = NULL;							
}														

//释放链表
void freelist(arglist_t *pHead)
{														
	arglist_t *pTemp1,*pTemp2;
	pTemp1 = pHead->pNext;
	pTemp2 = pHead->pNext;
	while(pTemp2 != NULL)								
	{													
		pTemp2 = pTemp1->pNext;							
		free(pTemp1);									
		pTemp1 = pTemp2;								
	}													
	pHead->pNext = NULL;								
}
//销毁链表
void destroy(arglist_t *pHead)					
{														
	freelist(pHead);									
	free(pHead);										
}														

//尾插节点
void add(arglist_t *pHead,arglist_t *pNew)
{														
	arglist_t *pTail = pHead;							
	while(pTail->pNext != NULL)							
		pTail = pTail->pNext;							
	pTail->pNext = pNew;								
	pNew->pNext = NULL;									
}
