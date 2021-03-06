/*
 *  Seat.c
 *
 *  Created on: 2015年6月12日
 *  Author: lc
 */
#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"
#include "../Persistence/Seat_Persist.h"
#include "EntityKey.h"
// 单个添加座位,成功返回1,失败返回0
inline int Seat_Srv_Add(const seat_t *data){
       return Seat_Perst_Insert(data);
}
// 批量添加座位,成功返回1,失败返回0
inline int Seat_Srv_AddBatch(seat_list_t list){
	return Seat_Perst_InsertBatch(list);
}
// 修改座位函数,成功返回1,失败返回0
inline int Seat_Srv_Modify(const seat_t *data){
	return Seat_Perst_Update(data);
}
// 根据座位ID删除其座位的函数,成功返回1,失败返回0
inline int Seat_Srv_DeleteByID(int ID){
	return Seat_Perst_DeleteByID(ID);
}
// 根据ID获取座位函数,成功返回1,失败返回0
inline int Seat_Srv_FetchByID(int ID, seat_t *buf){
	return Seat_Perst_SelectByID(ID,buf);
}
// 根据演出厅ID删除其所有座位函数,成功返回1,失败返回0
inline int Seat_Srv_DeleteAllByRoomID(int roomID){
       return Seat_Perst_DeleteAllByRoomID(roomID);
}

//根据演出厅ID载入座位
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID){
	int SeatCount;
	SeatCount = Seat_Perst_SelectByRoomID(list,roomID);
	Seat_Srv_SortSeatList(list);
        return SeatCount;
}

/*根据放映厅ID提取有效的座位*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
	int SeatCount,GoodSeat = 0;
        SeatCount = Seat_Perst_SelectByRoomID(list,roomID);
	if(list ->data.status == (seat_status_t)1)
		GoodSeat++;
	SeatCount = GoodSeat;
	Seat_Srv_SortSeatList(list);
        return SeatCount;
}


//根据行、列数初始化演出厅的座位
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,int colsCount) {
	int seatID;
	int r,c;
	seat_list_t pNew,pTemp;
	seatID = EntKey_Srv_CompNewKeys("seat",(rowsCount * colsCount));
	for(r = 0;r < rowsCount;r++)
	{
		for(c = 0;c < colsCount;c++)
		{
			pNew = (seat_list_t)malloc(sizeof(seat_node_t));
			if (pNew == NULL) return 0;
			pNew->data.roomID = roomID;
			pNew->data.row = r +1;
			pNew->data.column = c +1;
			pNew->data.status = (seat_status_t)1;
			List_AddTail(list, pNew);
		}
	}
	pTemp = list->next;
	while((seatID < (seatID + rowsCount * colsCount)) && pTemp != list)
	{
		pTemp->data.id = seatID;
		seatID++;	pTemp = pTemp->next;
	}
	Seat_Perst_InsertBatch(list);
	return 1;
}

//对座位链表list进行按座位行号和列号排序
void Seat_Srv_SortSeatList(seat_list_t list) {
	seat_list_t listLeft;
	seat_node_t *p;
    if(list == list->next)
		return;
	listLeft = list->next;
	list->prev->next = NULL;
	list->next =list;
	list->prev =list;
	while(listLeft != NULL)
	{
		p = listLeft;	listLeft = listLeft->next;
		Seat_Srv_AddToSoftedList(list,p);
	}
}

//将结点node加入到已排序链表list中
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
	seat_list_t pTemp = list->next;
        if(pTemp == list){
		List_AddTail(list,node);	return ;
	}
	pTemp = list->next;
	while(1)
	{
		if (pTemp != list)
		{
			if(!((pTemp->data.row < node->data.row) || ((pTemp->data.row == node->data.row) && (pTemp->data.column < node->data.column))))
			{
				List_InsertBefore(pTemp,node);	break;
			}
			pTemp = pTemp->next;
		}
		else
		{
			List_AddTail(list,node);	break;
		}
	}
	
}
// 根据行列号获取座位
inline seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {

	seat_list_t pTemp = list->next,pTarg = NULL;
	while(pTemp != list)
	{
		if ((pTemp->data.row == row) && (pTemp->data.column == column))
		{
			pTarg = pTemp;	break;
		}
		pTemp = pTemp->next;
	}
	return pTarg;
}


inline seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
        seat_list_t pNew = list->next;
	while(pNew != list)
	{
		if(pNew ->data.row == rowID && pNew ->data.column < rowID)
			return pNew;
		pNew = pNew->next;
	}
        return NULL;
}
