/*
 * studioPersist.c
 *
 *  Created on: 2015年4月21日
 *      Author: Administrator
 */

#include "Studio_Persist.h"
#include "../Service/Studio.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>


static const char STUDIO_DATA_FILE[] = "Studio.dat";
static const char STUDIO_DATA_TEMP_FILE[] = "StudioTmp.dat";

//向文件中添加一个新演出厅信息
int Studio_Perst_Insert(const studio_t *data) {
	assert(NULL!=data);
	FILE *fp = fopen(STUDIO_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("不能打开文件: %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(studio_t), 1, fp);

	fclose(fp);
	return rtn;
}

//在文件中更新演出厅信息(例如:修改后的更新)
int Studio_Perst_Update(const studio_t * data) {
	assert(NULL!=data);

	FILE *fp = fopen(STUDIO_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("不能打开: %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	studio_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(studio_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -sizeof(studio_t), SEEK_CUR);
				fwrite(data, sizeof(studio_t), 1, fp);
				found = 1;
				break;
			}

		}
	}
	fclose(fp);

	return found;
}

//通过ID删除演出厅信息
int Studio_Perst_DeleteByID(int ID) {

	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。

	//对原始数据文件重命名
	if(rename(STUDIO_DATA_FILE, STUDIO_DATA_TEMP_FILE)<0){
		printf("不能打开文件: %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(STUDIO_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("不能打开文件: %s!\n", STUDIO_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(STUDIO_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("不能打开文件: %s!\n", STUDIO_DATA_TEMP_FILE);
		return 0;
	}

	studio_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(studio_t), 1, fpSour)) {
			if (ID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(studio_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(STUDIO_DATA_TEMP_FILE);
	return found;
}

//根据ID获取文件中相应的影厅信息
int Studio_Perst_SelectByID(int ID, studio_t *buf) {
	assert(NULL!=buf);

	FILE *fp = fopen(STUDIO_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	studio_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(studio_t), 1, fp)) {
			if (ID == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}

//将文件的演播厅数据读取到链表里
int Studio_Perst_SelectAll(studio_list_t list) {
	studio_node_t *newNode;
	studio_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, studio_node_t);

	FILE *fp = fopen(STUDIO_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(studio_t), 1, fp)) {
			newNode = (studio_node_t*) malloc(sizeof(studio_node_t));
			if (!newNode) {
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