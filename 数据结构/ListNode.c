/*************************************************************************
	> File Name: ListNode.c
	> Author: jungzhang
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年11月09日 星期一 18时26分11秒
	> Description: 链表中一些有趣的题目
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *pNext;
}NODE;

//链表的初始化
NODE *Init(void)
{
    NODE *pHead = (NODE *)malloc(sizeof(NODE));

    return pHead;
}

//链表的创建
int Creat(NODE *pHead, int n)
{
    int i;
    NODE *pNew, *pTail = pHead;
    for (i = 0; i < n; i++)
    {
        if ((pNew = (NODE *)malloc(sizeof(NODE))) == NULL)
        {
            return 0;
        }
        pNew->data = i + 1;
        pTail->pNext = pNew;
        pTail = pNew;
    }
    pTail->pNext = NULL;
    
    return 1;
}

//查找单链表的中间结点函数
NODE *SearchMiddile(NODE *pHead)
{
    NODE *fast = pHead, *slow = pHead;

    while(fast)
    {
        if (fast->pNext == NULL)
            fast = fast->pNext;
        else
            fast = fast->pNext->pNext;
        slow = slow->pNext;
    }

    return slow;
}

//判断链表中是否有环,并返回链表中的环入口
int IsRing(NODE *pHead, NODE **pEnter)
{
    int a = 0, b = 0;
    NODE *pFast = pHead, *pSlow = pHead;
    while(pFast != NULL && pFast->pNext != NULL)
    {
        pFast = pFast->pNext->pNext;
        pSlow = pSlow->pNext;
        a++;    b += 2;

        if (pFast == pSlow && a != b){
            pFast = pHead;
            while(pFast != pSlow){
                pFast = pFast->pNext;
                pSlow = pSlow->pNext;
            }
            *pEnter = pSlow;
            return 1;
        }   
    }
    *pEnter = NULL;
    return 0;
}

//判断链表是否相交,并返回交点
/*int IsIntersection(NODE *pHead1, NODE *pHead2, NODE **intersec)
{
    NODE *temp = pHead1;
    while(temp->pNext){
        temp = temp->pNext;
    }
    temp->pNext = pHead1;
    
    return IsRing(pHead2, intersec);
}*/

//判断链表是否相交，并返回交点
int IsIntersection(NODE *pHead1, NODE *pHead2, NODE **intersec)
{
    int length1 = 0, length2 = 0, i, len;
    NODE *pTemp1 = pHead1, *pTemp2 = pHead2;
    
    //第一条链表从头遍历到尾
    while(pTemp1->pNext){
        pTemp1 = pTemp1->pNext;
        length1++;
    }

    //第二条链表从头遍历到尾
    while(pTemp2->pNext){
        pTemp2 = pTemp2->pNext;
        length2++;
    }

    //如果相交则从新遍历
    if (pTemp1 == pTemp2){
        len = abs(length1 - length2);
        pTemp1 = pHead1;    pTemp2 = pHead2;
        //将较长链表的遍历起始位置到lengthmax - lengthmin处
        if (length1 > length2){
            for (i = 0; i < len; i++){
               pTemp1 = pTemp1->pNext;
            }
        }
        else {
            for (i = 0; i < len; i++){
                pTemp2 = pTemp2->pNext;
            }
        }
        while(pTemp1 != pTemp2){
            pTemp1 = pTemp1->pNext;
            pTemp2 = pTemp2->pNext;
        }
        *intersec = pTemp1;
        return 1; 
    }

    *intersec = NULL;
    return 0;
}

//平均时间复杂度为O(1)内删除给定的结点
void DelNode(NODE *pHead, NODE *pDel)
{
    NODE *pTemp = pHead, *pTar;
    if (pDel == pHead){
        printf("不能删除头结点\n");
        return;
    }
    if (pDel->pNext != NULL){
        pDel->data = pDel->pNext->data;
        pTar = pDel->pNext;
        pDel->pNext = pTar->pNext;
    }
    else {
        while(pTemp->pNext != pDel){
            pTemp = pTemp->pNext;
        }
        pTar = pTemp->pNext;
        pTemp->pNext = pTar->pNext;
    }
    free(pTar);
}

//求链表中倒数第k个结点,1为尾结点
NODE *ListNode(NODE *pHead, int k)
{
    int i = 0;
    NODE *p1 = pHead, *p2 = pHead->pNext;
    while(p1 != NULL  && i < k){
        p1 = p1->pNext;     i++;
    }
    if (p1 != NULL){
        while(p1->pNext != NULL){
            p1 = p1->pNext; p2 = p2->pNext;
        }
        return p2;
    }
    else{
        return NULL;
    }
}

int main(void)
{
    int n;
    NODE *pHead = Init();
    NODE *pHead2 = Init();
    NODE *tar = pHead2;
   // scanf("%d", &n);
    Creat(pHead, 5);
    tar = ListNode(pHead, 0);
    if(tar != NULL)
        printf("%d\n", tar->data);
    else
        printf("有误!\n");
}
