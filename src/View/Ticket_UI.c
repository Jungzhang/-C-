#include "Ticket_UI.h"

#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"

#include <stdio.h>
#include <stdlib.h>

//根据状态返回对应表示状态符号
inline char Ticket_UI_Status2Char(ticket_status_t status) {

	// 请补充完整
       return 'X';
}

void Ticket_UI_Print(int ID){
	// 请补充完整
}

//根据计划ID显示所有票
void Ticket_UI_ListBySch(const schedule_t *sch,	ticket_list_t tickList, seat_list_t seatList) {
	// 请补充完整
}

void ListTickets(void){
	// 请补充完整
}


int UpdateTicket(int id){
	// 请补充完整
       return 1;
}


int QueryTicket(int id){

	// 请补充完整
       return 1;
}
