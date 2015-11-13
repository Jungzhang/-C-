/*******************************************************************************
 Author	 : zhanggen
 Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 Last modified : 2015-11-05 15:31
 Filename	 : Hanoi.c
 Description	 : 汉诺塔
*******************************************************************************/

#include <stdio.h>

//将x上的n个盘子借助y移动到z上(递归)
void RecursionMove(int n, char x, char y, char z)
{
	if (n == 1) {
		printf("%c -> %c\n", x, z);		//如果是一个盘子,直接将盘子从X移动到Z
	}
	else {
		move(n - 1, x, z, y);	//如果是n个盘子,先将n-1个盘子从x借助z移动到y
		printf("%c -> %c\n", x, z);	//将x上的剩余一个盘子直接移动到z上
		move(n - 1, y, x, z);	//将y上的n-1个盘子借助x移动到z
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);
	RecursionMove(n, 'x', 'y', 'z');
}
