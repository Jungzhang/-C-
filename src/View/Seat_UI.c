/*
 *  Seat_UI.c
 *
 *  Created on: 2015年5月23日
 *  Author: lc
 */

#include "Seat_UI.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/List.h"
#include <stdio.h>

void flu()
{
	char ch;while((ch=getchar())!='\n'&&ch!=EOF);
}

//根据座位状态返回对应表示状态的符号
inline char Seat_UI_Status2Char(seat_status_t status) 
{
	char rtn;
	if(status == (seat_status_t)0)
		rtn=' ';
	else if(status == (seat_status_t)1)
		rtn='#';
	else if(status == (seat_status_t)9)
		rtn='~';

	return rtn;
}

//根据状态符号返回座位状态
inline seat_status_t Seat_UI_Char2Status(char statusChar) 
{
	seat_status_t tmp;
	if(statusChar == '#')
		tmp = (seat_status_t)1;
	else if(statusChar == '~')
		tmp = (seat_status_t)9;
	else if(statusChar ==' ')
		tmp = (seat_status_t)0;

	return tmp;
}

//座位管理函数
void Seat_UI_MgtEntry(int roomID) 
{
	system("clear");
	flu();
	char choice;
	int i = 0,j,num;
	seat_list_t head,temp;
	studio_t buf;
	List_Init(head,seat_node_t);
	if(Studio_Srv_FetchByID(roomID,&buf)==0)
	{
		printf("未找到此ID对应的放映厅！\n");	
	}
	else
	{
		if(Seat_Srv_FetchByRoomID(head,roomID) == 0)
		{
			Seat_Srv_RoomInit(head,roomID,buf.rowsCount,buf.colsCount);buf.seatsCount = buf.rowsCount * buf.colsCount;
			if (Studio_Srv_Modify(&buf) == 0)
			{
				printf("\t\t演出厅座位初始化存档失败!\n");
				return;
			}
		}
		
		while(1)
		{
			Seat_Srv_FetchByRoomID(head,roomID);
			temp = head;		temp = temp->next;
			printf("**************************************************************************************************\n");
			printf("----------------------------------- 座 位 状 态--------------------------------------------------\n");
			for (i = 1; i <= buf.rowsCount; i++)
			{
				while(temp != head)
				{
					if (temp->data.row != i)
					{
						printf("\n");	break;
					}
					else
					{
						printf("%2c",Seat_UI_Status2Char(temp->data.status));
						temp = temp->next;
					}
				}
			} 
		/*	while (temp != head)
			{
				printf("%d\t",i); i++;	temp = temp->next;
			} */
			printf("\n");
			printf("====================================================================================================\n");
			printf("\n\t\t\t|***************************************************|\n");
			printf("\t\t\t|------------------- 座 位 管 理--------------------|\n");
			printf("\t\t\t|***************************************************|\n");
			printf("\t\t\t|                 'a'|'A':添加座位                  |\n");
			printf("\t\t\t|                 'u'|'U':修改座位                  |\n");
			printf("\t\t\t|                 'd'|'D':删除座位                  |\n");
			printf("\t\t\t|                 'r'|'R':返回上一级                |\n");
			printf("\t\t\t|===================================================|\n");
		loop:	printf("\t\t请选择:");
			scanf("%c",&choice);
			flu();
			switch(choice)
			{
				case'a':
				case'A':
					buf.seatsCount = (buf.seatsCount + Seat_UI_Add(head,roomID,buf.rowsCount,buf.colsCount));
					if (Studio_Srv_Modify(&buf) == 0)
					{
						printf("\t\t个数更新失败!演出厅座位初始化存档失败!\n");
					}
					break;
				case'u':
				case'U':
					Seat_UI_Modify(head,buf.rowsCount,buf.colsCount);
					break;
				case'd':
				case'D':
					buf.seatsCount = (buf.seatsCount - Seat_UI_Delete(head,buf.rowsCount,buf.colsCount));
					if (Studio_Srv_Modify(&buf) == 0)
					{
						printf("\t\t个数更新失败!演出厅座位初始化存档失败!\n");
					}
					break;
				case 'r':
				case 'R':
					return ;
				default:
					goto loop;
			}
	 	}
	}
	List_Destroy(head,seat_node_t);
}

//添加座位函数返回添加个数
int Seat_UI_Add(seat_list_t list, int roomID, int rowsCount, int colsCount) 
{
	int newRecCount=0,i;
	char choice,status;
	seat_t rec;
	do
	{
		system("clear"); 
		printf("\n\t\t\t=======================================================\n");
		printf("\t\t\t****************  添  加  新  座  位  ***************\n");
		printf("\t\t\t-------------------------------------------------------\n");
	loop:	printf("\t\t请输入行号：");	scanf("%d",&(rec.row));		flu();
		printf("\t\t请输入列号：");	scanf("%d",&(rec.column));	flu();
		printf("\t\t\t=======================================================\n");
		if (Seat_Srv_FindByRowCol(list,rec.row,rec.column) != NULL)
		{
			printf("座位已存在，请重新输入!\n");	goto loop;
		}
		rec.id=EntKey_Srv_CompNewKey("seat");
		printf("\t\t请输入座位状态( #/ /~):");
		loop1:scanf("%c",&status);	flu();
		switch(status)
		{
			case '#':	rec.status = (seat_status_t)1;	break;
			case ' ':	rec.status = (seat_status_t)0;	break;
			case '~':	rec.status = (seat_status_t)9;	break;
			default :	printf("座位状态输入有误,请重新输入:");	goto loop1;
		}
		rec.roomID = roomID;
		if(Seat_Srv_Add(&rec))
		{
			newRecCount+=1;
			printf("\t座位添加成功.\n");
			Seat_Srv_FetchByRoomID(list,roomID);	Seat_Srv_SortSeatList(list);
		}
		else
			printf("\t座位添加失败.\n");
		printf("\t\t\t-------------------------------------------------------\n");
		printf("\t[A]继续添加, [R]返回上一级:");
		choice = getchar();	flu();
	} while('a'==choice || 'A'==choice);
	system("clear");
	return newRecCount;
}

//修改座位函数返回修改个数
int Seat_UI_Modify(seat_list_t list, int rowsCount, int colsCount) 
{
	int newRecCount = 0,temp_colu,temp_row;
	char choice,status;
	seat_list_t pTarg;
	do
	{
		printf("\n\t\t\t=======================================================\n");
		printf("\t\t\t****************  修  改  座  位  ***************\n");
		printf("\t\t\t-------------------------------------------------------\n");
		printf("\t\t请输入行：");	scanf("%d",&temp_row);	flu();
		printf("\t\t请输入列：");	scanf("%d",&temp_colu);	flu();
		printf("\t\t\t=======================================================\n");
		if ((pTarg = Seat_Srv_FindByRowCol(list,temp_row,temp_colu)) == NULL)
		{
			printf("\t\t未找到该座位!\n");
		}
		else
		{
			loop1:printf("请输入修改后的座位状态:");	
			scanf("%c",&status);	flu();
			switch(status)
			{
				case '#':	pTarg->data.status = (seat_status_t)1;	break;
				case ' ':	pTarg->data.status = (seat_status_t)0;	break;
				case '~':	pTarg->data.status = (seat_status_t)9;	break;
				default :	printf("座位状态输入有误,请重新输入!\n");	goto loop1;
			}
			if(Seat_Srv_Modify(&(pTarg->data)))
			{
				printf("\t\t修改成功.\n");
				newRecCount++;
			}
			else
				printf("\t\t修改失败.\n");
		}
		printf("\t\t\t-------------------------------------------------------\n");
		printf("[U]继续修改,[R]返回 :");
		scanf("%c",&choice);	flu();
	} while('u'==choice || 'U'==choice);
	system("clear");
	return newRecCount;
}

//删除座位函数返回删除个数
int Seat_UI_Delete(seat_list_t list, int rowsCount, int colsCount) 
{
	int newRecCount=0,row,column;
	seat_list_t pTemp = list->next;
	char choice;
	do{
		printf("输入待删除行号:");	scanf("%d",&row);	flu();
		printf("输入待删除列号:");	scanf("%d",&column);	flu();
		while(pTemp != list)
		{
			if ((pTemp->data.row == row) && (pTemp->data.column == column))
			{
				break;
			}
			pTemp = pTemp->next;
		}
		if((pTemp != list) && (Seat_Srv_DeleteByID(pTemp->data.id)))
		{
			printf("删除成功.\n");
			newRecCount++;
		}
		else
			printf("删除失败.\n");
		printf("\t\t\t-------------------------------------------------------\n");
		printf("[D]继续删除,[R]返回:");
		scanf("%c",&choice);	flu();
	 }while('d'==choice || 'D'==choice);
	system("clear");
	return newRecCount;
}
