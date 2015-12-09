/*************************************************************************
	> File Name: GraphStack.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月09日 星期三 16时59分17秒
	> Description:
 ************************************************************************/
#ifndef _GRAPHSTACK_H
#define _GRAPHSTACK_H

#define MAX 88

typedef struct STACK{
    int data[MAX];
    int top;
}STACK;

//初始化栈
STACK *InitStack(void);

//入栈
int PushStack(STACK *stack, int data);

//出栈
int PopStack(STACK *stack, int *data);

//判栈空
int IsEmpty(STACK *stack);

//取栈顶
int GetTop(STACK *stack, int *data);

#endif
