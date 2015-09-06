#include "Schedule_Persist.h"
#include "../Service/Schedule.h"
#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../View/Ticket_UI.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>


static const char SCHEDULE_DATA_FILE[] = "Schedule.dat";
static const char SCHEDULE_DATA_TEMP_FILE[] = "ScheduleTmp.dat";

//添加演出计划信息
int Schedule_Perst_Insert(const schedule_t *data)
{
	assert(NULL != data);
	FILE *fp;
	int rtu = 0;
	fp = fopen(SCHEDULE_DATA_FILE,"ab");
	if (fp ==NULL)
	{
		printf("文件%s打开失败!\n","Play.dat");	
		return rtu;
	}
	rtu = fwrite(data,sizeof(schedule_t),1,fp);
	fclose(fp);
	return rtu;
}

//修改演出计划信息
int Schedule_Perst_Update(const schedule_t *data)
{
	assert(NULL != data);
	FILE *fp;
	int found = 0;
	schedule_t buf;
	fp = fopen(SCHEDULE_DATA_FILE,"rb+");
	if (fp == NULL)
	{
		printf("文件%s打开失败!\n","schedule.dat");
		return found;
	}
	while(!feof(fp))
	{
		if (fread(&buf,sizeof(schedule_t),1,fp))
		{
			if (buf.id == data->id)
			{
				fseek(fp,-sizeof(schedule_t),SEEK_CUR);
				fwrite(data,sizeof(schedule_t),1,fp);
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
	return found;
}

//根据ＩＤ删除演出计划
int Schedule_Perst_DeleteByID(int ID)
{
	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。

	//对原始数据文件重命名
	if(rename(SCHEDULE_DATA_FILE, SCHEDULE_DATA_TEMP_FILE)<0)
	{
		printf("不能打开文件: %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SCHEDULE_DATA_TEMP_FILE, "rb+");
	if (NULL == fpSour )
	{
		printf("不能打开文件: %s!\n", SCHEDULE_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SCHEDULE_DATA_FILE, "wb+");
	if ( NULL == fpTarg ) 
	{
		printf("不能打开文件: %s!\n", SCHEDULE_DATA_TEMP_FILE);
		return 0;
	}

	schedule_t buf;

	int found = 0;
	while (!feof(fpSour))
	{
		if (fread(&buf, sizeof(schedule_t), 1, fpSour))
		{
			if (ID == buf.id)
			{
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SCHEDULE_DATA_TEMP_FILE);
	return found;
}

//根据ＩＤ查询演出计划，并将数据保存如buf所指向内存
int Schedule_Perst_SelectByID(int ID, schedule_t *buf)
{
	assert(NULL!=buf);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp)
	{
		return 0;
	}

	schedule_t data;
	int found = 0;

	while (!feof(fp))
	{
		if (fread(&data, sizeof(schedule_t), 1, fp))
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

//获取所有演出计划
int Schedule_Perst_SelectAll(schedule_list_t list)
{
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, schedule_node_t);

	FILE *fp = fopen(SCHEDULE_DATA_FILE, "ab+");
	if (NULL == fp) 
	{	//文件不存在
		return 0;
	}

	while (!feof(fp)) 
	{
		if (fread(&data, sizeof(schedule_t), 1, fp))
		{
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
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

//获取剧目ＩＤ相同的所有演出计划
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id)
{
	assert(NULL != list);
	FILE *fp = fopen(SCHEDULE_DATA_FILE, "rb");
	if (NULL == fp)
	{
		return 0;
	}
	schedule_list_t pTmp;
	schedule_t data;
	int listCount = 0;
	while (!feof(fp))
	{
		if (fread(&data, sizeof(schedule_t), 1, fp))
		{
			if (data.play_id == play_id)
			{
				pTmp = (schedule_list_t)malloc(sizeof(schedule_node_t));
				if (pTmp == NULL)
					return 0;
				pTmp->data = data;
				List_AddTail(list,pTmp);
				listCount++;
			};
		}
	}
	fclose(fp);
	return listCount;
}
