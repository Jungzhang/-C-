#include "Ticket.h"
#include "EntityKey.h"

#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"
#include "../Persistence/Schedule_Persist.h"
#include "../Service/Seat.h"

#include <stdio.h>
#include <stdlib.h>
//批量生成主键为Schedule_id的演出计划的票，每张票对应主键为studio_id演出厅的一个可用座位
int Ticket_Srv_AddBatch(int schedule_id, int studio_id){
	int count,newCount = 0;
	seat_node_t *pos;
	seat_list_t list_s;
	ticket_list_t list_t;
	ticket_node_t *pNew;
	schedule_t schtemp;
	play_t playtemp;
	if (Schedule_Srv_FetchByID(schedule_id,&schtemp) == 0)
	{
		printf("获取演出计划失败!\n");	return 0;
	}
	if (Play_Srv_FetchByID(schtemp.play_id,&playtemp) == 0)
	{
		printf("获取剧目信息失败!\n");	return 0;
	}
	List_Init(list_s,seat_node_t);
	count = Seat_Srv_FetchByRoomID(list_s,studio_id);
	
	if (count!=0)
	{
		pos = list_s->next;
		List_Init(list_t,ticket_node_t);
		while(pos!=list_s)
		{
			pNew = (ticket_node_t*) malloc(sizeof(ticket_node_t));
			pNew->data.id = EntKey_Srv_CompNewKey("ticket");
			pNew->data.schedule_id = schedule_id;
			pNew->data.seat_id = pos->data.id;
			pNew->data.price = playtemp.price;
			pNew->data.status = (ticket_status_t)0;
			newCount++;
			List_AddTail(list_t,pNew);
			pos=pos->next;
		}
		Ticket_Perst_Insert(list_t);
	}
	else
		return 0;
	return newCount;
		
}
//批量删除主键为Schedule_id的演出计划的票
int Ticket_Srv_DeleteBatch(int schedule_id) {
	return Ticket_Perst_Delete(schedule_id);
}
//
int Ticket_Srv_Modify(const ticket_t * data){
	return Ticket_Perst_Update(data);
}

int Ticket_Srv_FetchByID(int ID, ticket_t *buf) {
	return Ticket_Perst_SelectByID(ID, buf);
}


//根据座位ID在list中找对应票
inline ticket_node_t * Ticket_Srv_FindBySeatID(ticket_list_t list, int seat_id){
		assert(NULL!=list);
		ticket_node_t *ptr=list->next;
		while(ptr!=list){
			if(ptr->data.id==seat_id)
						return ptr;
			else
						ptr=ptr->next;
		}
       return NULL;
}


//根据计划ID提取所有演出票
int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id) {

      return Ticket_Perst_SelectBySchID(list, schedule_id);
}

//根据演出计划ID，统计上座率及票房，返回票房数收入
int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount, int *totalCount){
	// 请补充完整
       return 1;
}


