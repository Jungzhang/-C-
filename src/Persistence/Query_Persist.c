#include "Query_Persist.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include "../Service/Studio.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>
#include <string.h>

static const char PLAY_DATA_FILE[] = "Play.dat";
static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";
static const char STUDIO_DATA_FILE[] = "Studio.dat";
static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char SEAT_DATA_FILE[] = "Seat.dat";
//Query play by name
//0: error, the play is not exits
//1: the play exits and storage the information in the struct
int Query_PlayName(char *playName, play_t *_play)
{
	// 请补充完整
       return 1;
}
//query schedule by play id
//return 0: error the schedule is note exits
//return 1:the schedule exits and storage the information in struct
int Query_Schedule_By_PlayId(int playId, schedule_t *sched)
{
	// 请补充完整
       return 1;
}
void Query_Studio_By_Schedule(int id, studio_t *studio)
{
	// 请补充完整
}
//已经售出的票
int Sold_Ticket_Count(int id)
{
	// 请补充完整
       return 1;
}

int Seat_Number_Count(int studio_id)
{
	// 请补充完整
       return 1;
}
