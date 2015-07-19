#include <stdio.h>
#define N 3

struct{

	char name[20];
	long num;
	int age;
	union{

		float score;
		char grade;		

	}result;

}employee[N];

void input(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("姓名:");	gets(employye[i].name);
		printf("准考证号:");	scanf("%ld",&num);
		printf("年龄:");	scanf("%d",&p[i].age);	getchar();
		if (age <= 30){
			printf("分数:");scanf("%d",&result.score);	getchar();
		}
		else{
			printf("等级:");	result.grade = getchar();
		}
	}
}

int tongji(struct employee *p,int n)
{
	int count,i;
	for (i = 0; i < n; i++)
	{
		if ((p[i].age <= 30) && (p[i].result.score >= 60))
			count++;
		else if ((p[i].age > 30) && (p[i].result.grade <= 'C'))
			count++;
	}

	return count;
}

void print(struct employee *p,int n)
{
	int i;
	printf("%20s","姓名");	printf("%20s","成绩/等级");
	for (i = 0; i < n; i++)
	{
		if (p[i].age <= 30)
			printf("%15d",p[i].result.score);
		else
			printf("%15c",p[i].result.grade);
		printf("\n");
	}
}

int main(void)
{
	input(employee,3);
	printf("及格%d个人!\n",tongji(employee,3));
	print(employee,3);

	return 0;
}
