/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-10-21 20:00
 * Filename	 : mage.c
 * Description	 : 魔术师发牌问题
 * *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct PlayCard{
	
	int num;
	struct PlayCard *pNext;

}PlayCard;

//创建一个带有13个结点的循环链表
PlayCard *CreatList(void)
{
	PlayCard *pHead, *pNew, *pTail;
	int i;

	pHead = (PlayCard *)malloc(sizeof(PlayCard));
	pHead->num = -1;
	pTail = pHead;
	for (i = 0; i < 13; i++){
		pNew = (PlayCard *)malloc(sizeof(PlayCard));
		pNew->num = 0;
		pTail->pNext = pNew;
		pTail = pNew;
	}
	pNew->pNext = pHead;

	return pHead;
}

//为每个结点存入数据
void WriteData(PlayCard *pHead)
{
	int CardNum = 1;
	int temp = 0;
	PlayCard *pTemp = pHead;

	while(1){
		if (CardNum == 14)
			break;
		while(temp != CardNum){
			temp++;
			pTemp = pTemp->pNext;
			if (pTemp->num != 0 || pTemp == pHead)
				temp--;
		}
		pTemp->num = CardNum;
		CardNum++;
		temp = 0;
	}
}

//打印链表
void ShowList(PlayCard *pHead)
{
	PlayCard *pTemp = pHead->pNext;
	while(pTemp != pHead){
		printf("%d\t", pTemp->num);
		pTemp = pTemp->pNext;
	}
	printf("\n");
}

int main(void)
{
	PlayCard *pHead;
	pHead = CreatList();
	WriteData(pHead);
	ShowList(pHead);

	return 0;
}
