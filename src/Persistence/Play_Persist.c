#include "Play_Persist.h"
#include "../Service/Play.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>
#include <string.h>

static const char PLAY_DATA_FILE[] = "Play.dat";
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat";

//将参数所指向的剧目信息写入剧目文件中,失败返回0,成功返回成功写入的个数
int Play_Perst_Insert(const play_t *data) {
	assert(NULL != data);
	FILE *fp;	int rtu = 0;
	fp = fopen(PLAY_DATA_FILE,"ab");
	if (fp ==NULL)
	{
		printf("文件%s打开失败!\n","Play.dat");		return rtu;
	}
	rtu = fwrite(data,sizeof(play_t),1,fp);
	fclose(fp);
	return rtu; 
}

//将参数所指向的剧目信息写入到剧目文件中,成功返回1,失败返回0
int Play_Perst_Update(const play_t *data) {

	assert(NULL != data);
	FILE *fp;	int found = 0;
	play_t buf;
	fp = fopen(PLAY_DATA_FILE,"rb+");
	if (fp == NULL)
	{
		printf("文件%s打开失败!\n",PLAY_DATA_FILE);	return found;
	}
	while(!feof(fp))
	{
		if (fread(&buf,sizeof(play_t),1,fp))
		{
			if (buf.id == data->id)
			{
				fseek(fp,-sizeof(play_t),SEEK_CUR);
				fwrite(data,sizeof(play_t),1,fp);
				found = 1;
				break;
			}
		}
	}
	fclose(fp);

	return found; 
}

//根据ID从文件中删除信息,成功返回1,失败返回0
int Play_Perst_DeleteByID(int ID) {

	FILE *fpSour,*fpTarg;	int found = 0;
	play_t buf;
	if (rename(PLAY_DATA_FILE,PLAY_DATA_TEMP_FILE) < 0)
	{
		printf("打开文件%s失败!\n",PLAY_DATA_FILE);	return found;
	}
	fpSour = fopen(PLAY_DATA_TEMP_FILE,"rb+");
	if (fpSour == NULL)
	{
		printf("打开文件%s失败!\n",PLAY_DATA_TEMP_FILE);	return  found;
	}
	fpTarg = fopen(PLAY_DATA_FILE,"wb+");
	if (fpTarg == NULL)
	{
		printf("打开文件%s失败!\n",PLAY_DATA_FILE);	return found;
	}
	while(!feof(fpSour))
	{
		if (fread(&buf,sizeof(play_t),1,fpSour))
		{
			if (buf.id == ID)
			{
				found = 1;	continue;
			}
			fwrite(&buf,sizeof(play_t),1,fpTarg);
		}
	}
	fclose(fpTarg);	fclose(fpSour);
	remove(PLAY_DATA_TEMP_FILE);

	return found; 
}

//根据ID获取文件中的数据到buf
int Play_Perst_SelectByID(int ID, play_t *buf) {
	
	assert(NULL!=buf);
	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) {
		printf("文件%s打开失败!\n",PLAY_DATA_FILE);
		return 0;
	}

	play_t data;
	int found = 0;
	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {

			if (data.id == ID)
			{
				*buf = data;	found = 1;	break;
			}

		}
	}

	return found; 
}

int Play_Perst_SelectAll(play_list_t list) {
	
	assert(NULL != list);
	play_list_t pNew;
	int newCount = 0;
	play_t data;
	List_Free(list,play_node_t);
	FILE *fp = fopen(PLAY_DATA_FILE, "rb+");
	if (fp == NULL)
	{
		printf("文件%s打开失败!",PLAY_DATA_FILE);
		return newCount;
	}
	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			pNew = (play_list_t)malloc(sizeof(play_node_t));
			if (!pNew) {
				printf("警告:内存不足,无法载入更多数据!\n");
				break;
			}
			pNew->data = data;
			List_AddTail(list, pNew);
			newCount++;
		}
	}

	return newCount;
}
// 根据名称把文件中的数据读入链表
int Play_Perst_SelectByName(play_list_t list, char condt[]) {

	assert(NULL!= list);	
	int temp;
	FILE *fp = fopen(PLAY_DATA_FILE, "rb");

	if (NULL == fp) {
		printf("文件%s打开失败!\n",PLAY_DATA_FILE);
		return 0;
	}

	play_list_t pNew;
	play_t data;
	int found = 0;
	List_Free(list,play_node_t);
	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			temp = strcmp(data.name,condt);
			if (temp == 0){
				pNew = (play_list_t)malloc(sizeof(play_node_t));
				pNew->data = data;
				List_AddTail(list,pNew);	found = 1;
			}
		}
	}
	return found;
}

