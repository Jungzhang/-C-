/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-09-17 19:41
 * Filename	 : split.c
 * Description	 : 链表拆分,以第一个结点为基准,将大于的放后边,小于的放前边
 * *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	
	int num;
	struct node *pNext;
	
}NODE;


//链表的初始化
NODE *InitList(void)
{
	NODE *pHead;
	if ((pHead = (NODE *)malloc(sizeof(NODE))) == NULL){
		exit(-1);
	}
	pHead->pNext = NULL;

	return pHead;
}

//链表的创建
void CreatList(NODE *pHead, int n)
{
	NODE *pNew, *pTail;
	int i;

	pTail = pHead;
	for (i = 0; i < n; i++){
		if ((pNew = (NODE *)malloc(sizeof(NODE))) == NULL){
			exit(-1);
		}
		printf("请输入第%d个结点的值 = ", i + 1);
		scanf("%d", &pNew->num);
		pTail->pNext = pNew;
		pTail = pNew;
	}
	pNew->pNext = NULL;
}


//链表的输出
void ShowList(NODE *pHead)
{
	NODE *pTemp = pHead->pNext;
	while(pTemp != NULL){
		printf("%5d", pTemp->num);
		pTemp = pTemp->pNext;
	}
	printf("\n");
}

//链表的拆分
void SplitList(NODE *pHead)
{
	NODE *pStan, *pTar, *pTemp;
	if ((pStan = pHead->pNext) == NULL)
		return ;
	pTar = pStan->pNext;
	pStan->pNext = NULL;
	while(pTar != NULL){
		pTemp = pTar->pNext;
		if (pTar->num < pStan->num){
			pTar->pNext = pHead->pNext;
			pHead->pNext = pTar;
		}
		else{
			pTar->pNext = pStan->pNext;
			pStan->pNext = pTar;
		}
		pTar = pTemp;
	}

}


int main(void)
{
	NODE *pHead = InitList();
	int n;
	printf("请输入n = ");
	scanf("%d", &n);
	CreatList(pHead, n);
	ShowList(pHead);
	SplitList(pHead);
	ShowList(pHead);

	
	return 0;
}
