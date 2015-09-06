/*
 * Account_Persist.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include "Account_Persist.h"
#include "../Service/Account.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<unistd.h>
#include <string.h>

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";

//判断账号文件是否存在
int Account_Perst_CheckAccFile() {
       // 请补充完整
	return 1;
}

//根据用户名载入账号
int Account_Perst_SelByName(char usrName[], account_t *buf) {

/*	int found = 0;
	FILE *fp;
	account_t temp;
	
	if ((fp = fopen(ACCOUNT_DATA_FILE,"r+")) == NULL)
	{
		printf("打开文件%s失败!\n",ACCOUNT_DATA_FILE);
	}
	else
	{
		while (!feof(fp))
		{
			if (fread(&temp,sizeof(account_t),1,fp))
			{
				if (strcmp(temp.username,usrName) == 0)
				{
					*buf = temp;
					found = 1;
					break;
				}
			}
		}	
	}
	
	fclose(fp);
*/
	return 1;
}

int Account_Perst_Insert(const account_t *data) {
	
/*	int rtn = 0;
	FILE *fp;
	
	if ((fp = fopen(ACCOUNT_DATA_FILE,"ab+")) == NULL){
		printf("打开文件%s失败!\n",ACCOUNT_DATA_FILE);
	}
	else{
		rtn = fwrite(data,sizeof(account_t),1,fp);
	}

	fcolse(fp);
*/		
	return 1;
}

int Account_Perst_Update(const account_t * data) {

/*	int rtu = 0;
	FILE *fp;

	if (fopen(ACCOUNT_DATA_FILE))
	{

	}
*/
	return 1;
}

int Account_Perst_DeleteByID(int id) {
	// 请补充完整
	return 1;
}

int Account_Perst_SelectByID(int id, account_t *buf) {
	// 请补充完整
	return 1;
}

int Account_Perst_SelectAll(account_list_t list) {
	// 请补充完整
	return 1;
}

