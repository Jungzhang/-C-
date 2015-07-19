#include <stdio.h>

typedef struct student{

	char id[20];
	char name[50];
	int score[4];

}STU;


void input(STU *stu,int n)
{
	int i,j;
	for (i = 0; i < n; i++)
	{
		printf("学号:");	gets(stu[i].id);
		printf("姓名:");	gets(stu[i].name);
		printf("语文：");	scanf("%d",&stu[i].score[0]);
		printf("数学：");	scanf("%d",&stu[i].score[1]);
		printf("英语：");	scanf("%d",&stu[i].score[2]); getchar();
	}
}

void average(STU *stu,int n,int *soreave,int m)
{
	int i,j = 0,temp;
	for (i = 0; i < n; i++)
	{
		stu[i].score[3] = (stu[i].score[0] + stu[i].score[1] + stu[i].score[2]) / 3.0 + 0.5;
	}
	for (j = 0; j < m; j++)
	{
		temp = 0;
		for (i = 0; i < n; i++)
			temp += stu[i].score[j];
		soreave[j] = 1.0 * temp / n + 0.5;
	}

}

STU max(STU *stu,int n)
{
	STU stumax = stu[0];
	int i,temp1,temp2;
	for (i = 0; i < n; i++)
	{
		temp1 = stumax.score[0] + stumax.score[1] + stumax.score[2];
		temp2 = stu[i].score[0] + stu[i].score[1] + stu[i].score[2];
		if (temp1 < temp2)
			stumax = stu[i];
	}
	
	return stumax;
}

int main(void)
{
	STU stu[3],stumax;
	int ave[3],i,j;
	input(stu,3);
	average(stu,3,ave,3);
	stumax = max(stu,3);
	printf("%13s","学  号");printf("%13s","姓  名");
	printf("%13s","语  文");printf("%13s","数  学");
	printf("%13s","英  语");printf("%13s\n","平  均");
	for (i = 0; i < 3; i++)
	{
		printf("%13s",stu[i].id);	printf("%13s",stu[i].name);
		for (j = 0; j < 4; j++)
		{
			printf("%9d",stu[i].score[j]);
		}
		printf("\n\n");
	}
	printf("成绩最高者:\n");
	printf("%13s",stumax.id);	printf("%13s",stumax.name);
	for (j = 0; j < 4; j++)
		printf("%9d",stumax.score[j]);
	printf("\n==================================================\n");
	printf("%20s","语文平均");printf("%20s","数学平均");
	printf("%20s","英语平均\n");
	for (i = 0; i < 3; i++)
		printf("%15d",ave[i]);
	printf("\n");

	return 0;
}
