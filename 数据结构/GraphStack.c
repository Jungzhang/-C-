/*************************************************************************
	> File Name: GraphStack.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月09日 星期三 16时57分58秒
	> Description: 图的相关算法所用到的辅助栈
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "GraphStack.h"

//初始化栈
STACK *InitStack(void)
{
    STACK *stack = (STACK *)malloc(sizeof(STACK));
    stack->top = -1;

    return stack;
}

//入栈
int PushStack(STACK *stack, int data)
{
    if (stack->top == MAX) {
        printf("栈已满,无法入栈");
        return 0;
    }

    stack->data[++stack->top] = data;
    
    return 1;
}

//取栈顶
int GetTop(STACK *stack, int *data)
{
    if (IsEmpty(stack)){
        printf("栈已空,无法出栈!\n");
        return 0;
    }
    *data = stack->data[stack->top];

    return 1;
}

//出栈
int PopStack(STACK *stack, int *data)
{
    if (IsEmpty(stack)){
        printf("栈已空,无法出栈!\n");
        return 0;
    }

    *data = stack->data[stack->top];
    --stack->top;

    return 1;
}

//判栈空
int IsEmpty(STACK *stack)
{
    if (stack->top < 0){
        return 1;
    } else {
        return 0;
    }   
}
