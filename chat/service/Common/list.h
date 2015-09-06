/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-07 13:54
 * Filename	 : list.h
 * Description	 : 链表相关操作
 * *****************************************************************************/
#include <stdlib.h>

//创建一个链表,传进来头指针和结点类型
#define list_creat(pHead, node_type){						\
	pHead = (node_type *)malloc(sizeof(node_type));	\
	(pHead)->pNext = NULL;							\
}

//尾插一个结点,传进来头结点和新结点
#define add_tial(pHead,new_node, node_type){	\
	node_type *pTemp1 = pHead;				\
	while(pTemp1 ->pNext != NULL)	\
		pTemp1 = pTemp1->pNext;		\
	(pTemp1)->pNext = new_node;		\
	(new_node)->pNext = NULL;			\
}

//删除一个结点,传进来头结点和待删除结点,结点类型
#define del_node(pHead,node,nodetype){		\
	nodetype *pTemp2;		\
	nodetype *pTar1;		\
	pTemp2 = pHead;			\
	while((pTemp2 != NULL) && (pTemp2->pNext != node)){	\
		pTemp2 = pTemp2->pNext;	\
	}\
	pTar1 = pTemp2->pNext;	\
	pTemp2->pNext = pTar1->pNext;	\
	free(pTar1);		\
}

//释放链表
#define list_free(pHead, node_type){	\
	node_type *pTemp3;	\
	node_type *pTemp4;	\
	pTemp4 = pTemp3 = pHead->pNext;		\
	while(pTemp3 != NULL){			\
		pTemp3 = pTemp4->pNext;	\
		free(pTemp4);	\
		pTemp4 = pTemp3;	\
	}\
	pHead->pNext = NULL;	\
}

//销毁链表
#define list_destroy(pHead, node_type){	\
	list_free(pHead, node_type);	\
	free(pHead);	\
}
