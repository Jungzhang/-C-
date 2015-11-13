/*******************************************************************************
* Author	 : zhanggen
* Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
* Last modified : 2015-11-05 18:36
* Filename	 : TreeStack.c
* Description	 : 树非递归遍历所用到的栈操作
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"

//初始化栈
STACK *InitStack(void)
{
	STACK *head = (STACK *)malloc(sizeof(STACK));
	head->top = -1;

	return head;
}

//入栈
int PushStack(STACK *head, BiTree *data)
{
	if (head->top == MAXSIZE - 1){
		return 0;
	}
	else{
		head->top++;
		head->data[head->top] = data;
	}

	return 1;
}

//出栈
int PopStack(STACK *head, BiTree **data)
{
	if (head->top == -1) {
		return 0;
	}
	else {
		*data = head->data[head->top];
		head->top--;
	}

	return 1;
}

//取栈顶
int GetTop(STACK *head, BiTree **data)
{
	if (head->top == -1) {
		return 0;
	}
	else {
		*data = head->data[head->top];
	}

	return 1;
}

//判栈空
int IsEmpty(STACK *head)
{
    if (head->top == -1)
        return 1;
    else
        return 0;
}

//销毁栈
void DestroyStack(STACK *head)
{
	free(head);
}
