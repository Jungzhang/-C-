#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int num;
	struct node *pNext;
}NODE;

void creat(NODE *pHead,int n)
{
	int i;
	NODE *pNew,*pTail = pHead;
	for (i = 0; i < n; i++)
	{
		pNew = malloc(sizeof(NODE));
		scanf("%d",&pNew->num);
		pNew->pNext = NULL;
		pTail->pNext = pNew;
		pTail = pTail->pNext;
	}
}

void reverse(NODE *pHead)
{
	NODE *pTemp1 = pHead->pNext,*pTemp2;
	if (pTemp1 != NULL)
	{
		while(pTemp1->pNext != NULL)
		{
			pTemp2 = pTemp1->pNext;
			pTemp1->pNext = pTemp2->pNext;
			pTemp2->pNext = pHead->pNext;
			pHead->pNext = pTemp2;
		}
	}
}

void print(NODE *pHead)
{
	NODE *pTemp = pHead->pNext;
	while(pTemp != NULL)
	{
		printf("%d\t",pTemp->num);
		pTemp = pTemp->pNext;
	}
	printf("\n");
}

int main(void)
{
	NODE *pHead = (NODE *)malloc(sizeof(NODE));
	creat(pHead,5);
	print(pHead);
	reverse(pHead);
	print(pHead);
	
	return 0;
}
