#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"

#include <stdio.h>
#include <stdlib.h>

static const int SCHE_PAGE_SIZE = 5;

void Schedule_UI_ListAll(void) {
	int id;
	printf("请输入演出计划ID：");	scanf("%d",&id);	flu();
	Schedule_UI_Query(id);
}

int Schedule_UI_Add(int play_id) {

	schedule_t schedu;
	studio_t studio;
	play_t play;
	int newCount = 0;
	char key;
	do{
		printf("请输入演出厅ID:");			scanf("%d",&schedu.studio_id);	flu();
		if (Studio_Srv_FetchByID(schedu.studio_id,&studio) == 0)
		{
			printf("添加失败!输入的演出厅ID不存在!\n");
		}
		else{
				schedu.play_id = play_id;
				printf("请输入演出日期(年月日,以空格分隔):");	scanf("%d %d %d",&schedu.date.year,&schedu.date.month,&schedu.date.day);
				printf("请输入演出时间(时分秒,以空格分隔):");	scanf("%d %d %d",&schedu.time.hour,&schedu.time.minute,&schedu.time.second);	flu();
				schedu.seat_count = studio.seatsCount;
				schedu.id = EntKey_Srv_CompNewKey("schedule");
				if (Schedule_Srv_Add(&schedu))
				{
					if (Ticket_Srv_AddBatch(schedu.id,studio.id))
						printf("票生成成功!\n");
					printf("添加成功!");		newCount++;
				}
				else{
					printf("添加失败!");
				}
		}
		
		printf("是否继续(输入A/a继续,输入其他返回)：");		scanf("%c",&key);	flu();
	}while(key == 'a' || key == 'A');
	
       return newCount;
}

int Schedule_UI_Modify(int id){
	
	int tempId;
	schedule_t buf;
	studio_t studio;
	play_t play;
	if (Schedule_Srv_FetchByID(id,&buf) == 0){
		printf("修改失败!该演出计划的ID不存在!\n");		return 0;
	}
	else{
		if (Studio_Srv_FetchByID(buf.studio_id,&studio) == 0)
		{
			printf("演出厅信息读取失败!\n");	return 0;
		}
		if (Play_Srv_FetchByID(buf.play_id,&play) == 0)
		{
			printf("剧目信息读取失败!\n");		return 0;
		}
		printf("|----------------------------------------------------演 出 计 划 修 改--------------------------------------------------------|\n");
		printf("%10s%15s%23s%20s%22s%18s%23s\n","ID","剧目ID","剧目名字","演出厅ID","演出厅名称","演出日期","演出时间");
		printf("%10d%10d%20s%15d%18s%10d年%2d月%2d日%8d时%2d分%2d秒\n",buf.id,buf.play_id,play.name,buf.studio_id,studio.name,buf.date.year,buf.date.month,buf.date.day,buf.time.hour,buf.time.minute,buf.time.second);
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
loop1:	printf("请输入新剧目ID:");	scanf("%d",&tempId);	flu();
		if (Play_Srv_FetchByID(tempId,&play) == 0)
		{
			printf("剧目ID不存在!\n");	goto loop1;	
		}
		buf.play_id = tempId;
loop2:	printf("请输入演出厅ID:");	scanf("%d",&tempId);	flu();
		if (Studio_Srv_FetchByID(tempId,&studio) == 0)
		{
			printf("演出厅ID不存在!\n");	goto loop2;
		}
		buf.studio_id = tempId;
		printf("请输入演出日期(年月日,以空格分隔):");	scanf("%d %d %d",&buf.date.year,&buf.date.month,&buf.date.day);
		printf("请输入演出时间(时分秒,以空格分隔):");	scanf("%d %d %d",&buf.time.hour,&buf.time.minute,&buf.time.second);	flu();
		buf.seat_count = studio.seatsCount;
		if (Schedule_Srv_Modify(&buf))
		{
			if (Ticket_Srv_DeleteBatch(id))
			{
				if (Ticket_Srv_AddBatch(id,studio.id))
				{
					printf("已重新生成票!\n");
				}
				else{
					printf("重新生成票失败!\n");	return 0;
				}
			}
			else
			{
				printf("旧票删除失败!\n");	return 0;
			}
		}
		else
		{	
			printf("修改失败!\n");	return 0;
		}
	}
	
	return 1;
}

int Schedule_UI_Delete(int id){

	if (Schedule_Srv_DeleteByID(id))
	{
		printf("删除演出计划成功!输入Enter键返回......");	flu();
	}
	else{
		printf("删除演出计划失败!输入Enter键返回......");	flu();
		return 0;
	}
	
	return 1;
}
int Schedule_UI_Query(int id){

	schedule_t buf;
	studio_t studio;
	play_t play;
	if (Schedule_Srv_FetchByID(id,&buf))
	{
		if (Studio_Srv_FetchByID(buf.studio_id,&studio) == 0)
		{
			printf("演出厅信息读取失败!\n");	return 0;
		}
		if (Play_Srv_FetchByID(buf.play_id,&play) == 0)
		{
			printf("剧目信息读取失败!\n");		return 0;
		}
		printf("|=============================================================================================================================|\n");
		printf("|----------------------------------------------------演 出 计 划 查 询--------------------------------------------------------|\n");
		printf("%10s%15s%23s%20s%22s%18s%23s\n","ID","剧目ID","剧目名字","演出厅ID","演出厅名称","演出日期","演出时间");
		printf("%10d%10d%20s%15d%18s%10d年%2d月%2d日%8d时%2d分%2d秒\n",buf.id,buf.play_id,play.name,buf.studio_id,studio.name,buf.date.year,buf.date.month,buf.date.day,buf.time.hour,buf.time.minute,buf.time.second);
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
		printf("已查询到!按Enter键返回：");	flu();	return 1;
	}
	else{
		printf("未查询到!按Enter键返回：");	flu();	return 0;
	}
	
}

/*以列表模式显示给定剧目的演出计划信息*/
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging){}

void Schedule_UI_MgtEntry(int play_id){

	int i;
	play_t play;
	studio_t studio;
	schedule_list_t pos;
	char choice;	int tempID;
	schedule_list_t pHead;
	List_Init(pHead,schedule_node_t);
	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SCHE_PAGE_SIZE;
	paging.totalRecords = Schedule_Srv_FetchAll(pHead);
	Paging_Locate_FirstPage(pHead,paging);
	do{
		
		system("clear");
		printf("|=============================================================================================================================|\n");
		printf("|----------------------------------------------------演 出 计 划 管 理--------------------------------------------------------|\n");
		printf("%10s%15s%23s%20s%22s%18s%23s\n","ID","剧目ID","剧目名字","演出厅ID","演出厅名称","演出日期","演出时间");
		Paging_ViewPage_ForEach(pHead,paging,schedule_node_t,pos,i)
		{
			if (Play_Srv_FetchByID(pos->data.play_id,&play) == 0)
			{
				printf("获取剧目失败!\n");
			}
			if (Studio_Srv_FetchByID(pos->data.studio_id,&studio) == 0)
			{
				printf("获取演出厅失败!\n");
			}
			printf("%10d%10d%20s%15d%18s%10d年%2d月%2d日%8d时%2d分%2d秒\n",pos->data.id,pos->data.play_id,play.name,pos->data.studio_id,studio.name,pos->data.date.year,pos->data.date.month,pos->data.date.day,pos->data.time.hour,pos->data.time.minute,pos->data.time.second);
		}
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
		printf("------------------------总条数:%2d -------------------------------------------------------- 页数 %2d/%2d -------------------------\n",paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
	
			printf("|-----------------[p]上一页 | [N]|下一页 | [Q]查询计划 | [A]添加计划 | [D]删除计划 | [U]修改计划 | [R]返回上一级--------------|\n");
			printf("|=============================================================================================================================|\n");
		printf("请选择:");		scanf("%c",&choice);		flu();
		switch(choice)
		{
			case 'a':
			case 'A':
				if (Schedule_UI_Add(play_id))
					paging.totalRecords = Schedule_Srv_FetchAll(pHead);
					Paging_Locate_LastPage(pHead, paging, schedule_node_t);
				break;
			case 'D':
			case 'd':
				printf("请输入待删除计划的ID:");	scanf("%d",&tempID);	flu();
				if (Schedule_UI_Delete(tempID)){
					paging.totalRecords = Schedule_Srv_FetchAll(pHead);
					List_Paging(pHead, paging, schedule_node_t);
				}
				break;
			case 'u':
			case 'U':
				printf("输入待修改计划的ID:");		scanf("%d",&tempID);	flu();
				if (Schedule_UI_Modify(tempID))
				{
					paging.totalRecords = Schedule_Srv_FetchAll(pHead);
					List_Paging(pHead, paging, schedule_node_t);
					printf("修改成功!输入Enter键返回:");	flu();
				}
				else{
					printf("修改失败!输入Enter键返回:");	flu();
				}
				break;
			case 'q':
			case 'Q':
				printf("请输入演出计划ID:");	scanf("%d",&tempID);	flu();
				Schedule_UI_Query(tempID);
				break;
			case 'P':
			case 'p':
				if(!Pageing_IsFirstPage(paging)){
					Paging_Locate_OffsetPage(pHead,paging,-1,schedule_node_t);
				}
				break;	
			case 'N':
			case 'n':
				if(!Pageing_IsLastPage(paging)){
					Paging_Locate_OffsetPage(pHead,paging,1,schedule_node_t);
				}
				break;
		}
		
	}while('r'!= choice && 'R' != choice);

}
