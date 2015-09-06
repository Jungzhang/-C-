/*
 *  Seat_Persist.c
 *
 *  Created on: 2015年5月23日
 *  Author: lc
 */

#include "Seat_Persist.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTemp.dat";

//在文件中存入单个座位
int Seat_Perst_Insert(const seat_t *data) {
	assert (data!=NULL);
	FILE *fp = fopen(SEAT_DATA_FILE,"ab");
	int rtn = 0;
	if (fp == NULL){
		printf ("不能打开%s文件!\n",SEAT_DATA_FILE);
		return 0;
	}

	rtn = fwrite (data,sizeof(seat_t),1,fp);
	
	fclose(fp);
	return rtn;
}

//在文件批量存入座位
int Seat_Perst_InsertBatch(seat_list_t list) {
	seat_node_t *pTemp = list->next;
	int rtn = 0;
	FILE *fp = fopen(SEAT_DATA_FILE,"ab");
	if (fp == NULL){
                printf ("不能打开%s文件!\n",SEAT_DATA_FILE);
                return 0;	
	}
	
	while (pTemp != list) {
		if (fwrite(&(pTemp->data), sizeof(seat_t), 1, fp)) {
			pTemp = pTemp->next;
			rtn++;
		}
	}

	fclose(fp);
	return rtn;
}

//在文件中更新座位
int Seat_Perst_Update(const seat_t *data) {

	assert (data!=NULL);
	
	FILE *fp = fopen(SEAT_DATA_FILE,"rb+");
	if (fp == NULL){
		printf ("不能打开%s文件!\n",SEAT_DATA_FILE);
		return 0;
	}
	
	seat_t buf;
	int found = 0;
	
	while (!feof(fp)){
		if (fread(&buf,sizeof(seat_t),1,fp)){
			if (buf.id == data->id){
				fseek(fp,-sizeof(seat_t),SEEK_CUR);
				found = fwrite(data,sizeof(seat_t),1,fp);
				break;
			}
		}
	}
	fclose(fp);
	
	return found;
}

//根据ID在文件中删除座位
int Seat_Perst_DeleteByID(int ID) {
	if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0){

		printf("不能打开%s文件!\n", SEAT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb+");
	if (NULL == fpSour ){
		printf("不能打开%s文件!\n", SEAT_DATA_FILE);
		return 0;
}

	fpTarg = fopen(SEAT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("不能打开%s文件!\n", SEAT_DATA_TEMP_FILE);
		return 0;
}

	seat_t buf;

	int found = 0;
	while (!feof(fpSour)){
		if (fread(&buf,sizeof(seat_t),1,fpSour)){
			if (ID == buf.id){
				found = 1;
				continue;
			}
			fwrite (&buf,sizeof(seat_t),1,fpTarg);
		}	
	}
	fclose(fpTarg);
	fclose(fpSour);

	remove(SEAT_DATA_TEMP_FILE);
	return found;
}

//根据放映厅ID批量删除
int Seat_Perst_DeleteAllByRoomID(int roomID) {

	seat_t buf;
        int found = 0;
        FILE *fpSour, *fpTarg;
	if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0){
                printf("不能打开%s文件!\n", SEAT_DATA_FILE);
                return 0;
        }
        fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb+");
        if (NULL == fpSour ){
                printf("不能打开%s文件!\n", SEAT_DATA_FILE);
                return 0;
        }
	fpTarg = fopen(SEAT_DATA_FILE, "wb");
        if ( NULL == fpTarg ) {
                printf("不能打开%s文件!\n", SEAT_DATA_TEMP_FILE);
                return 0;
        }
	
        while (!feof(fpSour)) {
		
                if (fread(&buf, sizeof(seat_t), 1, fpSour)) {
                        if (roomID == buf.roomID) {
                                found = 1;
                                continue;
                        }
                fwrite(&buf, sizeof(seat_t), 1, fpTarg);
                }
        }
        fclose(fpTarg);
        fclose(fpSour);
        remove(SEAT_DATA_TEMP_FILE);

        return found;

//        return 1;

}


//根据ID在文件中获取座位
int Seat_Perst_SelectByID(int ID, seat_t *buf) {
	assert(NULL!=buf);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");

	if (NULL == fp) {

		return 0;

	}

	seat_t data;

	int found = 0;

	while (!feof(fp)) {

		if (fread(&data, sizeof(seat_t), 1, fp)) {

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

//在文件中获取所有座位

int Seat_Perst_SelectAll(seat_list_t list) {

	seat_node_t *newNode;

	seat_t data;

	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, seat_node_t);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");

	if (NULL == fp) { 

		return 0;

	}

	while (!feof(fp)) {

		if (fread(&data, sizeof(seat_t), 1, fp)) {

			newNode = (seat_node_t*) malloc(sizeof(seat_node_t));

			if (!newNode) {

				printf("警告，内存溢出!!!\n不能更多的数据加载到内存中!!!");

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

//根据演出厅ID从文件中获取其所有座位

int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID) {

	seat_node_t *newNode;

	seat_t data;

	int recCount = 0;

	assert(NULL!=list);

	List_Free(list,seat_node_t);

	FILE *fp = fopen(SEAT_DATA_FILE,"rb");

	if(NULL == fp)
	{
		printf("不能打开文件%s!\n",SEAT_DATA_FILE);
		return 0;
	}

	while(!feof(fp))
	{

		if(fread(&data, sizeof(seat_t), 1, fp))

		{

			newNode = (seat_node_t *)malloc(sizeof(seat_node_t));

			if(!newNode)

			{

				printf("警告！内存溢出！\n 不能更多的数据加载到内存中!!");

				break;

			}


			if(data.roomID==roomID){
				newNode->data=data;
				List_AddTail(list,newNode);
				recCount++;
			}


		}	
	}

	fclose(fp);

	return recCount;

}











