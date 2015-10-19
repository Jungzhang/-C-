/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-10-19 11:10
 * Filename	 : StaticLinkList.c
 * Description	 : 静态链表
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10

//链表的结构体定义
typedef struct LinkList{
	
	int data;
	int cur;

}LINKLIST;

//初始化静态链表
LINKLIST *InitList(void)
{
	int i;
	LINKLIST *pHead;
	pHead = (LINKLIST *)malloc(sizeof(LINKLIST) * MAXSIZE);
	for (i = 0; i < MAXSIZE - 2; i++)
		pHead[i].cur = i + 1;	//当i=0时用第一个元素保存未用元素的首下标(即将第一个元素作为存储未用链表的头结点)

	pHead[MAXSIZE - 2].cur = -1;	//将最后一个元素的游标域置为-1(想象成指针中的NULL)
	pHead[MAXSIZE - 1].cur = -1;	//当i等于MAXSIZE-1时用最后一个元素保存已用元素的首下标
	    							//(即将最后一个元素作为存储已用链表的头结点)
	
	return pHead;
}

//输出链表内容
void ShowList(LINKLIST *pHead)
{
	int i;
	i = pHead[MAXSIZE - 1].cur;
	while(i != -1){
		printf("%d\n", pHead[i].data);
		i = pHead[i].cur;
	}
}

//尾插元素
int AddTailList(int num, LINKLIST *pHead)
{
	int i, temp;
	if (pHead[0].cur == -1){
		printf("存储池已满\n");
		return 0;
	}
	//遍历寻找最后一个元素(尾结点)
	i = MAXSIZE - 1;
	while(pHead[i].cur != -1){
		i = pHead[i].cur;
	}

	temp = pHead[pHead[0].cur].cur;
	pHead[i].cur = pHead[0].cur;
	pHead[pHead[0].cur].data = num;
	pHead[pHead[i].cur].cur = -1;
	pHead[0].cur = temp;

	return 1;
}

//删除链表中第pos个(pos从0开始)元素
int DelList(int pos, LINKLIST *pHead)
{
	int i, posTemp = -1, tailTemp;
	i = MAXSIZE - 1;

	if (pos < 0){
		printf("输入有误\n");
		return -1;
	}
	//找到待删除元素的前一个结点
	while(posTemp != pos - 1 && i != -1){
		i = pHead[i].cur;
		posTemp++;
	}

	if (i == -1){
		printf("未找到该下标的元素\n");
		return 0;
	}
	
	tailTemp = pHead[0].cur;
	pHead[0].cur = pHead[i].cur;
	pHead[i].cur = pHead[pHead[i].cur].cur;
	pHead[pHead[0].cur].cur = tailTemp;

	return 1;
}

int main(void)
{
	int num, i;
	LINKLIST *pHead = InitList();
	ShowList(pHead);
	for(i = 0; i < 3; i++){
		printf("请输入元素内容:");
		scanf("%d", &num);
		AddTailList(num, pHead);
	}
	ShowList(pHead);
	DelList(2,pHead);
	printf("删除下标2后：\n");
	ShowList(pHead);
	DelList(0,pHead);
	printf("删除下标0后：\n");
	ShowList(pHead);
	DelList(9, pHead);
	printf("删除下标9后：\n");
	ShowList(pHead);
	DelList(2, pHead);
	printf("删除下标2后：\n");
	ShowList(pHead);

	return 0;
}
