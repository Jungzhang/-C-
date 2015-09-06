/*
 * Studio_UI.c
 *
 *  Created on: 2015年4月24日
 *      Author: Administrator
 */
#include "Studio_UI.h"

#include "../Common/List.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"
#include "../Service/EntityKey.h"
#include "Seat_UI.h"

static const int STUDIO_PAGE_SIZE = 10;

#include <stdio.h>

void Studio_UI_MgtEntry(void) {
	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("clear");
		printf("\n\t\t\t============================================================================\n");
		printf(
				"\t\t\t*************************** 演 出 厅 信 息 列 表 ***************************\n");
		printf(
				"\t\t\t----------------------------------------------------------------------------\n");
		printf("\t\t%20s%20s%20s%20s%20s\n", "演出厅ID", "演出厅名称", "座位行数",
				"座位列数", "座位总数");
		printf(
				"\t\t\t----------------------------------------------------------------------------\n");
		//显示数据
		Paging_ViewPage_ForEach(head, paging, studio_node_t, pos, i){
			printf("\t\t%15d%15s%15d%15d%18d\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
		}

		printf("\t\t\t------- 总条数:%2d -------------------------------------- 页码 %2d/%2d --------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t****************************************************************************\n");
		printf("\t\t\t[P]上一页|[N]下一页 | [A]添加|[D]删除|[U]修改 | [S]座位管理 | [R]返回上一级");
		printf("\n\t\t\t============================================================================\n");
		printf("\t请选择:");		setbuf(stdin,NULL);
		scanf("%c", &choice);	setbuf(stdin,NULL);
	//	system("clear");

		switch (choice) {
		case 'a':
		case 'A':
			if (Studio_UI_Add()) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
			}
			break;
		case 'd':
		case 'D':
			printf("\t请输入ID:");
			scanf("%d", &id);	setbuf(stdin,NULL);
			if (Studio_UI_Delete(id)) {	//重新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 'u':
		case 'U':
			printf("\t请输入演出厅ID:");
			scanf("%d", &id);	setbuf(stdin,NULL);
			if (Studio_UI_Modify(id)) {	//重新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 's':
		case 'S':
			printf("\t请输入演出厅ID:");
			scanf("%d", &id);
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, studio_node_t);
}

//添加演出厅信息,成功返回添加个数,失败返回0
int Studio_UI_Add(void) {
	studio_t rec;
	int newRecCount = 0;
	char choice;
	seat_list_t list;
	List_Init(list,seat_node_t);
	do {
		/*system("cls");*/
		printf("\n\t\t\t=======================================================\n");
		printf("\t\t\t****************  添 加 新 演 出 厅  ****************\n");
		printf("\t\t\t-------------------------------------------------------\n");
		printf("\t\t演出厅名字:");			scanf("%s",rec.name);
		printf("\t\t演出厅座位行数:");		scanf("%d", &(rec.rowsCount));
		printf("\t\t演出厅座位列数:");		scanf("%d", &(rec.colsCount));	setbuf(stdin,NULL);
		rec.seatsCount = 0;
		printf("\t\t\t=======================================================\n");

		//获取主键
		rec.id = EntKey_Srv_CompNewKey("Studio");

		if (Seat_Srv_RoomInit(list, rec.id, rec.rowsCount,rec.colsCount))
		{
				rec.seatsCount = rec.rowsCount * rec.colsCount;
				printf("座位初始化成功!\n");
		}
		if (Studio_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("\t演出厅添加成功!\n");
		} else
			printf("\t演出厅添加失败\n");
		printf("\t\t\t-------------------------------------------------------\n");
		printf("\t[A]继续添加, [R]返回上一级");
		scanf("%c", &choice);	setbuf(stdin,NULL);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

//放映厅修改界面,成功返回1,失败返回0
int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("您要修改的演出厅不存在,请按Enter键返回!\n");
		getchar();	setbuf(stdin,NULL);
		return 0;
	}

	printf("\t\t\t\n=======================================================\n");
	printf("\t\t\t**************** 修 改 管 理 厅 信 息  ****************\n");
	printf("\t\t\t-------------------------------------------------------\n");
	printf("\t演出厅ID:%d\n", rec.id);
	printf("\t演出厅名字:%s:", rec.name);
	setbuf(stdin,NULL);
	scanf("%s",rec.name);	setbuf(stdin,NULL);

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if (seatcount) {
		do {			//如果座位文件中已有座位信息，则更新的行列必须比以前大，否则不允许更改
			printf("\t需新更改座位行数 >= [%d]:", rec.rowsCount);
			scanf("%d", &(newrow));
			printf("\t需新更改座位列数 >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));	setbuf(stdin,NULL);
		} while (newrow < rec.rowsCount || newcolumn < rec.colsCount);
		rec.rowsCount = newrow;
		rec.colsCount = newcolumn;
		rec.seatsCount = seatcount;
	} else {
		printf("\t请输入座位行数:");
		scanf("%d", &rec.rowsCount);
		printf("\t请输入座位列数:");
		scanf("%d", &rec.colsCount);
		rec.seatsCount = 0;
	}

	printf("\t\t\t-------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf("放映厅信息修改成功,请按Enter键继续!\n");
	} else
		printf("放映厅信息修改失败,请按Enter键返回\n");

	getchar();	setbuf(stdin,NULL);
	return rtn;
}

//放映厅信息删除,成功返回1,失败返回0
int Studio_UI_Delete(int id) {

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		//在删除放映厅时，同时根据放映厅id删除座位文件中的座位
		if (Seat_Perst_DeleteAllByRoomID(id))
			printf("座位信息删除成功!\n");
		printf("放映厅信息删除成功,请按Enter键继续!\n");
		rtn = 1;
	} else {
		printf("演出厅删除失败,可能原因为其不存在,按Enter键返回!\n");
	}

	getchar();	setbuf(stdin,NULL);
	return rtn;
}

