/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-10-26 15:46
 * Filename	 : BeeLanguage.c
 * Description	 : 魔王语言解释器
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

//栈
typedef struct stack{
	
	char data[MAXSIZE];
	int top;

}STACK;

//初始化栈
STACK *InitStack()
{

	STACK *reverse = (STACK *)malloc(sizeof(STACK));
	reverse->top = -1;

	return reverse;
}

//入栈
int PushStack(STACK *reverse, char data)
{

	if (reverse->top == MAXSIZE - 1){
		printf("栈已满,无法入栈\n");
		return 0;
	}
	reverse->data[++reverse->top] = data;

	return 1;
}

//出栈
int PopStack(STACK *reverse, char *data)
{
	if (reverse->top == -1){
		printf("栈已空,无法出栈\n");
		return 0;
	}
	*data = reverse->data[reverse->top];
	reverse->top--;

	return 1;
}

//输出汉字
void ShowMessage(char data)
{
	if (data == 't'){
		printf("天");
	}
	else if (data == 'd'){
		printf("地");
	}
	else if (data == 's'){
		printf("上");
	}
	else if (data == 'a'){
		printf("一只");
	}
	else if (data == 'e'){
		printf("鹅");
	}
	else if (data == 'z'){
		printf("追");
	}
	else if (data == 'g'){
		printf("赶");
	}
	else if (data == 'x'){
		printf("下");
	}
	else if (data == 'n'){
		printf("蛋");
	}
	else if (data == 'h'){
		printf("恨");
	}
	else{
		printf("%c", data);
	}
}

int main(void)
{
	int i = 0, flag = 0;
	char character[MAXSIZE], frist, temp, ch;
	STACK *reverse = InitStack();

	printf("请输入字符串:");
	ch = getchar();
	while(ch != '\n'){
		if (ch == 'A'){
			if (flag != 0){
				if (reverse->top == -1){
					character[i] = frist;	i++;
				}
				while(reverse->top > -1){
					PopStack(reverse, &temp);
					character[i] = frist;	i++;
					character[i] = temp;	i++;
				}
				flag = 0;
				character[i] = frist;	i++;
			}
			character[i] = 's';	i++;
			character[i] = 'a';	i++;
			character[i] = 'e';	i++;
		}
		else if (ch == 'B'){
			if (flag != 0){
				if (reverse->top == -1){
					character[i] = frist;	i++;
				}
				while(reverse->top > -1){
					character[i] = frist;	i++;
					PopStack(reverse, &temp);
					character[i] = temp;	i++;
				}
				character[i] = frist;	i++;
				flag = 0;
			}
			character[i] = 't';	i++;
			character[i] = 's';	i++;
			character[i] = 'a';	i++;
			character[i] = 'e';	i++;
			character[i] = 'd';	i++;
			character[i] = 's';	i++;
			character[i] = 'a';	i++;
			character[i] = 'e';	i++;
		}
		else{
			if (flag == 0){
				frist = ch;
				flag = 1;
			}
			else{
				PushStack(reverse,ch);
			}
		}
		ch = getchar();
	}
	character[i] = '\0';
	for(i = 0; character[i] != '\0'; i++){
		ShowMessage(character[i]);
	}
	printf("\n");
	
	return 0;
}
