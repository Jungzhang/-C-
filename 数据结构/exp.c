/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-09-21 21:40
 * Filename	 : exp.c
 * Description	 : 中缀式表达式求值
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

//数字栈
typedef struct oprd{
	
	double data[MAXSIZE];
	int top;

}OPRD;

//运算符栈
typedef struct optr{

	char data[MAXSIZE];
	int top;

}OPTR;

//因为涉及到两个栈的操作,所以将栈相关的操作用宏定义写成函数,
//这样就具有了通用性

//初始化栈
#define InitStack(StackType, stack)	\
{	\
	*stack = (StackType *)malloc(sizeof(StackType));	\
	*stack->top = -1;	\
}

//判栈空
#define EmptyStack(stack)	\
(	\
	stack->top == -1	\
)

//判栈满
#define FullStack(stack)	\
(	\
	stack->top == MAXSIZE - 1	\
)

//入栈
#define PushStack(stack, value)	\
{	\
	if (!FullStack(stack)){	\
		stack->top++;	\
		stack->data[stack->top] = value;	\
	}	\
	else{	\
		printf("栈已满,无法入栈\n");	\
		exit(-1);	\
	}	\
}

//出栈
#define PopStack(stack, value)	\
{	\
	if (!EmptyStack(stack)){	\
		*value = stack->data[stack->top];	\
		stack->top--;	\
	}	\
	else{	\
		printf("栈已空,无法出栈\n");	\
		exit(-1);	\
	}	\
}

//取栈顶元素
#define GetStackTop(stack, value)	\
{	\
	if (!EmptyStack(stack)){	\
		*value = stack->data[stack->top];	\
	}	\
	else{	\
		printf("栈为空,无法取栈顶元素\n");	\
	}	\
}

//优先级表
char compare(char ch, char top)
{
	switch(ch){
		case '+':
		case '-':
			if (top == '+' || top == '-' || top == '*' || top == '/')
				return '<';	//扫描的小于栈顶
			else
				return '>';	//扫描的大于栈顶
			break;
		case '*':
		case '/':
			if (top == '*' || top == '/')
				return '<';
			else
				return '>';
			break;
		case '(':
			if(top == ')'){
				printf("输入有误!\n");	exit(-1);
			}
			return '>';
			break;
		case ')':
			if (top == '(')
				return '=';
			else if(top == '#'){
				printf("输入有误!\n");
				exit(-1);
			}
			else{
				return '<';
			}
			break;
		case '#':
			return '<';
	}
}

//输入表达式并计算结果
double CalculateExp(void)
{
	double result, tempNum1, tempNum2;
	double data = 0, expn;
	char ch, topSign, point = 'n', num = 'n';
	OPTR *sign;
	OPRD *number;

	InitStack(OPTR, &sign);
	InitStack(OPRD, &number);
	PushStack(sign, '#');
	printf("请输入表达式：");
	ch = getchar();
	GetStackTop(sign, &topSign);

	while(ch != '#' || topSign != '#'){
		if ('0' <= ch && ch <= '9' || ch == '.'){
			if (ch == '.' && point == 'y'){
				printf("表达式输入有误!\n");
				exit(-1);
			}
			else if (ch == '.' && point == 'n'){
				point = 'y';
				expn = 0.1;
			}
			else{
				if (point == 'y'){
					data = data + expn * (ch - '0');
					expn *= 0.1;
				}
				else{
					data = data * 10 + (ch - '0');
				}
				num = 'y';
			}
			ch = getchar();
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#'){
			if (num == 'y'){
				PushStack(number, data);
				num = 'n';	point = 'n';
				data = 0;
			}
			GetStackTop(sign, &topSign);
			switch(compare(ch, topSign)){
				case '<':		//扫描运算符优先级小于栈顶元素
					PopStack(sign, &topSign);
					PopStack(number, &tempNum1);
					PopStack(number, &tempNum2);
					switch(topSign){
						case '+':	result = tempNum1 + tempNum2;	break;
						case '-':	result = tempNum1 - tempNum2;	break;
						case '*':	result = tempNum1 * tempNum2;	break;
						case '/':	result = tempNum2 / tempNum1;	break;
					}
					PushStack(number, result);
					break;
				case '>':		//扫描运算符优先级大于栈顶元素
					PushStack(sign, ch);
					ch = getchar();
					break;
				case '=':		//扫描运算符为右括号,匹配到了左括号
					PopStack(sign, &topSign);
					ch = getchar();
					break;
			}
		}
		else if (ch == '\n'){
			ch = '#';
		}
		else{
			printf("输入的表达式有误!\n");
			exit(-1);
		}
		GetStackTop(sign, &topSign);
	}
	PopStack(number, &result);	//将结果从栈中取出来
	if (!EmptyStack(number)){   //如果取出后栈不为空则表示输入的表达式不正确
		printf("表达式有误!\n");
		exit(-1);
	}
	
	return result;
}

int main(void)
{
	printf("%lf\n", CalculateExp());
	
	return 0;
}
