/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-09-28 20:25
 * Filename	 : maze1.c
 * Description	 : 非递归走迷宫
 * *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define COUNT_I 9
#define COUNT_J 8
#define START_I 0
#define START_J 0
#define END_I 8
#define END_J 7
#define MAXSIZE 1000

//坐标位置结构体
typedef struct local{
	
	int x;
	int y;

}LOCAL;

typedef struct stack{
	
	LOCAL data[MAXSIZE];
	int top;

}STACK;

//初始化栈
STACK *InitStack(void)
{
	STACK *maze;
	maze = (STACK *)malloc(sizeof(STACK));
	maze->top = -1;
	
	return maze;
}

//判栈空
int EmptyStack(STACK *maze)
{
	if (maze->top == -1)
		return 1;
	else
		return 0;
}

//判栈满
int IsFull(STACK *maze)
{
	if (maze->top == MAXSIZE - 1)
		return 1;
	else
		return 0;

}

//入栈
int PushStack(STACK *maze, LOCAL *x)
{
	if (maze->top <= MAXSIZE - 1){
		maze->data[++maze->top] = *x;
		return 1;
	}
	else{
		printf("栈已满\n");
		return 0;
	}
}

//出栈
int PopStack(STACK *maze, LOCAL *x)
{
	if (maze->top > -1){
		*x = maze->data[maze->top];
		maze->top--;
		return 1;
	}
	else{
		printf("栈已空\n");
		return 0;
	}
}

//走迷宫函数
int VistMaze(int maze[][COUNT_J], LOCAL path[][COUNT_J])
{
	int i, j;

	//初始化栈
	STACK *stack;
	LOCAL temp;
	stack = InitStack();
	temp.x = 0; temp.y = 0;
	if (maze[START_I][START_J] == 0)
		PushStack(stack, &temp);
	else
		return 0;
	while(!EmptyStack(stack)){
		PopStack(stack, &temp);
		i = temp.x;	j = temp.y;
		maze[i][j] = 2;

		if (i == END_I && j == END_J)
			break;

		//下
		if (i + 1 <= END_I && maze[i + 1][j] == 0){
			maze[i + 1][j] = 2;
			path[i + 1][j].x = i;	path[i + 1][j].y = j;
			temp.x = i + 1;
			temp.y = j;
			PushStack(stack, &temp);
		}
		//右
		if (j + 1 <= END_J && maze[i][j + 1] == 0){
			maze[i][j + 1] = 2;
			path[i][j + 1].x = i;	path[i][j + 1].y = j;
			temp.x = i;
			temp.y = j + 1;
			PushStack(stack, &temp);
		}
		//左
		if (j - 1 >= 0 && maze[i][j - 1] == 0){
			maze[i][j - 1] = 2;
			path[i][j - 1].x = i;	path[i][j - 1].y = j;
			temp.x = i;
			temp.y = j - 1;
			PushStack(stack, &temp);
		}
		//上
		if (i - 1 >= 0 && maze[i - 1][j] == 0){
			maze[i - 1][j] = 2;
			path[i - 1][j].x = i;	path[i - 1][j].y = j;
			temp.x = i - 1;
			temp.y = j;
			PushStack(stack, &temp);
		}
	}
	//如果到达终点而退出的循环则将路径标识出来
	if (i == END_I && j == END_J){
		maze[i][j] = 3;
		while(path[temp.x][temp.y].x != -1){
			temp = path[temp.x][temp.y];
			maze[temp.x][temp.y] = 3;
		}
		
		return 1;
	}
	else{
		return 0;
	}
}



int main(void)
{
	//迷宫
	int i, j;
	int maze[COUNT_I][COUNT_J] = {
			{0,0,1,0,0,0,1,0},
			{0,0,1,0,0,0,1,0},
			{0,0,0,0,1,1,0,1},
			{0,1,1,1,0,0,1,0},
			{0,0,0,1,0,0,0,0},
			{0,1,0,0,0,1,0,1},
			{0,1,1,1,1,0,0,1},
			{1,1,0,0,1,1,0,1},
			{1,1,0,0,0,0,0,0}
		};
	
	//定义路径数组,将到(x,y)点的路径保存进数组
	LOCAL path[COUNT_I][COUNT_J];
	for(i = 0; i < COUNT_I; i++){
		for(j = 0; j < COUNT_J; j++){
			path[i][j].x = -1;
			path[i][j].y = -1;
		}
	}

	//打印出迷宫
	printf("原迷宫：\n");
	for(i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");
	for (i = 0; i < COUNT_I; i++){
		printf("|");
		for (j = 0; j < COUNT_J; j++){
			if (maze[i][j] == 1)
				printf("@");
			else
				printf(" ");
		}
		printf("|\n");
	}
	for(i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");

	if (VistMaze(maze, path) == 0){
		printf("没有路径可走\n");
		exit(0);
	}

	//打印出迷宫和路径
	printf("迷宫和路径：\n");
	for(i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");
	for (i = 0; i < COUNT_I; i++){
		printf("|");
		for (j = 0; j < COUNT_J; j++){
			if (maze[i][j] == 1)
				printf("@");
			else if (maze[i][j] == 3)
				printf("%%");
			else
				printf(" ");
		}
		printf("|\n");
	}
	for(i = 0; i <= COUNT_I; i++)
		printf("-");
	printf("\n");

	return 0;
}
