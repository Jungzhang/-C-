#include "Ticket_Persist.h"
//#include "../Persistence/Common_Persist.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>

static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char TICKET_DATA_TEMP_FILE[]="TicketTemp.dat";

//将list链表上的所有票信息数据写入票数据文件中
int Ticket_Perst_Insert(ticket_list_t list)
{
	assert(NULL != list);
	FILE *fp;	
	int rtu = 0;
	ticket_list_t pTemp = list->next;
	fp = fopen(TICKET_DATA_FILE,"ab");
	if (fp ==NULL)
        {  
                printf("文件%s打开失败!\n","Ticket.dat");
		return rtu;
        }
	while(pTemp != list)
	{
		fwrite(&(pTemp->data),sizeof(ticket_t),1,fp);
		pTemp = pTemp->next;
		rtu = 1;
	}
	fclose(fp);

	return rtu;
}

// 从文件中删除与主键为schedule_id相关的票数据
int Ticket_Perst_Delete(int schedule_id)
{
	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。
	//对原始数据文件重命名
	if(rename(TICKET_DATA_FILE, TICKET_DATA_TEMP_FILE)<0)
	{
		printf("不能打开文件: %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(TICKET_DATA_TEMP_FILE, "rb+");
	if (NULL == fpSour )
	{
		printf("不能打开文件: %s!\n", TICKET_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(TICKET_DATA_FILE, "wb+");
	if ( NULL == fpTarg ) 
	{
		printf("不能打开文件: %s!\n", TICKET_DATA_TEMP_FILE);
		return 0;
	}

	ticket_t buf;

	int found = 0;
	while (!feof(fpSour))
	{
		if (fread(&buf, sizeof(ticket_t), 1, fpSour))
		{
			if (schedule_id == buf.schedule_id)
			{
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(ticket_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(TICKET_DATA_TEMP_FILE);
	return found;
}

// 将data所指的票信息更新入演出计划数据文件中
int Ticket_Perst_Update(const ticket_t * data) 
{
	assert(NULL != data);
	FILE *fp;
	int found = 0;
	ticket_t buf;
	fp = fopen(TICKET_DATA_FILE,"rb+");
	if (fp == NULL)
	{
		printf("文件%s打开失败!\n",TICKET_DATA_FILE);
		return found;
	}
	while(!feof(fp))
	{
		if (fread(&buf,sizeof(ticket_t),1,fp))
		{
			if (buf.id == data->id)
			{
				fseek(fp,-sizeof(ticket_t),SEEK_CUR);
				fwrite(data,sizeof(ticket_t),1,fp);
				found = 1;
				break;
			}
		}
	}
	fclose(fp);

	return found; 
}

//根据ＩＤ从文件中查询票数据，并保存到buf所指的内存中
int Ticket_Perst_SelectByID(int ID, ticket_t *buf) 
{
	assert(NULL!=buf);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp)
	{
		return 0;
	}

	ticket_t data;
	int found = 0;

	while (!feof(fp))
	{
		if (fread(&data, sizeof(ticket_t), 1, fp))
		{
			if (ID == data.id)
			{
				*buf = data;
				found = 1;
				break;
			};
		}
	}
	fclose(fp);

	return found;
}

//查询所有票数据，并保存在buf所指的内存中
int Ticket_Perst_SelectAll(ticket_list_t list) 
{
	ticket_node_t *newNode;
	ticket_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, ticket_node_t);

	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp) 
	{	//文件不存在
		return 0;
	}

	while (!feof(fp)) 
	{
		if (fread(&data, sizeof(ticket_t), 1, fp))
		{
			newNode = (ticket_node_t*) malloc(sizeof(ticket_node_t));
			if (!newNode)
			{
				printf("警告:内存不足,无法载入更多数据!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);

	return recCount;
}

//获取与主键schedule_id相关的所有票
int Ticket_Perst_SelectBySchID(ticket_list_t list, int schedule_id) 
{
	assert(NULL != list);
	FILE *fp = fopen(TICKET_DATA_FILE, "rb");
	if (NULL == fp)
	{
		return 0;
	}
	ticket_node_t *pNew;
	ticket_t data;
	int listCount = 0;
	while (!feof(fp))
	{
		if (fread(&data, sizeof(ticket_t), 1, fp))
		{
			if (data.schedule_id == schedule_id)
			{
				pNew=(ticket_node_t *)malloc(sizeof(ticket_node_t));
				pNew->data = data;
				List_AddTail(list,pNew);
				listCount++;
			}
		}
	}
	fclose(fp);

	return listCount;
}

//根据票主键列表载入票
int Ticket_Perst_SelectByKeyList(ticket_list_t list, entkey_list_t keyList) {
	// 请补充完整
       return 1;
}
