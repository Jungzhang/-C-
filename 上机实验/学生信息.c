#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	
	char name[20];
	char id[20];
	int score;
	struct student *pNext;

}STU;

void addstu(STU *pHead)
{
	STU *pTemp = pHead,*pNew;
	while(pTemp->pNext != NULL)
		pTemp = pTemp->pNext;
	pNew = (STU *)malloc(sizeof(STU));
	pTemp->pNext = pNew;
	printf("name:");	gets(pNew->name);
	printf("Id:");	gets(pNew->id);
	printf("score:");	scanf("%d",&pNew->score);	getchar();
	pNew->pNext = NULL;
}

void delstu(STU *pHead,char *id)
{
	STU *pTar = pHead,*pTemp;
	while((pTar->pNext != NULL) && (strcmp(pTar->pNext->id,id)!=0))
		pTar = pTar->pNext;
	if (pTar->pNext == NULL)
		printf("Not find this student!\n");
	else
	{
		pTemp = pTar->pNext->pNext;
		free(pTar->pNext);
		pTar->pNext = pTemp;
		printf("Delete succeed!\n");
	}
}

void seekstu(STU *pHead,char *id)
{
	STU *pTemp = pHead;
	while((pTemp->pNext != NULL) && (strcmp(pTemp->pNext->id,id) != 0))
		pTemp = pTemp->pNext;
	if (pTemp->pNext == NULL)
		printf("Not find this student!\n");
	else
	{
		printf("%20s","ID");printf("%20s","NAME");printf("%10s\n","SCORE");
		printf("%20s",pTemp->pNext->id);
		printf("%20s",pTemp->pNext->name);
		printf("%10d\n",pTemp->pNext->score);
	}
}

int main(void)
{
	STU *pHead = (STU *)malloc(sizeof(STU));
	int key; char ch,tid[20];
	loop1:printf("1.Add student.\n");
	printf("2.Delete student.\n");
	printf("3.Seek student.\n");
	printf("Please choice:");
	scanf("%d",&key);getchar();
	switch(key)
	{
		case 1:{
			loop2:addstu(pHead);
			loop3:printf("Do you want go on input(y/n):");
			ch = getchar();getchar();
			if (ch == 'y')	goto loop2;
			else if (ch == 'n')	break;
			else	goto loop3;
		}
		case 2:{	
			loop4:fflush(stdin);
			printf("Please input id:");gets(tid);delstu(pHead,tid);
			loop5:printf("Do you want go on delete(y/n):");
			ch = getchar();getchar();
			if (ch == 'y')	goto loop4;
			else if (ch == 'n')	break;
			else	goto loop5;
		}
		case 3:{	
			loop6:fflush(stdin);
			printf("Please input id:");gets(tid);seekstu(pHead,tid);
			loop7:printf("Do you want go on seek(y/n):");
			ch = getchar();getchar();
			if (ch == 'y')	goto loop6;
			else if (ch == 'n')	break;
			else printf("Input ERROR!\n");goto loop7;
		}
		default:
			printf("Input ERROR!\n");	goto loop1;
	}
	loop8:fflush(stdin);printf("Do you go on(y/n):");
	ch = getchar();getchar();
	if (ch == 'y')	goto loop1;
	else if (ch == 'n')	return 0;
	else printf("Input ERROR!\n");goto loop8;

	return 0;
}
