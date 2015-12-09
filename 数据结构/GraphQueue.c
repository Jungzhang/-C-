/*************************************************************************
	> File Name: GraphQueue.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月09日 星期三 19时40分59秒
	> Description: 图相关算法的辅助队列
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "GraphQueue.h"

//初始化队列
Queue *InitQueue(void)
{
    //QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    Queue *q = (Queue *)malloc(sizeof(Queue));
    //node->pNext = NULL;
    q->front = NULL;
    q->rear = NULL;

    return q;
}

//入队
int InQueue(Queue *q, int data)
{
    QueueNode *pNew = (QueueNode *)malloc(sizeof(QueueNode));
    if (pNew == NULL){
        printf("内存分配失败!\n");
        return 0;
    }
    pNew->data = data;
    pNew->pNext = NULL;
    if (q->front == NULL && q->rear == NULL){
        q->front = pNew;
        q->rear = pNew;
    } else {
        q->rear->pNext = pNew;
        q->rear = pNew;
    }

    return 1;
}

//出队
int OutQueue(Queue *q, int *data)
{
    QueueNode *pTemp;
    if (QIsEmpty(q)){
        printf("队已空,无法出队!\n");
        return 0;
    }
    *data = q->front->data;
    pTemp = q->front;
    if (q->rear == q->front){
        q->front = q->front->pNext;
        q->rear = q->front;
    } else {
        q->front = q->front->pNext;
    }
    free(pTemp);

    return 1;
}

//判队空
int QIsEmpty(Queue *q)
{
    if (q->front == NULL && q->rear == NULL){
        return 1;
    } else {
        return 0;
    }
}
