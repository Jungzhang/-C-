#include "Sale_Persist.h"
#include "../Common/List.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

int Sale_Perst_Insert(const sale_t *data) {
	assert (data!=NULL);

	FILE *fp = fopen(SALE_DATA_FILE,"ab");

	int rtn = 0;

	if (fp == NULL){

		printf ("不能打开%s文件!\n",SALE_DATA_FILE);

		return 0;

	}
	rtn = fwrite (data,sizeof(sale_t),1,fp);
	fclose(fp);

	return rtn;
}

//根据销售ＩＤ删除订单的信息
int Sale_Perst_DeleteByID(int saleID)
{
	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。

	//对原始数据文件重命名
	if(rename(SALE_DATA_FILE, SALE_DATA_TEMP_FILE)<0)
	{
		printf("不能打开文件: %s!\n", SALE_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SALE_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour )
	{
		printf("不能打开文件: %s!\n", SALE_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SALE_DATA_FILE, "wb");
	if ( NULL == fpTarg ) 
	{
		printf("不能打开文件: %s!\n", SALE_DATA_TEMP_FILE);
		return 0;
	}

	sale_t buf;

	int found = 0;
	while (!feof(fpSour))
	{
		if (fread(&buf, sizeof(sale_t), 1, fpSour))
		{
			if (saleID == buf.id)
			{
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(sale_t), 1, fpTarg);
		}
	}

	fclose(fpTarg);
	fclose(fpSour);

	//删除临时文件
	remove(SALE_DATA_TEMP_FILE);

	return found;
}

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate,
		user_date_t endDate) {
	int recCount=0;
	sale_t saleRec;
	sale_node_t *newNode;
	assert(list!=NULL);
	FILE *fp = fopen(SALE_DATA_FILE,"rt");
	if(fp == NULL)
	{
		printf("不能打开%s文件!\n",SALE_DATA_FILE);
		return 0;
	}
	else
	{
		while(!feof(fp))
		{
			if(fread(&saleRec,sizeof(sale_t),1,fp)){

			if((saleRec.user_id == usrID)  && (saleRec.date.year >= stDate.year) && (saleRec.date.month >= stDate.month)  && (saleRec.date.day >= stDate.day) && (saleRec.date.year <= endDate.year) && (saleRec.date.year <= endDate.year) && (saleRec.date.month <= endDate.month) && ((saleRec.date.day <= endDate.day) || (saleRec.date.day >= endDate.day))){
							
			newNode = (sale_node_t *)malloc(sizeof(sale_node_t));

			if(!newNode){

				printf("警告:内存不足,无法载入更多数据!\n");

				break;	

			}

			newNode->data = saleRec;

			List_AddTail(list,newNode);

			recCount++;
			
			}
		    }
		}
		fclose(fp);
		return recCount;
	}
}


//根据给定时间区间内的销售记录
int Sale_Perst_SelectByDate(sale_list_t list, user_date_t stDate,
		user_date_t endDate)
{
	assert(NULL != list);
	FILE *fp = fopen(SALE_DATA_FILE, "rb");
	if (NULL == fp)
	{
		return 0;
	}
	sale_t saleRoc;
	sale_list_t newNode;
	int rocCount = 0;
	while(!feof(fp))
	{
		if (fread(&saleRoc, sizeof(sale_t), 1, fp))
		{
			if((stDate.year <= saleRoc.date.year && saleRoc.date.year <= endDate.year) && (stDate.month <= saleRoc.date.year && saleRoc.date.month <= endDate.month))

			{
			if((stDate.month < saleRoc.date.month && endDate.month > saleRoc.date.month) || (stDate.month == saleRoc.date.month) && (saleRoc.date.day > stDate.day) || (saleRoc.date.month == endDate.month) && (saleRoc.date.day < endDate.day))
				{
					newNode = (sale_node_t *)malloc(sizeof(sale_node_t));
					newNode->data = saleRoc;
					List_AddTail(list,newNode);
					rocCount++;
				}
			}
		}
		
	}
	fclose(fp);

       return rocCount;
}

/*

//queryUid = null,query all the uid Sale information return the all uid Sale information number
//queryUid =  uid, query the uid Sale information return the uid Sale  number
 *
int  Sale_Infor_By_Uid(char * queryUid, Sale_list_t head)
{
       // 请补充完整
       return 1;
}

int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head)
{
// 请补充完整
       return 1;
}

//根据票的id获得票的基本信息 
int Select_Price_By_Playid(int id, ticket_t *buf)
{
// 请补充完整
       return 1;
}
*/

