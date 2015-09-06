#include "Play_UI.h"
#include "Schedule_UI.h"

#include "../Common/List.h"
#include "../Service/Play.h"
#include "../Service/EntityKey.h"
#include "../Service/Ticket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int PLAY_PAGE_SIZE=5;

//显示剧目信息
void Play_UI_ShowList(play_list_t list, Pagination_t paging) 
{
 	int i;
	play_t play;
	char type[10];
	char rating[10];
	play_list_t pos1;
//	while(1)
	{
		system("clear");
		printf("\n|=============================================================================================================================|\n");
		printf("|*******************************************************剧 目 信 息***********************************************************|\n");
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
		printf("|%6s%25s%20s%15s%15s%15s%20s%20s%15s|\n","剧目ID","剧目名称","剧目类型","地区","适宜人群","时长","上映时间","下线日期","票价");
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
		Paging_ViewPage_ForEach(list,(paging),play_node_t,pos1,i)
		{
			if (pos1->data.type == (play_type_t)1)
				strcpy(type,"电影");
			else if (pos1->data.type == (play_type_t)2)
				strcpy(type,"戏剧");
			else if (pos1->data.type == (play_type_t)3)
				strcpy(type,"音乐");
			if (pos1->data.rating == (play_rating_t)1)
        		        strcpy(rating,"儿童");
        		else if (pos1->data.rating == (play_rating_t)2)
        		        strcpy(rating,"青年");
        		else if (pos1->data.rating == (play_rating_t)3)
        		        strcpy(rating,"成人");
			printf("%5d%20s%20s%15s%10s%14d分%8d年%2d月%2d日%8d年%2d月%2d日%7d\n",pos1->data.id,pos1->data.name,type,pos1->data.area,rating,pos1->data.duration,pos1->data.start_date.year,pos1->data.start_date.month,pos1->data.start_date.day,pos1->data.end_date.year,pos1->data.end_date.month,pos1->data.end_date.day,pos1->data.price);
		}
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
		printf("|---------------总条数:%2d ------------------------------------------------------------------------------------ 页数 %2d/%2d ----|\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
	}

}
//获取所有剧目信息显示
void Play_UI_MgtEntry(int flag){
	int k;
	play_t play;
	char type[10];
	char rating[10];
	play_list_t pos1;
	int i,id;
	char choice;
	play_list_t head,pTemp;
	play_t pos;
	Pagination_t paging;
	List_Init(head,play_node_t);
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;
	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head,paging);
	flu();
	if(flag!=0){
		printf("输入剧目ID:");
		scanf("%d",&id);
		Play_UI_Query(id);
	}
	else
	{
	do{
	system("clear");
	printf("\n|=============================================================================================================================|\n");
	printf("|*******************************************************剧 目 信 息***********************************************************|\n");
	printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
	printf("|%6s%25s%20s%15s%15s%15s%20s%20s%15s|\n","剧目ID","剧目名称","剧目类型","地区","适宜人群","时长","上映时间","下线日期","票价");
	printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
	Paging_ViewPage_ForEach(head,(paging),play_node_t,pos1,k)
	{
		if (pos1->data.type == (play_type_t)1)
			strcpy(type,"电影");
		else if (pos1->data.type == (play_type_t)2)
			strcpy(type,"戏剧");
		else if (pos1->data.type == (play_type_t)3)
			strcpy(type,"音乐");
		if (pos1->data.rating == (play_rating_t)1)
        	        strcpy(rating,"儿童");
        	else if (pos1->data.rating == (play_rating_t)2)
        	        strcpy(rating,"青年");
        	else if (pos1->data.rating == (play_rating_t)3)
        	        strcpy(rating,"成人");
		printf("%5d%20s%20s%15s%10s%14d分%8d年%2d月%2d日%8d年%2d月%2d日%7d\n",pos1->data.id,pos1->data.name,type,pos1->data.area,rating,pos1->data.duration,pos1->data.start_date.year,pos1->data.start_date.month,pos1->data.start_date.day,pos1->data.end_date.year,pos1->data.end_date.month,pos1->data.end_date.day,pos1->data.price);
		}
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
		printf("|---------------总条数:%2d ------------------------------------------------------------------------------------ 页数 %2d/%2d ----|\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
	
	printf("|-----[p]上一页 | [N]|下一页 | [S]演出计划管理 | [Q]查询剧目 | [A]添加剧目 | [D]删除剧目 | [U]修改剧目 | [R]返回上一级--------|\n");
	printf("|=============================================================================================================================|\n");
	printf("请选择:");
	scanf("%c",&choice);
	flu();
	switch(choice){
	case 'p':
	case 'P':
		if(!Pageing_IsFirstPage(paging)){
			Paging_Locate_OffsetPage(head,paging,-1,play_node_t);
			Play_UI_ShowList(head,paging);
		}
			break;
	case 'n':
	case 'N':
		if(!Pageing_IsLastPage(paging)){
			Paging_Locate_OffsetPage(head,paging,1,play_node_t);
		}
			break;
	case 's':
	case 'S':
		printf("输入剧目ID：");
		scanf("%d",&id);	flu();
		if(Play_Perst_SelectByID(id,&pos))
			Schedule_UI_MgtEntry(id);
		else
			printf("该剧目不存在!\n");	break;
	case 'q':
	case 'Q':
		printf("输入ID:");
		scanf("%d",&id);
		Play_UI_Query(id);
			break;
	case 'a':
	case 'A':
		if(Play_UI_Add())
                                paging.totalRecords = Play_Srv_FetchAll(head);
		List_Paging(head, paging, play_node_t);
			break;
	case 'd':
	case 'D':
		printf("输入ID:");
		scanf("%d",&id);
		if(Play_UI_Delete(id))
			paging.totalRecords = Play_Srv_FetchAll(head);
		List_Paging(head, paging, play_node_t);
			break;
	case 'u':
	case 'U':
		printf("输入ID:");
		scanf("%d",&id);	flu();
		if(Play_UI_Modify(id))
		{
			printf ("修改成功！\n");	printf("按Enter键继续...");	flu();
			Play_Srv_FetchAll(head);
			List_Paging(head, paging, play_node_t);
		}
		else
		{
			printf ("修改失败！\n");	printf("按Enter键继续...");	flu();
		}
			break;
	}

	}while('r'!= choice && 'R' != choice);
	//销毁
	List_Destroy(head,play_node_t);
	}
}


//添加新剧目界面
int Play_UI_Add(void)
{
	int n;
	int recCount=0;
	play_t play;
	char choice;
	
loop:	play.id = EntKey_Srv_CompNewKey("play");
	printf ("剧目名称：");
	scanf ("%s",play.name);	flu();
	printf("影片类型:\n");
loop1:	printf ("1.电影   2.戏剧   3.音乐   请选择： ");
	scanf ("%d",&n);	flu();
	switch(n)
	{
		case 1 : play.type = (play_type_t)1;break;
		case 2 : play.type = (play_type_t)2;break;
		case 3 : play.type = (play_type_t)3;break;
		default : printf("输入错误,请重新输入!\n");	goto loop1;
	}
	printf ("剧目出品地区：");
	scanf ("%s",play.area);	flu();
	printf ("剧目等级：\n");
	printf ("1.儿童   2.青年   3.成人   请选择：");
loop2:	scanf ("%d",&n);	flu();
        switch(n)
        {
                case 1 : play.rating = (play_rating_t)1;break;
                case 2 : play.rating = (play_rating_t)2;break;
                case 3 : play.rating = (play_rating_t)3;break;
                default : printf("输入错误,请重新输入!\n");	goto loop2;

        }

	printf ("时长（分钟）：");
	scanf ("%d",&play.duration);	flu();
	printf ("输入上线日期（年 月 日以空格分割）：");
	scanf ("%d %d %d",&play.start_date.year,&play.start_date.month,&play.start_date.day);	flu();
	printf ("输入下线日期（年 月 日以空格分割）：");
	scanf ("%d %d %d",&play.end_date.year,&play.end_date.month,&play.end_date.day);	flu();
	printf ("票价：");
	scanf ("%d",&play.price);	flu();

	if (Play_Srv_Add(&play)){
		printf ("添加成功！\n");
		recCount++;
	}
	else
		printf ("添加失败！\n");
	printf ("是否继续添加(A/a继续,按其他返回):");
	scanf ("%c",&choice);	flu();
	if (choice == 'a' || choice == 'A')
		goto loop;

	else
		return recCount;
}
//根据ID修改界面
int Play_UI_Modify(int id){
	play_t play;
	int rtn = 0;
	int n;
	play_list_t list;
	int playcount;
	char type[10];
	char rating[10];
	if (!Play_Srv_FetchByID(id,&play)){
			printf ("无剧目！按任意键返回\n");
			getchar();
			return 0;
	}	
	if (play.type == (play_type_t)1)
		strcpy(type,"电影");
	else if (play.type == (play_type_t)2)
		strcpy(type,"戏剧");
	else if (play.type == (play_type_t)3)
		strcpy(type,"音乐");
	if (play.rating == (play_rating_t)1)
                strcpy(rating,"儿童");
        else if (play.rating == (play_rating_t)2)
                strcpy(rating,"青年");
        else if (play.rating == (play_rating_t)3)
                strcpy(rating,"成人");
	printf ("===============================================================================================================================\n");
	printf ("*******************************************************原 剧 目 信 息**********************************************************\n");
	printf ("-------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|%6s%25s%20s%15s%15s%15s%20s%20s%15s|\n","剧目ID","剧目名称","剧目类型","地区","适宜人群","时长","上映时间","下线日期","票价");
	printf ("%5d%20s%20s%15s%10s%14d分%8d年%2d月%2d日%8d年%2d月%2d日%7d\n",play.id,play.name,type,play.area,rating,play.duration,play.start_date.year,play.start_date.month,play.start_date.day,play.start_date.year,play.start_date.month,play.start_date.day,play.price);
	printf ("===============================================================================================================================\n");
        printf ("******************************************************新 剧 目 信 息***********************************************************\n");
        printf ("-------------------------------------------------------------------------------------------------------------------------------\n");
	printf ("新剧目名称：");
        scanf ("%s",play.name);	flu();
        printf ("剧目类型：\n");
loop1:  printf ("1.电影   2.戏剧   3.音乐    请选择： ");
        scanf ("%d",&n);	flu();
        switch(n)
        {
                case 1 : play.type = (play_type_t)1;break;
                case 2 : play.type = (play_type_t)2;break;
                case 3 : play.type = (play_type_t)3;break;
                default : goto loop1;
        }
        printf ("剧目出品地区：");
        scanf ("%s",play.area);		flu();
        printf ("剧目等级：\n");

loop2:  printf ("1.儿童   2.青年   3.成人    请选择：");

        scanf ("%d",&n);	flu();

        switch(n)

        {

                case 1 : play.rating = (play_rating_t)1;break;
                case 2 : play.rating = (play_rating_t)2;break;
                case 3 : play.rating = (play_rating_t)3;break;
                default : goto loop2;
        }
        printf ("时长（分钟）：");
        scanf ("%d",&play.duration);  flu();      
	printf ("上映日期（年 月 日,以空格分隔）：");
        scanf ("%d %d %d",&play.start_date.year,&play.start_date.month,&play.start_date.day);
	printf ("下线日期（年 月 日,以空格分隔）：");
        scanf ("%d %d %d",&play.end_date.year,&play.end_date.month,&play.end_date.day);
        printf ("票价：");
        scanf ("%d",&(play.price));	flu();
	if (Play_Srv_Modify(&play))
		rtn = 1;

        return rtn;
}

//根据ID删除剧目界面
int Play_UI_Delete(int id){
       int rtn = 0;flu();
	if (Play_Srv_DeleteByID(id)){
		
		printf ("删除成功！按Enter键返回\n");
		rtn = 1;
	}
	else
		printf ("删除失败！按Enter键返回\n");
	flu();
	return rtn;
}

       
//根据ID查询剧目界面
int Play_UI_Query(int id){
	play_t play;
	char type[10];
	char rating[10];
	getchar();
        int rtn = 0;
	if (Play_Srv_FetchByID(id,&play)){
		if (play.type == (play_type_t)1)
			strcpy(type,"电影");
		else if (play.type == (play_type_t)2)
			strcpy(type,"戏剧");
		else if (play.type == (play_type_t)3)
			strcpy(type,"音乐");
		if (play.rating == (play_rating_t)1)
       	         	strcpy(rating,"儿童");
	   	else if (play.rating == (play_rating_t)2)
        	        strcpy(rating,"青年");
      		else if (play.rating == (play_rating_t)3)
              		 strcpy(rating,"成人");
		printf ("===============================================================================================================================\n");	
		printf ("*******************************************************原 剧 目 信 息**********************************************************\n");
		printf ("-------------------------------------------------------------------------------------------------------------------------------\n");
		printf("|%6s%25s%20s%15s%15s%15s%20s%20s%15s|\n","剧目ID","剧目名称","剧目类型","地区","适宜人群","时长","上映时间","下线日期","票价");
		printf ("%5d%20s%20s%15s%10s%14d分%8d年%2d月%2d日%8d年%2d月%2d日%7d\n",play.id,play.name,type,play.area,rating,play.duration,play.start_date.year,play.start_date.month,play.start_date.day,play.start_date.year,play.start_date.month,play.start_date.day,play.price);
		printf ("===============================================================================================================================\n");
		printf ("查询到此剧目！按Enter键返回\n");		
		rtn = 1;
	}
	else
		printf ("未查询到此剧目！按Enter键返回\n");
	flu();
	return rtn;
}
