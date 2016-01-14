/*******************************************************************************
* Author	 : zhanggen
* Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
* Last modified : 2015-11-05 18:40
* Filename	 : BiTree.h
* Description	 : 树非递归操作用到的栈头文件
*******************************************************************************/
#ifndef BiTree_H_
#define BiTree_H_

#define MAXSIZE 1000

//树的数据结构
typedef struct BiTree{
	    
	char data;
	struct BiTree *LChid;
	struct BiTree *RChid;
					
}BiTree;

//栈的数据结构
typedef struct stack{
	
	BiTree *data[MAXSIZE];
	int top;
	
}STACK;

//初始化栈
STACK *InitStack(void);

//入栈
int PushStack(STACK *head, BiTree *data);

//出栈
int PopStack(STACK *head, BiTree **data);

//取栈顶
int GetTop(STACK *head, BiTree **data);

//判栈空
int IsEmpty(STACK *head);

//销毁栈
void DestroyStack(STACK *head);

#endif
