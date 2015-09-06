/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-06-10 10:57
 * Filename	 : analyze_dir.c
 * Description	 : 获取目录下的文件并按参数打印
 * *****************************************************************************/
#include "head.h"

extern showifo(struct stat *pbuf,char *name);
extern display_attribute(struct stat *buf,char *name,int type);
void freelist(DIRNAME *pHead);
int count = 0;

//获取目录下的文件,将其存入链表
int save_dir(DIRNAME *pHead,char *path)
{
//	freelist(pHead);
	DIRNAME *pTail = pHead,*pNew;
	DIR *pdir;
	struct dirent *ptr;
	char *t_path = NULL;
	t_path = getcwd(t_path,0);
	if ((pdir = opendir(path)) == NULL)
	{
		perror("OPEN_ERROR");	return -1;
	}
	if (chdir(path) == -1)
	{
		perror("CD_ERROR");		return -1;
	}
	while((ptr = readdir(pdir)) != NULL)
	{
		if ((pNew = (DIRNAME *)malloc(sizeof(DIRNAME))) == NULL)
		{
			perror("MALLOC_ERROR");	exit(-1);
		}
		strcpy(pNew->dir_name,ptr->d_name);
		if (lstat(pNew->dir_name,&(pNew->buf)) == -1)
		{
			perror("LSTAT_ERROR");exit(-1);
		}
		pTail->pNext = pNew;	pNew->pNext = NULL;	pTail = pTail->pNext;	count++;
	}
	if (chdir(t_path) == -1)
		printf("RECDERROR");
	closedir(pdir);
}

//将文件名按照字典顺序排列
void sort_name(DIRNAME *pHead)
{
	setlocale(LC_ALL,""); //设置当前locale,第二个参数为空表示依照操作系统的当前设置
	DIRNAME *pTemp,*pTar1,*pTar2;
	int i;
	for (i = 0; i < count - 1; i++)
	{
		pTemp = pHead;
		while(pTemp->pNext->pNext != NULL)
		{
			if (strcoll(pTemp->pNext->dir_name,pTemp->pNext->pNext->dir_name) > 0)
			{
				pTar1 = pTemp->pNext;	pTar2 = pTemp->pNext->pNext;
				pTar1->pNext = pTar2->pNext;	pTar2->pNext = pTar1;
				pTemp->pNext = pTar2;
			}
			pTemp = pTemp->pNext;
		}
	}
}

//链表逆置
void reverse(DIRNAME * pHead)
{
	DIRNAME *pTemp1 = pHead->pNext,*pTemp2;
	if(pTemp1 != NULL)
	{
		while(pTemp1->pNext != NULL)
		{
			pTemp2 = pTemp1->pNext;
			pTemp1->pNext = pTemp2->pNext;
			pTemp2->pNext = pHead->pNext;
			pHead->pNext = pTemp2;
		}
	}
}

//文件名输出
void show_dir(DIRNAME *pHead,int type,int i_type)
{
	DIRNAME *pTemp = pHead->pNext;
	if (type == 0)
	{
		while (pTemp != NULL)
		{
			if (pTemp->dir_name[0] != '.')
			{
				if (i_type == 1)
					printf("%d ",(int)pTemp->buf.st_ino);
				showifo(&(pTemp->buf),pTemp->dir_name);
			}
			pTemp = pTemp->pNext;
		}
	}
	else
	{
		while (pTemp != NULL)
		{
			showifo(&(pTemp->buf),pTemp->dir_name);
			pTemp = pTemp->pNext;
		}
	}
}

//打印文件的详细信息(-l)
void display_exhau(DIRNAME *pHead,char *path,int g_type,int a_type)
{
	//g_type:是否打印所有者信息(-g)
	//a_type:是否含有-a参数
	DIRNAME *pTemp = pHead->pNext;
	if (chdir(path) == -1)
	{
		perror("CD_ERROR");exit(-1);
	}
	if (a_type == 0)
	{
		while (pTemp != NULL)
		{
			if (pTemp->dir_name[0] != '.')
				display_attribute(&(pTemp->buf),pTemp->dir_name,g_type);
			pTemp = pTemp->pNext;
		}
	}
	else
	{
		while (pTemp != NULL)
		{
			display_attribute(&(pTemp->buf),pTemp->dir_name,g_type);
			pTemp = pTemp->pNext;
		}
	}
}

//将文件按照最后更改的状态排序(-c)
void sort_ctime(DIRNAME *pHead)
{
	DIRNAME *pTemp,*pTar1,*pTar2;
	int i;
	for (i = 0; i < count - 1; i++)
	{
		pTemp = pHead;
		while(pTemp->pNext->pNext != NULL)
		{
			if (pTemp->pNext->buf.st_ctime < pTemp->pNext->pNext->buf.st_ctime)
			{
				pTar1 = pTemp->pNext;	pTar2 = pTemp->pNext->pNext;
				pTar1->pNext = pTar2->pNext;	pTar2->pNext = pTar1;
				pTemp->pNext = pTar2;
			}
			pTemp = pTemp->pNext;
		}
	}

}

//释放链表
void freelist(DIRNAME *pHead)
{
	DIRNAME *pTemp1,*pTemp2;
	pTemp1 = pHead->pNext;
	pTemp2 = pHead->pNext;
	while(pTemp2 != NULL)
	{
		pTemp2 = pTemp1->pNext;
		free(pTemp1);
		pTemp1 = pTemp2;
	}
//	free(pHead);
	pHead->pNext = NULL;
}

//销毁链表
void dellist(DIRNAME *pHead)
{
	freelist(pHead);
	free(pHead);
}

//递归解析路径下所有文件夹下的文件
void show_all(DIRNAME *pHead,char *path)
{
	int flag = 0;
	char pathadd[PATH_MAX + 1],pathTemp[PATH_MAX + 1];
	DIRNAME *pTemp = pHead,*pHead2;
	pHead2 = (DIRNAME *)malloc(sizeof(DIRNAME));	pHead2->pNext = NULL;
	//显示当前路径下的所有文件
	printf("%s\n",path);
	sort_name(pHead);	show_dir(pTemp,0,0);
	printf("\n\n");

	pTemp = pHead->pNext;
	while(pTemp != NULL)
	{
		if ((S_ISDIR(pTemp->buf.st_mode) != 0) && (strncmp(pTemp->dir_name,".",1) != 0))
		{
			strcpy(pathTemp,path);
			strcpy(pathadd,pTemp->dir_name);
			strcat(pathTemp,pathadd);	strcat(pathTemp,"/");
			if (save_dir(pHead2,pathTemp) != -1)
				show_all(pHead2,pathTemp);
			else
				printf("%s\n",pathTemp);
			memset(pathTemp,0,PATH_MAX);
		}
		pTemp = pTemp->pNext;
	}
	//freelist(pHead2);
//	dellist(pHead);

	return ;
}

//打印目录信息
void choise_display(DIRNAME *pHead,char *path,int type)
{
	//type:选择参数
	switch(type)
	{
		case NONE:	sort_name(pHead);	show_dir(pHead,0,0);		break;	//不带任何参数
		case A:		sort_name(pHead);	show_dir(pHead,1,0);		break;	//带-a参数
		case L:		sort_name(pHead);
					display_exhau(pHead,path,0,0);					break;	//带-l参数
		case C:		sort_ctime(pHead);	show_dir(pHead,0,0);		break;	//带-c参数
		case G:		sort_name(pHead);
					display_exhau(pHead,path,1,0);					break;	//带-g参数
		case CAPU:	show_dir(pHead,0,0);							break;	//带-U参数
		case LA:	sort_name(pHead);	
					display_exhau(pHead,path,0,1);					break;  //带-la参数
		case AC:	sort_ctime(pHead);	show_dir(pHead,1,0);		break;	//带-ac参数
		case ACAPU:	show_dir(pHead,1,0);							break;	//带aU参数
		case LCAPU:	display_exhau(pHead,path,0,0);					break;	//带lU参数
		case GCAPU:	display_exhau(pHead,path,1,0);					break;  //带gU参数
		case GA:	sort_name(pHead);	
					display_exhau(pHead,path,1,1);					break;  //带ga参数
		case CAPR:	show_all(pHead,path);							break;  //带R参数
		case R:		sort_name(pHead);	reverse(pHead);	
					show_dir(pHead,0,0);							break;	//带r参数
		case I:		sort_name(pHead);	show_dir(pHead,0,1);		break;	//带i参数
	}
}
