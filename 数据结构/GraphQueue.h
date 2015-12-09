/*************************************************************************
	> File Name: GraphQueue.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月09日 星期三 19时41分00秒
	> Description:
 ************************************************************************/
#ifndef _GRAPHQUEUE_H
#define _GRAPHQUEUE_H

typedef struct QueueNode{
    int data;
    struct QueueNode *pNext;
}QueueNode;

typedef struct Queue{
    QueueNode *front;
    QueueNode *rear;
}Queue;

//初始化队列
Queue *InitQueue(void);

//入队
int InQueue(Queue *q, int data);

//判队空
int QIsEmpty(Queue *q);

//出队
int OutQueue(Queue *q, int *data);

#endif
